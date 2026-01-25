#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <Platform/defines.h>

BEGIN_C_DECLARATIONS

typedef struct PointerListNode PointerListNode;
typedef struct PointerList PointerList;

typedef struct PointerListNode
	{
	PointerList *owner;
	void *data;
	PointerListNode *next, *previous;
	} PointerListNode;

typedef struct PointerList
	{
	PointerListNode *first, *last;
	unsigned count;
	} PointerList;

void PointerList_Initialize ( PointerList *list );
void PointerList_Destroy ( PointerList *list );
PointerListNode *PointerList_AddAtEnd ( PointerList *list, const void *data );
PointerListNode *PointerList_InsertAfter ( PointerList *list, PointerListNode *node, const void *data );
PointerListNode *PointerList_InsertBefore ( PointerList *list, PointerListNode *node, const void *data );
void PointerList_DestroyNode ( PointerList *list, PointerListNode *node );

bool PointerList_IsEmpty ( const PointerList *list );
unsigned PointerList_GetSize ( const PointerList *list );
void PointerList_Clear ( PointerList *list );
void *PointerList_GetNodeData ( const PointerListNode *node );

PointerListNode *PointerList_Find ( const PointerList *list, PointerListNode *start, const void *data );
PointerListNode *PointerList_GetFirst ( const PointerList *list );
PointerListNode *PointerList_GetLast ( const PointerList *list );
PointerListNode *PointerList_GetNextNode ( const PointerListNode *node );
PointerListNode *PointerList_GetPreviousNode ( const PointerListNode *node );

END_C_DECLARATIONS
