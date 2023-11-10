#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED
#include "stack.h"

#define CPU_DUMP(cpu, f) ({                                                   \
    dump_processor((cpu), (f), __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    })

struct CPU {
    int rax = 0;
    int rbx = 0;
    int rcx = 0;
    int rdx = 0;
    int com_buffer_size = 0;
    char* comand_buffer = nullptr;
    int* memory = nullptr;
    int car;
    Stack stk = {};
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

void dump_processor(CPU* cpu, FILE* dump_file, const char* file, const char* func, const int line);
void cpu_init(CPU* cpu);
void cpu_dtor(CPU* cpu);
int read_comands(CPU* cpu, const char * FileName);


#endif