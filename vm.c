#include "vm.h"
#include "common.h"
#include "stdio.h"
#include "debug.h"

VM vm;

static InterpretResult run()
{
    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        printf("              ");
        for (Value *slot = vm.stack; slot < vm.stack_top; slot++)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        dissasemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = *vm.ip++)
        {
        case OP_CONSTANT:
        {
            Value constant = vm.chunk->constants.values[*vm.ip++];
            push(constant);
            break;
        }
        case OP_RETURN:
        {
            print_value(pop());
            printf("\n");
            return INTERPRET_OK;
            break;
        }
        }
    }
}
InterpretResult interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code; // ip starts at the firrst byte
    run();
}

static void reset_stack()
{
    vm.stack_top = vm.stack;
}

void init_vm()
{
    reset_stack();
}

void free_vm()
{
}

void push(Value value)
{
    *vm.stack_top = value; // stack_top points just past the last used element. So *vm.stack_top = value will store the value in the array.
    vm.stack_top++;
}

Value pop()
{
    vm.stack_top--;
    return *vm.stack_top;
}
