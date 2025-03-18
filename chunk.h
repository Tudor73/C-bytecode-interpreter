#ifndef chunk_h
#define chunk_h

#include "common.h"
#include "value.h"

typedef enum OpCode
{
	OP_CONSTANT,
	OP_RETURN,

} OpCode;

typedef struct Chunk
{
	int count;
	int capacity;
	uint8_t *code;
	int *lines;
	ValueArray constants;
} Chunk;

void init_chunk(Chunk *chunk);
void write_chunk(Chunk *chunk, uint8_t byte, int line);
int add_constant(Chunk *chunk, Value value);
void free_chunk(Chunk *chunk);

#endif