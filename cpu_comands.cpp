#include "stack.h"
#include <math.h>
#include "cpu_comands.h"
#include "commons.h"

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
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = (int)cos((double)number);
    stack_push(&cpu->stk, res);
}

void comand_sin(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = (int)sin((double)number);
    stack_push(&cpu->stk, res);
}

void comand_sqrt(CPU* cpu) {
    int res = 0;
    int number = 0;
    stack_pop(&cpu->stk, &number);
    res = (int)sqrt((double)number);
    stack_push(&cpu->stk, res);
}

void comand_rpush(CPU* cpu) {
    int number = 0;
    stack_pop(&cpu->stk, &number);
    cpu->car++;
    int reg = cpu->comand_buffer[cpu->car];
    switch (reg) {
        case RAX:
            cpu->rax = number;
            break;
        case RBX:
            cpu->rbx = number;
            break;
        case RCX:
            cpu->rcx = number;
            break;
        case RDX:
            cpu->rdx = number;
            break;
        default:
            break;
    }
}

void comand_rpop(CPU* cpu) {
    cpu->car++;
    int reg = cpu->comand_buffer[cpu->car];
    switch (reg) {
        case RAX:
            stack_push(&cpu->stk, cpu->rax);
            break;
        case RBX:
            stack_push(&cpu->stk, cpu->rbx);
            break;
        case RCX:
            stack_push(&cpu->stk, cpu->rcx);
            break;
        case RDX:
            stack_push(&cpu->stk, cpu->rdx);
            break;
        default:
            break;
    }
}


void comand_in(CPU* cpu) {
    printf("Input number - \n");
    int number = 0;
    scanf("%d", &number);
    stack_push(&cpu->stk, number);
}

void comand_out(CPU* cpu) {
    int number = 0;
    stack_pop(&cpu->stk, &number);
    printf("%d ", number);
}

