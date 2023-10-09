#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STK_DUMP(stk) ({                                                \
    stack_dump((stk), 0, __FILE__, __PRETTY_FUNCTION__, __LINE__);         \
    })

#define STK_CTOR(stk) ({                                                \
    stack_ctor((stk), #stk, __LINE__, __PRETTY_FUNCTION__, __FILE__);   \
    })

typedef int Elem_t;
const unsigned long LEFT_PARROT  = 0xDEDABABA;
const unsigned long RIGHT_PARROT = 0x40401367;
const Elem_t VOID_ELEM = 9996;
const int CAPACITY_MULTIPLIER = 2;
const int CAPACITY_GISTERESIS = 2;

enum stack_error_type {
    STACK_NO_ERR                 = 0 << 0,

    STACK_MEM_ALLOC_ERR         = 1 << 1,
    STACK_NULL_PTR_ERR          = 1 << 2,
    STACK_OUT_OF_INDEX_ERR      = 1 << 3,
    STACK_IS_NOT_EXIST          = 1 << 4,
    STACK_CANARY_ERR            = 1 << 5,
    STACK_SIZE_ERR              = 1 << 6,
    STACK_HASH_ERR              = 1 << 7,
    STACK_VERIFICATION_ERR      = 1 << 9,
    STACK_NO_VOID_ELEM_ERR      = 1 << 9,
};

struct Stack {
    unsigned long left_canary = LEFT_PARROT;

    Elem_t* data = NULL;
    int size        = 0;
    int capacity    = 0;
    bool is_exist   = 0;
    int errors = NO_ERR;

    int              line =    0;
    const char*      name = NULL;
    const char* file_name = NULL;
    const char* func_name = NULL;

    long hash = 0;
    void (*print_func)(void*) = NULL;

    unsigned long right_canary = RIGHT_PARROT;
};


stack_error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file);
stack_error_type stack_pop(Stack* stk, Elem_t* poped);
stack_error_type stack_dtor(Stack* stk);
stack_error_type stack_dump(Stack* stk, bool only_data, const char* file, const char* func, const int line);
stack_error_type print_error(stack_error_type error);
stack_error_type stack_push(Stack* stk, Elem_t value);
stack_error_type put_error(Stack* stk, stack_error_type error);
long hasher (Stack* stk);
stack_error_type print_stack(Stack* stk);
bool check_error (Stack* stk);
int stack_verificator(Stack* stk);
void execution(Stack* stk);

#endif // STACK_H_INCLUDED
