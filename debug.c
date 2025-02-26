#include "debug.h"

void dissasemble_chunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;)
    {
        // increment the offset in the funciton because instructions will have different sizes
        offset = dissasemble_instruction(chunk, offset);
    }
}

static int simple_instruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

int dissasemble_instruction(Chunk *c, int offset)
{
    printf("%04d ", offset); // this prints 4 ints, and fills at the start with 0s
    uint8_t instruction = c->code[offset];
    switch (instruction)
    {
    case OP_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
    return 0;
}
