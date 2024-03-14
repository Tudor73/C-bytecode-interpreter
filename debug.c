#include "debug.h"
#include <stdio.h>
#include "value.h"
#include "chunk.h"

void disassemble_chunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassemble_instruction(chunk, offset);
    }
}

static int constant_instruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];
    printf("%s %d ", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static int simpleInstruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

int disassemble_instruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset);
    if (offset > 0 &&
        chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf(" | ");
    }
    else
    {
        printf("%4d ", chunk->lines[offset]);
    }
    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
        return constant_instruction("OP_CONSTANT", chunk, offset);
    case OP_ADD:
        return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
        return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
        return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
        return simpleInstruction("OP_DIVIDE", offset);
    case OP_NEGATE:
        return simpleInstruction("OP_NEGATE", offset);
    default:
        printf("Unknown opcode at line %d\n", instruction);
        return offset + 1;
        return 0;
    }
}
