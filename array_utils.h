#pragma once
#include <stdbool.h>

bool array_resize ( void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_capacity, const bool clear );
bool array_ensure_free_space ( void **array, const unsigned used, unsigned *capacity, const unsigned element_size, const unsigned desired_free_space, const bool clear );
