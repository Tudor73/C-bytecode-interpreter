#include "value.h"
#include "memory.h"
#include <stdlib.h>

void init_value_array(ValueArray *array)
{
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void write_value_array(ValueArray *array, Value val)
{
    if (array->capacity < array->count + 1)
    {
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->values = (Value *)reallocate(array->values, sizeof(uint8_t) * old_capacity, sizeof(uint8_t) * array->capacity);
    }
    array->values[array->count] = val;
    array->count += 1;
}

void free_value_array(ValueArray *array)
{
    reallocate(array->values, sizeof(uint8_t) * array->capacity, 0);
    init_value_array(array);
}
