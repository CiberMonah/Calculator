#include "cpu_comands.h"
#include "stack.h"
#include <math.h>

void comand_push(CPU* cpu) {
    cpu->car ++;
    char number = cpu->comand_buffer[cpu->car];
    stack_push(&cpu->stk, (int)number);
}

void comand_pop(CPU* cpu) {
    int number = 0;
    stack_pop(&cpu->stk, &number);
}

void comand_add(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res += number;
    stack_pop(&cpu->stk, &number);
    res += number;
    stack_push(&cpu->stk, res);
}

void comand_sup(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = number;
    stack_pop(&cpu->stk, &number);
    res -= number;
    stack_push(&cpu->stk, res);
}

void comand_mul(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = number;
    stack_pop(&cpu->stk, &number);
    res *= number;
    stack_push(&cpu->stk, res);
}

void comand_div(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = number;
    stack_pop(&cpu->stk, &number);
    res /= number;
    stack_push(&cpu->stk, res);
}

void comand_cos(CPU* cpu) {
    Elem_t res = 0, number = 0;
    comand_pop(stk, &number);
    res = (int)(cos(double(number)));
    comand_push(stk, res);
}

void comand_sin(CPU* cpu) {
    Elem_t res = 0, number = 0;
    comand_pop(stk, &number);
    res = (int)(sin(double(number)));
    comand_push(stk, res);
}

void comand_sqrt(CPU* cpu) {
    Elem_t res = 0, number = 0;
    comand_pop(stk, &number);
    res = (int)(sqrt((double)number));
    comand_push(stk, (Elem_t) res);
}

void comand_rpush(CPU* cpu) {
    Elem_t number = 0;
    comand_pop(proc->stk, &number);
    proc->rax
}

void comand_rpop(CPU* cpu) {
    Elem_t number = 0;
    comand_pop(proc->stk, &number);
    comand_push(proc->stk, number);
    proc->rax
}


void comand_in(CPU* cpu) {
    printf("Input number - \n");
    Elem_t number = 0;
    scanf("%d", &number);
    comand_push(stk, number);
}

void comand_out(CPU* cpu) {
    Elem_t number = 0;
    comand_pop(stk, &number);
    printf("%d", number);
}

