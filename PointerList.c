#include "PointerList.h"
#include <memory.h>
#include <assert.h>

// public functions
void PointerList_Initialize ( PointerList *list )
	{
	list->first = list->last = NULL;
	list->count = 0;
	}

void PointerList_Destroy ( PointerList *list )
	{
	PointerList_Clear ( list );
	free ( list );
	}

PointerListNode *PointerList_AddAtEnd ( PointerList *list, void *data )
	{
	PointerListNode *new_node = calloc ( 1, sizeof ( PointerListNode ) );
	if ( new_node == NULL )
		return NULL;

	new_node->owner = list;
	new_node->next = NULL;
	new_node->previous = list->last;
	new_node->data = data;

	if ( list->first == NULL )
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

PointerListNode *PointerList_InsertAfter ( PointerList *list, PointerListNode *node, void *data )
	{
	// In case the list is empty, <node> parameter can be null
	if ( node == NULL )
		{
		if ( list->first == NULL )
			return PointerList_AddAtEnd ( list, data );
		else
			return NULL;
		}

	assert ( node->owner == list );
	PointerListNode *new_node = calloc ( 1, sizeof ( PointerListNode ) );
	if ( new_node == NULL )
		return NULL;

	// Connect this node to neighbours
	new_node->owner = list;
	new_node->next = node->next;
	new_node->previous = node;
	new_node->data = data;

	// connect the reference node and neighbours to the new node
	if ( node->next != NULL )
		node->next->previous = new_node;
	node->next = new_node;

	// if last node was the reference node, it is now the new one
	if ( node->next == list->last )
		list->last = new_node;
	++list->count;
	return new_node;
	}

PointerListNode *PointerList_InsertBefore ( PointerList *list, PointerListNode *node, void *data )
	{
	// In case the list is empty, <node> parameter can be null
	if ( node == NULL )
		{
		if ( list->first == NULL )
			return PointerList_AddAtEnd ( list, data );
		else
			return NULL;
		}

	assert ( node->owner == list );
	PointerListNode *new_node = calloc ( 1, sizeof ( PointerListNode ) );
	if ( new_node == NULL )
		return NULL;

	// Connect this node to neighbours
	new_node->owner = list;
	new_node->next = node;
	new_node->previous = node->previous;
	new_node->data = data;

	// connect the reference node and neighbours to the new node
	if ( node->previous != NULL )
		node->previous->next = new_node;
	node->previous = new_node;

	// if first node was the reference node, it is now the new one
	if ( node->previous == list->first )
		list->first = new_node;
	++list->count;
	return new_node;
	}

void PointerList_DestroyNode ( PointerList *list, PointerListNode *node )
	{
	assert ( node->owner == list );
	if ( node->previous )
		node->previous->next = node->next;
	if ( node->next )
		node->next->previous = node->previous;

	if ( node == list->first )
		list->first = node->next;
	if ( node == list->last )
		list->last = node->previous;
	node->next = node->previous = NULL;
	--list->count;
	}

bool PointerList_IsEmpty ( const PointerList *list )
	{
	return list->count == 0;
	}

unsigned PointerList_GetSize ( const PointerList *list )
	{
	return list->count;
	}

void PointerList_Clear ( PointerList *list )
	{
	PointerListNode *iterator = list->first;
	while ( iterator != NULL )
		{
		PointerListNode *next = iterator->next;
		iterator->next = iterator->previous = NULL;
		iterator->owner = NULL;
		free ( iterator );
		iterator = next;
		}
	list->first = list->last = NULL;
	list->count = 0;
	}

void *PointerList_GetNodeData ( const PointerListNode *node )
	{
	return node->data;
	}

PointerListNode *PointerList_Find ( const PointerList *list, PointerListNode *start, const void *data )
	{
	if ( start == NULL )
		return NULL;
	assert ( start->owner == list );
	PointerListNode *iterator = start;
	while ( ( iterator != NULL ) && ( start->data != data ) )
		{
		iterator = iterator->next;
		}
	return iterator;
	}

PointerListNode *PointerList_GetFirst ( const PointerList *list )
	{
	return list->first;
	}

PointerListNode *PointerList_GetLast ( const PointerList *list )
	{
	return list->last;
	}

PointerListNode *PointerList_GetNextNode ( const PointerListNode *node )
	{
	return node->next;
	}

PointerListNode *PointerList_GetPreviousNode ( const PointerListNode *node )
	{
	return node->previous;
	}