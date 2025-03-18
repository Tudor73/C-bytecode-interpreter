#include "debug.h"
#include "value.h"
#include <stdio.h>

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

static int constant_instruciton(char *name, Chunk *chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]); // the values are in constants.values. In other languages you would only do constan[constant]
    printf("\n");
    return offset + 2;
}

int dissasemble_instruction(Chunk *c, int offset)
{
    printf("%04d ", offset); // this prints 4 ints, and fills at the start with 0s
    if (offset > 0 && c->lines[offset] == c->lines[offset - 1])
    {
        printf("     | ");
    }
    else
    {
        printf("%4d ", c->lines[offset]);
    }
    uint8_t instruction = c->code[offset];
    switch (instruction)
    {
    case OP_CONSTANT:
        return constant_instruciton("OP_CONSTANT", c, offset);
    case OP_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
    return 0;
}
