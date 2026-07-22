#pragma once
#include <stdbool.h>

bool Array_Resize ( void **ArrayPointer, const unsigned Used, unsigned *Capacity, const unsigned ElementSize, const unsigned desired_capacity, const bool clear );
bool Array_EnsureFreeSpace ( void **ArrayPointer, const unsigned Used, unsigned *Capacity, const unsigned ElementSize, const unsigned DesiredFreeSpace, const bool clear );
bool Array_DeleteAndShift ( void **ArrayPointer, const unsigned IndexToDelete, unsigned *Used, const unsigned ElementSize );
bool Array_DeleteAndSwap ( void **ArrayPointer, const unsigned IndexToDelete, unsigned *Used, const unsigned ElementSize );
void Array_Clear ( void **ArrayPointer, unsigned *Used, unsigned *Capacity, const unsigned ElementSize, const bool clear );
void Array_Free ( void **ArrayPointer, unsigned *Used, unsigned *Capacity );
bool Memory_ReallocAndClear ( void **Pointer, const unsigned CurrentSize, const unsigned NewSize );
bool Memory_Realloc ( void **Pointer, const unsigned NewSize );

#define ARRAY_RESIZE(ARRAY,USED,CAPACITY,DESIRED) Array_Resize((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]),DESIRED,true)
#define ARRAY_ENSURE_FREE_SPACE(ARRAY,USED,CAPACITY,DESIRED) Array_EnsureFreeSpace((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]),DESIRED,true)
#define ARRAY_PUSH_BACK(ARRAY,USED,CAPACITY,ITEM) {Array_EnsureFreeSpace((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]), 1, false);ARRAY[USED]=ITEM;++USED; }
