#ifndef clox_vm_h
#define clox_vm_h
#include "chunk.h"
#include "value.h"

#define STACK_MAX 256
typedef struct VM
{
    Chunk *chunk;
    uint8_t *ip; // instruction pointer
    Value stack[STACK_MAX];
    Value *stack_top;
} VM;

typedef enum Interpret_Result
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} Interpret_Result;

void init_VM();
void free_VM();
Interpret_Result interpret(const char *source);
void push(Value value);
Value pop();
#endif
