#include "ThreadPool.h"
#include "PointerList.h"
#include <threads.h>
#include <assert.h>

typedef enum
	{
	QUEUED,
	RUNNING,
	FINISHED
	} TaskStatus;

typedef struct
	{
	int (*function)(void *);
	void *extra_data;
	int task_id;
	int result;
	TaskStatus status;
	} TaskData;

typedef struct ThreadPool
	{
	PointerList task_list;
	int last_task_id;
	mtx_t task_list_mutex;
	cnd_t wake_up;
	mtx_t wake_up_mutex;
	cnd_t task_finished;
	mtx_t task_finished_mutex;

	thrd_t *threads;
	unsigned thread_count;
	unsigned free_threads;
	bool quitting;
	} ThreadPool;

static void PushTaskToQueue(const TaskData *new_task, ThreadPool *pool)
	{
	thrd_t current_thread = thrd_current();
	mtx_lock(&pool->task_list_mutex);
	PointerList_AddAtEnd(&pool->task_list, new_task);
	printf("thread %u - PUSH - task queue now with %u tasks\n", current_thread._Tid, PointerList_GetSize(&pool->task_list));
	mtx_unlock(&pool->task_list_mutex);
	}

static TaskData *PopTaskFromQueue(ThreadPool *pool)
	{
	thrd_t current_thread = thrd_current();
	mtx_lock(&pool->task_list_mutex);
	pointer_list_node *first_node = PointerList_GetFirst(&pool->task_list);
	TaskData *current_task = NULL;
	if (first_node != NULL)
		{
		current_task = PointerList_GetNodeData(first_node);
		PointerList_DestroyNode(&pool->task_list, first_node);
		}
	printf("thread %u - POP - task queue now with %u tasks\n", current_thread._Tid, PointerList_GetSize(&pool->task_list));
	mtx_unlock(&pool->task_list_mutex);
	return current_task;
	}

static int ThreadPool_LoopFunction(ThreadPool *pool)
	{
	thrd_t current_thread = thrd_current();
	printf("thread %u - start\n", current_thread._Tid);
	do
		{
		if (pool->quitting)
			{
			printf("thread %u - quitting enabled. Leaving\n", current_thread._Tid);
			break;
			}

		// Grab the first available task, if available
		TaskData *current_task = PopTaskFromQueue(pool);

		if (current_task != NULL) // There was a task. run it...
			{
			pool->free_threads--;
			current_task->status = RUNNING;
			current_task->result = current_task->function(current_task->extra_data);
			current_task->status = FINISHED;
			pool->free_threads++;
			cnd_signal(&pool->task_finished);
			free(current_task);
			}
		else // No more tasks. Wait for a signal
			{
			printf("thread %u - no tasks available. Waiting\n", current_thread._Tid);
			mtx_lock(&pool->wake_up_mutex);
			cnd_wait(&pool->wake_up, &pool->wake_up_mutex);
			mtx_unlock(&pool->wake_up_mutex);// unlock mutex so that other threads can wait using it
			printf("thread %u - wake up\n", current_thread._Tid);
			}

		}
	while (pool->quitting == false);
	return 0;
	}

ThreadPool *ThreadPool_Create(void)
	{
	ThreadPool *pool = calloc(1, sizeof(ThreadPool));
	if (pool == NULL)
		return NULL;

	PointerList_Initialize(&pool->task_list);
	pool->last_task_id = -1;
	int result = mtx_init(&pool->task_list_mutex, mtx_plain);
	result = cnd_init(&pool->wake_up);
	result = mtx_init(&pool->wake_up_mutex, mtx_plain);
	result = cnd_init(&pool->task_finished);
	result = mtx_init(&pool->task_finished_mutex, mtx_recursive);
	pool->thread_count = 8;
	pool->free_threads = pool->thread_count;
	pool->quitting = false;
	pool->threads = calloc(pool->thread_count, sizeof(thrd_t));
	if (pool->threads == NULL)
		{
		free(pool);
		return NULL;
		}
	for (unsigned index = 0; index < pool->thread_count; ++index)
		{
		thrd_create(&pool->threads[index], ThreadPool_LoopFunction, pool);
		}
	return pool;
	}

void ThreadPool_Destroy(ThreadPool *pool)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return;

	ThreadPool_CancelAll(pool);

	pool->quitting = true;
	cnd_broadcast(&pool->wake_up);

	for (unsigned index = 0; index < pool->thread_count; ++index)
		{
		thrd_join(pool->threads[index], NULL);
		printf("thread %u - joined\n", pool->threads[index]._Handle);
		}

	pool->thread_count = 0;
	free(pool->threads);
	cnd_destroy(&pool->wake_up);
	mtx_destroy(&pool->wake_up_mutex);
	cnd_destroy(&pool->task_finished);
	mtx_destroy(&pool->task_finished_mutex);
	mtx_destroy(&pool->task_list_mutex);
	pool->last_task_id = -1;
	PointerList_Destroy(&pool->task_list);
	free(pool);
	}

int ThreadPool_AddTask(ThreadPool *pool, int(*func)(void *), void *extra_data)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return -1;

	TaskData *new_task = (TaskData *)calloc(1, sizeof(TaskData));
	if (new_task == NULL)
		return -2;

	int task_id = ++pool->last_task_id;
	new_task->function = func;
	new_task->extra_data = extra_data;
	new_task->task_id = task_id;
	new_task->status = QUEUED;
	PushTaskToQueue(new_task, pool);

	cnd_signal(&pool->wake_up);
	return task_id;
	}

void ThreadPool_CancelTask(ThreadPool *pool, int task_id)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return;
	if (task_id < 0)
		return;

	// Search for this task on the queue
	mtx_lock(&pool->task_list_mutex);
	for (pointer_list_node *iterator = PointerList_GetFirst(&pool->task_list); iterator != NULL; iterator = PointerList_GetNextNode(iterator))
		{
		TaskData *task_pointer = PointerList_GetNodeData(iterator);
		if (task_pointer->task_id == task_id)
			{
			free(task_pointer);
			PointerList_DestroyNode(&pool->task_list, iterator);
			break;
			}
		}
	mtx_unlock(&pool->task_list_mutex);
	}

void ThreadPool_CancelAll(ThreadPool *pool)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return;

	mtx_lock(&pool->task_list_mutex);
	for (pointer_list_node *iterator = PointerList_GetFirst(&pool->task_list); iterator != NULL; iterator = PointerList_GetNextNode(iterator))
		{
		TaskData *task_pointer = PointerList_GetNodeData(iterator);
		free(task_pointer);
		}
	PointerList_Clear(&pool->task_list);
	mtx_unlock(&pool->task_list_mutex);
	}

bool ThreadPool_IsTaskQueued(ThreadPool *pool, int task_id)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return false;
	if (task_id < 0)
		return false;

	// Search for this task on the queue
	TaskData *selected_task = NULL;
	mtx_lock(&pool->task_list_mutex);
	for (pointer_list_node *iterator = PointerList_GetFirst(&pool->task_list); iterator != NULL; iterator = PointerList_GetNextNode(iterator))
		{
		TaskData *task_pointer = PointerList_GetNodeData(iterator);
		if (task_pointer->task_id == task_id)
			{
			selected_task = task_pointer;
			break;
			}
		}
	mtx_unlock(&pool->task_list_mutex);
	if (selected_task == NULL)
		return false;
	return true;
	}

bool ThreadPool_WaitForAll(ThreadPool *pool)
	{
	assert(pool != NULL);
	if (pool == NULL)
		return false;

	bool is_empty = false;
	mtx_lock(&pool->task_list_mutex);
	is_empty = PointerList_IsEmpty(&pool->task_list);
	mtx_unlock(&pool->task_list_mutex);
	while ((is_empty == false) || (pool->free_threads != pool->thread_count))
		{
		mtx_lock(&pool->task_finished_mutex);
		cnd_wait(&pool->task_finished, &pool->task_finished_mutex);
		mtx_unlock(&pool->task_finished_mutex);
		mtx_lock(&pool->task_list_mutex);
		is_empty = PointerList_IsEmpty(&pool->task_list);
		mtx_unlock(&pool->task_list_mutex);
		}

	return true;
	}
