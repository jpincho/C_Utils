#pragma once
#include <stdbool.h>

bool Array_Resize ( void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_capacity, const bool clear );
bool Array_EnsureFreeSpace ( void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_free_space, const bool clear );
