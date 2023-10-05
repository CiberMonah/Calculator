#include <stdio.h>
#include <stdlib.h>
#include "commons.h"
#include "stack.h"
#include "calculator.h"
#include <math.h>

const int PRECISION = 100;

int get_command(FILE* fp, int* command) {
    if(fscanf(fp, "%d", command) == EOF) {
        return 0;
    } else {
        return 1;
    }
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

