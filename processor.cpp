#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "processor.h"
#include "cpu_comands.h"
#include "commons.h"


void dump_processor(CPU* cpu, FILE* dump_file, const char* file, const char* func, const int line) {
    fprintf(dump_file, "Dump called in file -%s\n"
            "func - %s\n"
            "line - %d\n", file, func, line);
    fprintf(dump_file, "rax - %d\n"
            "rbx - %d\n"
            "rcx - %d\n"
            "rdx - %d\n", cpu->rax, cpu->rbx, cpu->rcx, cpu->rdx);
    fprintf(dump_file, "Number of commands: %d\n", cpu->com_buffer_size);
    if(cpu->comand_buffer != nullptr) {
        fprintf(dump_file, "Commands: ");
        for(int i = 0; cpu->comand_buffer[i] ; i++)
            fprintf(dump_file, "%d ", cpu->comand_buffer[i]);
        fprintf(dump_file, "\n");
    }
    fprintf(dump_file,"Car - %d\nSTACK:\n", cpu->car);

    print_stack(&cpu->stk, dump_file);
}

void cpu_init(CPU* cpu) {
    cpu->car = 0;

    cpu->comand_buffer = nullptr;
    cpu->memory        = nullptr;

    cpu->rax = 0;
    cpu->rbx = 0;
    cpu->rcx = 0;
    cpu->rdx = 0;
    
    STK_CTOR(&cpu->stk);
}

void cpu_dtor(CPU* cpu) {
    cpu->car = -1;

    cpu->comand_buffer = nullptr;
    cpu->memory        = nullptr;

    cpu->rax = -1;
    cpu->rbx = -1;
    cpu->rcx = -1;
    cpu->rdx = -1;
    
    stack_dtor(&cpu->stk);
}


int read_comands(CPU* cpu, const char * FileName) {
    FILE* binary;
    binary = fopen(FileName, "rb");

    if (binary == NULL)
    {
        printf("invalid command file name");
        return -1;
    }

    struct stat FileData;
    stat(FileName, &FileData);

    cpu->com_buffer_size = FileData.st_size;
    cpu->comand_buffer = (char*)calloc(FileData.st_size, sizeof(char));

    fread(cpu->comand_buffer, sizeof(char), FileData.st_size, binary);
    return 0;
}

void do_comands(CPU* cpu) {
    while(true) {
        switch(cpu->comand_buffer[cpu->car]){
            case ADD:
                comand_add(cpu);
                break;
            case MUL:
                comand_mul(cpu);
                break;
            case PUSH:
                comand_push(cpu);
                break;
            case POP:
                comand_pop(cpu);
                break;
            case RPUSH:
                comand_rpush(cpu);
                break;
            case RPOP:
                comand_rpop(cpu);
                break;
            case OUT:
                comand_out(cpu);
                break;
            case DIV:
                comand_div(cpu);
                break;
            case COS:
                comand_cos(cpu);
                break;
            case SIN:
                comand_sin(cpu);
                break;
            case SUP:
                comand_sup(cpu);
                break;
            case SQRT:
                comand_sqrt(cpu);
                break;
            case IN:
                comand_in(cpu);
                break;
            case HLT:
                return;
            case CALL:
                command_call(cpu);
                break;
            default:
                printf("ERROR WRONG COMMAND - %d", cpu->comand_buffer[cpu->car]);
                return;
        }
        //printf("%d[%d]\n", cpu->comand_buffer[cpu->car], cpu->car);
    }
}
