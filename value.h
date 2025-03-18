#ifndef value_h
#define value_h

#include "common.h"

typedef double Value;

typedef struct ValueArray
{
    int capacity;
    int count;
    Value *values;
} ValueArray;

void init_value_array(ValueArray *array);
void write_value_array(ValueArray *array, Value val);
void free_value_array(ValueArray *array);
void print_value(Value value);
#endif