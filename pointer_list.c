#include "pointer_list.h"
#include <memory.h>
#include <assert.h>

// public functions
void pointer_list_init(pointer_list *list)
	{
	list->first = list->last = NULL;
	list->count = 0;
	}

void pointer_list_destroy(pointer_list *list)
	{
	pointer_list_clear(list);
	free(list);
	}

pointer_list_node *pointer_list_add_at_end(pointer_list *list, void *data)
	{
	pointer_list_node *new_node = calloc(1, sizeof(pointer_list_node));
	if (new_node == NULL)
		return NULL;

	new_node->owner = list;
	new_node->next = NULL;
	new_node->previous = list->last;
	new_node->data = data;

	if (list->first == NULL)
		{
		list->first = new_node;
		}
	else
		{
		list->last->next = new_node;
		}
	list->last = new_node;
	++list->count;
	return new_node;
	}

pointer_list_node *pointer_list_insert_after(pointer_list *list, pointer_list_node *node, void *data)
	{
	// In case the list is empty, <node> parameter can be null
	if (node == NULL)
		{
		if (list->first == NULL)
			return pointer_list_add_at_end(list, data);
		else
			return NULL;
		}

	assert(node->owner == list);
	pointer_list_node *new_node = calloc(1, sizeof(pointer_list_node));
	if (new_node == NULL)
		return NULL;

	// Connect this node to neighbours
	new_node->owner = list;
	new_node->next = node->next;
	new_node->previous = node;
	new_node->data = data;

	// connect the reference node and neighbours to the new node
	if (node->next != NULL)
		node->next->previous = new_node;
	node->next = new_node;

	// if last node was the reference node, it is now the new one
	if (node->next == list->last)
		list->last = new_node;
	++list->count;
	return new_node;
	}

pointer_list_node *pointer_list_insert_before(pointer_list *list, pointer_list_node *node, void *data)
	{
	// In case the list is empty, <node> parameter can be null
	if (node == NULL)
		{
		if (list->first == NULL)
			return pointer_list_add_at_end(list, data);
		else
			return NULL;
		}

	assert(node->owner == list);
	pointer_list_node *new_node = calloc(1, sizeof(pointer_list_node));
	if (new_node == NULL)
		return NULL;

	// Connect this node to neighbours
	new_node->owner = list;
	new_node->next = node;
	new_node->previous = node->previous;
	new_node->data = data;

	// connect the reference node and neighbours to the new node
	if (node->previous != NULL)
		node->previous->next = new_node;
	node->previous = new_node;

	// if first node was the reference node, it is now the new one
	if (node->previous == list->first)
		list->first = new_node;
	++list->count;
	return new_node;
	}

void pointer_list_destroy_node(pointer_list *list, pointer_list_node *node)
	{
	assert(node->owner == list);
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;

	if (node == list->first)
		list->first = node->next;
	if (node == list->last)
		list->last = node->previous;
	node->next = node->previous = NULL;
	--list->count;
	}

bool pointer_list_empty(const pointer_list *list)
	{
	return list->count == 0;
	}

unsigned pointer_list_size(const pointer_list *list)
	{
	return list->count;
	}

void pointer_list_clear(pointer_list *list)
	{
	pointer_list_node *iterator = list->first;
	while (iterator != NULL)
		{
		pointer_list_node *next = iterator->next;
		iterator->next = iterator->previous = NULL;
		iterator->owner = NULL;
		free(iterator);
		iterator = next;
		}
	list->first = list->last = NULL;
	list->count = 0;
	}

void *pointer_list_get_node_data(const pointer_list_node *node)
	{
	return node->data;
	}

pointer_list_node *pointer_list_find(const pointer_list *list, pointer_list_node *start, const void *data)
	{
	if (start == NULL)
		return NULL;
	assert(start->owner == list);
	pointer_list_node *iterator = start;
	while ((iterator != NULL) && (start->data != data))
		{
		iterator = iterator->next;
		}
	return iterator;
	}

pointer_list_node *pointer_list_first(const pointer_list *list)
	{
	return list->first;
	}

pointer_list_node *pointer_list_last(const pointer_list *list)
	{
	return list->last;
	}

pointer_list_node *pointer_list_get_next_node(const pointer_list_node *node)
	{
	return node->next;
	}

pointer_list_node *pointer_list_get_previous_node(const pointer_list_node *node)
	{
	return node->previous;
	}