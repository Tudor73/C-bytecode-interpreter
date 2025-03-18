#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk *chunk)
{
	chunk->capacity = 0;
	chunk->count = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	init_value_array(&chunk->constants);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line)
{
	if (chunk->capacity < chunk->count + 1)
	{
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = (uint8_t *)reallocate(chunk->code, sizeof(uint8_t) * oldCapacity, chunk->capacity * sizeof(uint8_t));
		chunk->lines = (int *)reallocate(chunk->lines, sizeof(int) * oldCapacity, chunk->capacity * sizeof(int));
	}
	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

int add_constant(Chunk *chunk, Value value)
{
	write_value_array(&chunk->constants, value);
	return chunk->constants.count - 1;
}

void free_chunk(Chunk *chunk)
{
	reallocate(chunk->code, sizeof(uint8_t) * chunk->capacity, 0);
	reallocate(chunk->lines, sizeof(int) * chunk->capacity, 0);
	free_value_array(&chunk->constants);
	init_chunk(chunk);
}