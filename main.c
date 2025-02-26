#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char *argv[])
{
	Chunk chunk;
	init_chunk(&chunk);
	write_chunk(&chunk, OP_RETURN);
	dissasemble_chunk(&chunk, "Test");
	free_chunk(&chunk);
	return 0;
}