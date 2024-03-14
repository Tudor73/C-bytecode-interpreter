#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#define DEBUG_TRACE_EXECUTION 10

void disassemble_chunk(Chunk *chunk, const char *name);

int disassemble_instruction(Chunk *chunk, int offset);
#endif