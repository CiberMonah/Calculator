#ifndef COMMONS_H_INCLUDED
#define COMMONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "assembler.h"

const int VERSION = 1;
char SIGNATURE[] = "CM";


const int MAX_LENGTH_OF_CMD = 5;


enum cpu_commands_id {
    WRONG_COMMAND   =  -1,

    PUSH            = 1 ,
    POP             = 2 ,
    ADD             = 3 ,
    MUL             = 4 ,
    DIV             = 5 ,
    SQRT            = 6 ,
    SUP             = 7 ,
    SIN             = 8 ,
    COS             = 9 ,
    IN              = 10,
    OUT             = 11,
    HLT             = 12,
    RPOP            = 13,
    RPUSH           = 14,
    JMP             = 15,
    LBL             = 16,
};

struct CPU_OP {
    const char*     name                            = nullptr;

    cpu_commands_id com_id                          = WRONG_COMMAND;
    int             argn                            = 0;

    // value_type <-> signature
    cpu_arguments   cpu_argvt[MAX_ARGN]             = {};
    Elem_t          cpu_argv [MAX_ARGN]             = {};
    cpu_registers   cpu_regv [MAX_ARGN]             = {};
};

const CPU_OP ALL_COMMANDS[50] {                                 //!ORDER IS IMPORTANT!
                                                                //The array element is accessed by the command code that matches the number in the array
    {"wrong",           WRONG_COMMAND,  -1,     {},     {},     {}      },
    {"push",            PUSH,           1,      {B},    {},     {}      },
    {"pop",             POP,            1,      {B},    {},     {}      },
    {"add",             ADD,            0,      {},     {},     {}      },
    {"mul",             MUL,            0,      {},     {},     {}      },
    {"div",             DIV,            0,      {},     {},     {}      },
    {"sqrt",            SQRT,           0,      {},     {},     {}      },
    {"sup",             SUP,            0,      {},     {},     {}      },
    {"sin",             SIN,            0,      {},     {},     {}      },
    {"cos",             COS,            0,      {},     {},     {}      },
    {"in",              IN,             1,      {},     {},     {}      },
    {"out",             OUT,            0,      {},     {},     {}      },
    {"hlt",             HLT,            0,      {},     {},     {}      },
    {"rpush",           RPUSH,          1,      {R},    {},     {}      },
    {"rpop",            RPOP,           1,      {R},    {},     {}      },
    {"jmp",             JMP,            1,      {N},    {},     {}      },
    {"adl",             LBL,            0,      {L},    {},     {}      }
};



#endif