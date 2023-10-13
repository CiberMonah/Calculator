#ifndef COMMONS_H_INCLUDED
#define COMMONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

const int VERSION = 1;
char SIGNATURE[] = "CM";

enum cpu_commands {
    PUSH = 1,
    POP = 2,
    ADD = 3,
    MUL = 4,
    DIV = 5,
    SQRT = 6,
    SUP = 7,
    SIN = 8,
    COS = 9,
    IN = 10,
    OUT = 11,
    HLT = -1,
    RPUSH = 43,
    RPOP = 33
};

enum cpu_arguments {
    N = 1,
    R = 1 << 1,
};

enum cpu_registers {
    rax = 1,
    rbx = 1 << 1,
    rcx = 1 << 2,
    cdx = 1 << 3,
};

enum cpu_error_type {
    CPU_NO_ERR = 0,

    CPU_READING_ERR = 1 << 1,
    CPU_WRONG_COMMAND_ERROR = 1 << 2,
    CPU_WRONG_ARGUMENT_ERROR = 1 << 3,
};

#endif