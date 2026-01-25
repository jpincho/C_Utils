#include "PointerArray.h"
#include <stdlib.h>
#include <assert.h>

void PointerArray_Initialize ( PointerArray *array )
	{
	array->capacity = array->count = 0;
	array->data = NULL;
	}

void PointerArray_Destroy ( PointerArray *array )
	{
	array->capacity = array->count = 0;
	if ( array->data )
		free ( array->data );
	array->data = NULL;
	}

bool PointerArray_Reserve ( PointerArray *array, unsigned new_capacity )
	{
	if ( new_capacity < array->count )
		return false;
	void *temp = realloc ( array->data, sizeof ( uintptr_t ) * new_capacity );
	assert ( temp != NULL );
	if ( temp == NULL )
		return false;
	array->data = temp;
	array->capacity = new_capacity;
	return true;
	}

bool PointerArray_EnsureFreeSpace ( PointerArray *array, unsigned free_space )
	{
	unsigned needed_capacity = array->count + free_space;
	if ( needed_capacity > array->capacity )
		{
		unsigned new_size = needed_capacity / 10;
		if ( new_size < needed_capacity )
			new_size += 10;
		return PointerArray_Reserve ( array, new_size );
		}
	return true;
	}

bool PointerArray_AddAtEnd ( PointerArray *array, intptr_t data )
	{
	if ( PointerArray_EnsureFreeSpace ( array, 1 ) == false )
		return false;

	array->data[array->count] = data;
	++array->count;
	return true;
	}

bool PointerArray_InsertAt ( PointerArray *array, unsigned index, intptr_t data )
	{
	if ( PointerArray_EnsureFreeSpace ( array, 1 ) == false )
		return false;

	// shift all elements forward
	memmove ( array->data + index + 1, array->data + index, array->count - index );
	array->data[index] = data;
	++array->count;
	return true;
	}

void PointerArray_RemoveAt ( PointerArray *array, unsigned index )
	{
	PointerArray_EnsureFreeSpace ( array, 1 );

	// shift all elements back
	memmove ( array->data + index, array->data + index + 1, array->count - index - 1 );
	--array->count;
	}

bool PointerArray_IsEmpty ( const PointerArray *array )
	{
	return array->count == 0;
	}

unsigned PointerArray_GetSize ( const PointerArray *array )
	{
	return array->count;
	}

void PointerArray_Clear ( PointerArray *array )
	{
	array->count = 0;
	}

intptr_t PointerArray_Get ( const PointerArray *array, const unsigned index )
	{
	return array->data[index];
	}

void PointerArray_Set ( const PointerArray *array, const unsigned index, const intptr_t new_value )
	{
	assert ( index < array->count );
	array->data[index] = new_value;
	}