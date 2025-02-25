#ifndef chunk_h
#define chunk_h

#include "common.h"

typedef enum OpCode
{
	OP_RETURN,

} OpCode;

typedef struct Chunk
{
	int count;
	int capacity;
	uint8_t *code;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte);
void free_chunk(Chunk *chunk);

#endif