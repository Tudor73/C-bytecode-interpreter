#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
typedef enum OpCode
{
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

typedef struct Chunk
{
    int count;
    int capacity;
    uint8_t *code;
    ValueArray constants;
    int *lines;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte, int line);
void free_chunk(Chunk *chunk);
int add_constant(Chunk *chunk, Value value);
#endif