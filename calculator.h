#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED
#include "stack.h"
#include "assembler.h"
#include "commons.h"

#define PRC_DUMP(prc) ({                                                 \
    dump_processor((prc), __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    })

struct CPU {
    int RAX = 0;
    int RBX = 0;
    int RCX = 0;
    int RDX = 0;
    int* CS = NULL;
    int IP = 0;
    Stack* stk;
};

enum cpu_error_type {
    CPU_NO_ERR                  = 0,

    CPU_READING_ERR             = 1 << 1,
    CPU_WRONG_COMMAND_ERR       = 1 << 2,
    CPU_WRONG_ARGUMENT_ERR      = 1 << 3,
    CPU_WRONG_REGISTER_ERR      = 1 << 4,
    CPU_MEM_ALLOC_ERR           = 1 << 5,
    CPU_VOID_POINTER_ERR        = 1 << 6,
};

void dump_processor(CPU* cpu) ;
void command_add(Stack* stk);
void command_out(Stack* stk);
void command_mul(Stack* stk);
void command_div(Stack* stk);
void command_sin(Stack* stk);
void command_cos(Stack* stk);
void command_sup(Stack* stk);
void command_sqrt(Stack* stk);
void command_in(Stack* stk);
int  get_command(FILE* fp, int* command);
void command_pop(Stack* stk, Elem_t* number);
void command_push(Stack* stk, Elem_t number);

#endif