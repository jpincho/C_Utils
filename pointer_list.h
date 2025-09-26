#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <Platform/defines.h>

BEGIN_C_DECLARATIONS

typedef struct pointer_list_node pointer_list_node;
typedef struct pointer_list pointer_list;

typedef struct pointer_list_node
	{
	pointer_list *owner;
	void *data;
	pointer_list_node *next, *previous;
	}pointer_list_node;

typedef struct pointer_list
	{
	pointer_list_node *first, *last;
	unsigned count;
	}pointer_list;

void pointer_list_init ( pointer_list *list );
void pointer_list_destroy ( pointer_list *list );
pointer_list_node *pointer_list_add_at_end ( pointer_list *list, const void *data );
pointer_list_node *pointer_list_insert_after ( pointer_list *list, pointer_list_node *node, const void *data );
pointer_list_node *pointer_list_insert_before ( pointer_list *list, pointer_list_node *node, const void *data );
void pointer_list_destroy_node ( pointer_list *list, pointer_list_node *node );

bool pointer_list_empty ( const pointer_list *list );
unsigned pointer_list_size ( const pointer_list *list );
void pointer_list_clear ( pointer_list *list );
void *pointer_list_get_node_data ( const pointer_list_node *node );

pointer_list_node *pointer_list_find ( const pointer_list *list, pointer_list_node *start, const void *data );
pointer_list_node *pointer_list_first ( const pointer_list *list );
pointer_list_node *pointer_list_last ( const pointer_list *list );
pointer_list_node *pointer_list_get_next_node ( const pointer_list_node *node );
pointer_list_node *pointer_list_get_previous_node ( const pointer_list_node *node );

END_C_DECLARATIONS
