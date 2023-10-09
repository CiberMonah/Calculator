#ifndef COMMONS_H_INCLUDED
#define COMMONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

const int VERSION = 1;
char SIGNATURE[] = "CM";

enum stack_commands {
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

enum cpu_error_type {
    NO_ERR = 0,

    READING_ERR = 1 << 1,
    WRONG_COMMAND_ERROR = 1 << 2,

};

#endif