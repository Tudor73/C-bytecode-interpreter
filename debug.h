#ifndef debug_h
#define debug_h

#include "chunk.h"
#include <stdio.h>

void dissasemble_chunk(Chunk *chunk, const char *name);
int dissasemble_instruction(Chunk *c, int offset);

#endif