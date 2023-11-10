#include <stdio.h>
#include <stdlib.h>
#include "commons.h"
#include "stack.h"
#include "processor.h"
#include <math.h>

const int PRECISION = 1;


//void processor_ctor...
//processor d_tor

void dump_processor(CPU* cpu, const char* file, const char* func, const int line) {
    printf( "Dump called in file -%s\n"
            "func - %s\n"
            "line - %d\n", file, func, line);
    printf( "rax - %d\n"
            "rbx - %d\n"
            "rcx - %d\n"
            "rdx - %d\n", cpu->RAX, cpu->RBX, cpu->RCX, cpu->RDX);
    printf("Commands");
    for(int i = 0; cpu->CS[i] != HLT; i++)
        printf("%d ", cpu->CS[i]);
    printf("IP - %d\n", cpu->car);
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
    cpu->RAX = 0;
    cpu->RBX = 0;
    cpu->RCX = 0;
    cpu->RDX = 0;
    cpu->CS = nullptr;
    cpu->car = 0;
    stack_dtor(cpu->stk);
    return CPU_NO_ERR;
}
