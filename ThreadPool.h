#pragma once
#include <stdbool.h>

typedef struct ThreadPool ThreadPool;

ThreadPool *ThreadPool_Create ( void );
void ThreadPool_Destroy ( ThreadPool *pool );
int ThreadPool_AddTask ( ThreadPool *pool, int ( *func ) ( void * ), void *extra_data );
void ThreadPool_CancelTask ( ThreadPool *pool, int task_id );
void ThreadPool_CancelAll ( ThreadPool *pool );
bool ThreadPool_IsTaskQueued ( ThreadPool *pool, int task_id );
bool ThreadPool_WaitForAll ( ThreadPool *pool );
