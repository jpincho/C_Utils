#include "pointer_array.h"
#include <stdlib.h>
#include <assert.h>

void pointer_array_init(pointer_array *array)
    {
    array->capacity = array->count = 0;
    array->data = NULL;
    }

void pointer_array_destroy(pointer_array *array)
    {
    array->capacity = array->count = 0;
    if (array->data)
        free(array->data);
    array->data = NULL;
    }

bool pointer_array_reserve(pointer_array *array, unsigned new_capacity)
    {
    if (new_capacity < array->count)
        return false;
    void *temp = realloc(array->data, sizeof(uintptr_t) * new_capacity);
    assert(temp != NULL);
    if (temp == NULL)
        return false;
    array->data = temp;
    array->capacity = new_capacity;
    return true;
    }

bool pointer_array_ensure_free_space(pointer_array *array, unsigned free_space)
    {
    unsigned needed_capacity= array->count + free_space;
    if(needed_capacity > array->capacity)
        {
        unsigned new_size = needed_capacity / 10;
        if (new_size < needed_capacity)
            new_size += 10;
        return pointer_array_reserve(array, new_size);
        }
    return true;
    }

bool pointer_array_add_at_end(pointer_array *array, intptr_t data)
    {
    if (pointer_array_ensure_free_space(array, 1) == false)
        return false;

    array->data[array->count] = data;
    ++array->count;
    return true;
    }

bool pointer_array_insert_at(pointer_array *array, unsigned index, intptr_t data)
    {
    if (pointer_array_ensure_free_space(array, 1) == false)
        return false;

    // shift all elements forward
    memmove(array->data + index + 1, array->data + index, array->count - index);
    array->data[index] = data;
    ++array->count;
    return true;
    }

void pointer_array_remove_at(pointer_array *array, unsigned index)
    {
    pointer_array_ensure_free_space(array, 1);

    // shift all elements back
    memmove(array->data + index, array->data + index + 1, array->count - index - 1);
    --array->count;
    }

bool pointer_array_empty(const pointer_array *array)
    {
    return array->count == 0;
    }

unsigned pointer_array_size(const pointer_array *array)
    {
    return array->count;
    }

void pointer_array_clear(pointer_array *array)
    {
    array->count = 0;
    }

intptr_t pointer_array_get(const pointer_array *array, const unsigned index)
    {
    return array->data[index];
    }

void pointer_array_set(const pointer_array *array, const unsigned index, const intptr_t new_value)
    {
    assert(index < array->count);
    array->data[index] = new_value;
    }