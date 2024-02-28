#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
typedef enum Opcode
{
    OP_RETURN,
} OpCode;

typedef struct Chunk
{
    int count;
    int capacity;
    uint8_t *code;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte);
void free_chunk(Chunk *chunk);
#endif