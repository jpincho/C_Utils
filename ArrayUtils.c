#include "ArrayUtils.h"
#include <stdlib.h>
#include <memory.h>

bool Array_Resize(void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_capacity, const bool clear)
	{
	if (*capacity == desired_capacity)
		return true;
	if (used > desired_capacity)
		return false;

	void *new_pointer = realloc(*array, desired_capacity * element_size);
	if (new_pointer == NULL)
		return false;
	*array = new_pointer;
	// Clears the new area, if needed
	if ((clear) && (desired_capacity > *capacity))
		memset((char *)*array + (*capacity * element_size), 0, element_size * (desired_capacity - *capacity));
	*capacity = desired_capacity;
	return true;
	}

bool Array_EnsureFreeSpace(void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_free_space, const bool clear)
	{
	// If I already have enough free space, return
	if (*capacity >= used + desired_free_space)
		return true;

	// Calculate new capacity and realloc
	unsigned new_capacity = used + desired_free_space;
	return Array_Resize(array, used, capacity, element_size, new_capacity, clear);
	}