#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <Platform/defines.h>

BEGIN_C_DECLARATIONS
typedef struct
    {
    intptr_t *data;
    unsigned count, capacity;
    } pointer_array;

void pointer_array_init ( pointer_array *array );
void pointer_array_destroy ( pointer_array *array );
bool pointer_array_reserve ( pointer_array *array, unsigned new_capacity );
bool pointer_array_ensure_free_space ( pointer_array *array, unsigned free_space );
bool pointer_array_add_at_end ( pointer_array *array, intptr_t data );
bool pointer_array_insert_at ( pointer_array *array, unsigned index, intptr_t data );
void pointer_array_remove_at ( pointer_array *array, unsigned index );
bool pointer_array_empty ( const pointer_array *array );
unsigned pointer_array_size ( const pointer_array *array );
void pointer_array_clear ( pointer_array *array );
intptr_t pointer_array_get ( const pointer_array *array, const unsigned index );
void pointer_array_set ( const pointer_array *array, const unsigned index, const intptr_t new_value );
END_C_DECLARATIONS
