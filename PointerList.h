#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <Platform/defines.h>

BEGIN_C_DECLARATIONS

typedef struct pointer_list_node pointer_list_node;
typedef struct PointerList PointerList;

typedef struct pointer_list_node
	{
	PointerList *owner;
	void *data;
	pointer_list_node *next, *previous;
	} pointer_list_node;

typedef struct PointerList
	{
	pointer_list_node *first, *last;
	unsigned count;
	} PointerList;

void PointerList_Initialize ( PointerList *list );
void PointerList_Destroy ( PointerList *list );
pointer_list_node *PointerList_AddAtEnd ( PointerList *list, const void *data );
pointer_list_node *PointerList_InsertAfter ( PointerList *list, pointer_list_node *node, const void *data );
pointer_list_node *PointerList_InsertBefore ( PointerList *list, pointer_list_node *node, const void *data );
void PointerList_DestroyNode ( PointerList *list, pointer_list_node *node );

bool PointerList_IsEmpty ( const PointerList *list );
unsigned PointerList_GetSize ( const PointerList *list );
void PointerList_Clear ( PointerList *list );
void *PointerList_GetNodeData ( const pointer_list_node *node );

pointer_list_node *PointerList_Find ( const PointerList *list, pointer_list_node *start, const void *data );
pointer_list_node *PointerList_GetFirst ( const PointerList *list );
pointer_list_node *PointerList_GetLast ( const PointerList *list );
pointer_list_node *PointerList_GetNextNode ( const pointer_list_node *node );
pointer_list_node *PointerList_GetPreviousNode ( const pointer_list_node *node );

END_C_DECLARATIONS
