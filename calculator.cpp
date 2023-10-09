#include <stdio.h>
#include <stdlib.h>
#include "commons.h"
#include "stack.h"
#include "calculator.h"
#include <math.h>

const int PRECISION = 100;


//void processor_ctor...
//processor d_tor

void dump_processor(CPU* cpu, const char* file, const char* func, const int line) {
    printf( "Dump called in file -%s\n"
            "func - %s\n"
            "line - %d\n", file, func, line);
    printf( "rax - %d\n"
            "rbx - %d\n"
            "rcx - %d\n"
            "rdx - %d\n");
    printf("Commands");
    for(int i = 0; cpu->CS[i] != HLT; i++)
        printf("%d ", cpu->CS[i]);
    printf("IP - %d\n", cpu->IP);
    print_stack(cpu->stk);
}

//По кайфу добавить возращаемое значение ошибки

int get_command(FILE* fp, int* command) {
    if(fscanf(fp, "%d", command) == EOF) {
        return 0;
    } else {
        return 1;
    }
}

cpu_error_type cpu_dtor(CPU* cpu) {
    cpu->rax = 0;
    cpu->rbx = 0;
    cpu->rcx = 0;
    cpu->rdx = 0;
    cpu->CS = nullptr;
    cpu->IP = 0;
    stack_dtor(cpu->stk);
    return CPU_NO_ERR;
}

void command_push(Stack* stk, Elem_t number) {
    stack_push(stk, number * PRECISION);
}

void command_pop(Stack* stk, Elem_t* number) {
    stack_pop(stk, number);
}

void command_add(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res += number;
    command_pop(stk, &number);
    res += number;
    command_push(stk, res / PRECISION);
}

void command_sup(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res += number;
    command_pop(stk, &number);
    res -= number;
    command_push(stk, res / PRECISION);
}

void command_mul(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res = number;
    command_pop(stk, &number);
    res *= number;
    command_push(stk, res / (PRECISION * PRECISION));
}

void command_div(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res = number;
    command_pop(stk, &number);
    if(number == 0) return;
    res = (int)(((double)number / (double)res));
    command_push(stk, res);
}

void command_cos(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res = (int)(cos(double(number)));
    command_push(stk, res / PRECISION);
}

void command_sin(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res = (int)(sin(double(number)) * (double)PRECISION);
    command_push(stk, res / PRECISION);
}

void command_sqrt(Stack* stk) {
    Elem_t res = 0, number = 0;
    command_pop(stk, &number);
    res = (int)(sqrt((double)number));
    command_push(stk, (Elem_t) (res * sqrt(PRECISION)) / PRECISION);
}

// void command_rpush(Processor* proc){
//     Elem_t number = 0;
//     command_pop(proc->stk, &number);
//     proc->rax
    
// }

// void command_rpop(Processor* proc){
//     Elem_t number = 0;
//     command_pop(proc->stk, &number);
//     command_push(proc->stk, number);
//     proc->rax
    
// }




void command_in(Stack* stk) {
    printf("Input number - \n");
    Elem_t number = 0;
    scanf("%d", &number);
    command_push(stk, number);
}

void command_out(Stack* stk) {
    Elem_t number = 0;
    command_pop(stk, &number);
    printf("Result - %d,%d\n", number / PRECISION, number % PRECISION);
}

