#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#include "commons.h";

struct CPU_OP {
    const char* name = nullptr;
    cpu_commands com_id = POP;
    int argn = 0;
    cpu_arguments* cpu_argv = nullptr;
};

struct CPU_REG {
    const char* name = nullptr;
    cpu_registers value = rax;
};

void assembler(FILE* inf, FILE* outf);
cpu_error_type creat_op(char* name, cpu_commands com_id, int argn, cpu_arguments arg_arr[], CPU_OP* operation);



#endif