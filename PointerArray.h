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

void PointerArray_Initialize ( pointer_array *array );
void PointerArray_Destroy ( pointer_array *array );
bool PointerArray_Reserve ( pointer_array *array, unsigned new_capacity );
bool PointerArray_EnsureFreeSpace ( pointer_array *array, unsigned free_space );
bool PointerArray_AddAtEnd ( pointer_array *array, intptr_t data );
bool PointerArray_InsertAt ( pointer_array *array, unsigned index, intptr_t data );
void PointerArray_RemoveAt ( pointer_array *array, unsigned index );
bool PointerArray_IsEmpty ( const pointer_array *array );
unsigned PointerArray_GetSize ( const pointer_array *array );
void PointerArray_Clear ( pointer_array *array );
intptr_t PointerArray_Get ( const pointer_array *array, const unsigned index );
void PointerArray_Set ( const pointer_array *array, const unsigned index, const intptr_t new_value );
END_C_DECLARATIONS
