#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED
#include "stack.h"

void command_add(Stack* stk);
void command_out(Stack* stk);
void command_mul(Stack* stk);
void command_div(Stack* stk);
void command_sin(Stack* stk);
void command_cos(Stack* stk);
void command_sup(Stack* stk);
void command_sqrt(Stack* stk);
void command_in(Stack* stk);
int get_command(FILE* fp, int* command);
void command_pop(Stack* stk, Elem_t* number);
void command_push(Stack* stk, Elem_t number);

#endif