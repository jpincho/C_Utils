#pragma once
#include <stdbool.h>

bool Array_Resize ( void **array, const unsigned Used, unsigned *Capacity, const unsigned element_size, const unsigned desired_capacity, const bool clear );
bool Array_EnsureFreeSpace ( void **array, const unsigned Used, unsigned *Capacity, const unsigned element_size, const unsigned desired_free_space, const bool clear );
void Array_Clear ( void **array, unsigned *Used, unsigned *Capacity, const unsigned element_size, const bool clear );
void Array_Free ( void **array, unsigned *Used, unsigned *Capacity );

#define ARRAY_RESIZE(ARRAY,USED,CAPACITY,DESIRED) Array_Resize((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]),DESIRED,true)
#define ARRAY_ENSURE_FREE_SPACE(ARRAY,USED,CAPACITY,DESIRED) Array_EnsureFreeSpace((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]),DESIRED,true)
#define ARRAY_PUSH_BACK(ARRAY,USED,CAPACITY,ITEM) {Array_EnsureFreeSpace((void**)&ARRAY,USED,&CAPACITY,sizeof(ARRAY[0]), 1, false);ARRAY[USED]=ITEM;++USED; }
