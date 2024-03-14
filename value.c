#include "value.h"

#include <stdio.h>
#include "memory.h"

void init_value_array(ValueArray *array)
{
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void write_value_array(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, array->capacity, array->capacity * 2);
    }
    array->values[array->count] = value;
    array->count++;
}

void free_value_array(ValueArray *array)
{
    FREE_ARRAY(Value, array->values, array->count);
    init_value_array(array); // resets the value array
}

void print_value(Value value)
{
    printf("%g", value);
}
