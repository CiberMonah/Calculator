#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#include "commons.h"
#include "stack.h"
#include "calculator.h"

const int MAX_ARGN          = 3;
const int NUMBER_OF_CMD     = 100;
const int NUMBER_OF_LABELS  = 10;
const int POISON_VALUE      = 999;

enum cpu_arguments {
    NONE_ARG        = 0,

    N               = 1,
    R               = 1 << 1,
    B               = N | R,
    L               = 1 << 2,
};

enum cpu_registers {
    NONE            = 0,

    RAX             = 1,
    RBX             = 1 << 1,
    RCX             = 1 << 2,
    RDX             = 1 << 3,
};

struct CPU_REG {
    const char*     name                = nullptr;
    cpu_registers   value               = NONE;
};

struct LABEL {
    char* name              = 0;
    int ptr                 = -1;
};

LABEL LABELS[NUMBER_OF_LABELS] = {};


void assembler(FILE* inf, FILE* outf, FILE* log, FILE* bin);


#endif