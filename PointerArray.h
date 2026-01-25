#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <Platform/defines.h>

BEGIN_C_DECLARATIONS
typedef struct
	{
	intptr_t *data;
	unsigned count, capacity;
	} PointerArray;

void PointerArray_Initialize ( PointerArray *array );
void PointerArray_Destroy ( PointerArray *array );
bool PointerArray_Reserve ( PointerArray *array, unsigned new_capacity );
bool PointerArray_EnsureFreeSpace ( PointerArray *array, unsigned free_space );
bool PointerArray_AddAtEnd ( PointerArray *array, intptr_t data );
bool PointerArray_InsertAt ( PointerArray *array, unsigned index, intptr_t data );
void PointerArray_RemoveAt ( PointerArray *array, unsigned index );
bool PointerArray_IsEmpty ( const PointerArray *array );
unsigned PointerArray_GetSize ( const PointerArray *array );
void PointerArray_Clear ( PointerArray *array );
intptr_t PointerArray_Get ( const PointerArray *array, const unsigned index );
void PointerArray_Set ( const PointerArray *array, const unsigned index, const intptr_t new_value );
END_C_DECLARATIONS
