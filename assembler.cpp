#include "commons.h"
#include <string.h>
#include <assert.h>
#include "assembler.h"
#include "stack.h"
#include <stdlib.h>

static void print_command_info(FILE* stream, int command_id) {
    fprintf(stream, "command id: %d;\n", command_id);
    fprintf(stream, "Name: %s; number: of args %d\n", ALL_COMMANDS[command_id].name, ALL_COMMANDS[command_id].argn);
    if(ALL_COMMANDS[command_id].argn > 0) {
        fprintf(stream, "Argument types: ");
        for(int i = 0; i < ALL_COMMANDS[command_id].argn; i++) {
            fprintf(stream, "arg type elem[%d]: %d ", i, ALL_COMMANDS[command_id].cpu_argvt[i]);
        } fprintf(stream, "\n");
    }
}

// static cpu_error_type create_op(char* name, cpu_commands_id com_id, int argn, cpu_arguments arg_arr[], CPU_OP* operation) {
//     operation->name = name;
//     operation->com_id = com_id;
//     operation->argn = argn;
//     for(int i = 0; i < argn; i++)
//         operation->cpu_argvt[i] = arg_arr[i];
//     return CPU_NO_ERR;
// }

// static cpu_error_type create_reg(char* name, cpu_registers value, CPU_REG* reg) {
//     reg->name   = name;
//     reg->value  = value;

//     return CPU_NO_ERR;
// }

static cpu_error_type get_arg(FILE* inf, cpu_arguments argt, cpu_registers* reg, Elem_t* argv) {
    char* str = nullptr;
    printf("AAAAAAAa%d", argt);
    if(argt == N) {
        if(fscanf(inf, "%d", argv) == 0)
            return CPU_WRONG_ARGUMENT_ERR;
    } else if(argt == R) {
        if      (strcmp(str, "rax") == 0)
            (*reg) = RAX;
        else if (strcmp(str, "rbx") == 0)
            (*reg) = RBX;
        else if (strcmp(str, "rcx") == 0)
            (*reg) = RCX;
        else if (strcmp(str, "rdx") == 0)
            (*reg) = RDX;
        else 
            return CPU_WRONG_REGISTER_ERR;
    }
    if (argt == B) {
        printf("ZALUPA");
        if (fscanf(inf, "%d", argv) == 1);
        else if (fscanf(inf, "%s", str) == 1) {
            if      (strcmp(str, "rax") == 0)
                (*reg) = RAX;
            else if (strcmp(str, "rbx") == 0)
                (*reg) = RBX;
            else if (strcmp(str, "rcx") == 0)
                (*reg) = RCX;
            else if (strcmp(str, "rdx") == 0)
                (*reg) = RDX;
            else 
                return CPU_WRONG_REGISTER_ERR;
        }
        return CPU_WRONG_ARGUMENT_ERR;
    }
    
    return CPU_NO_ERR;
}

static int get_label(char* str, int ptr) {                          //6Lya IsPrAvb PZ
    if(str[0] == ':')  {
        LABELS[str[1] - '0'].name   = str[1] - '0';                 //DA-DA imya labela est ego nomer poka chto

        LABELS[str[1] - '0'].ptr    = ptr;                          //Kladem v ukazatel lablenomer kuda hotim tepnutsa
    }

    return -1;
}

static cpu_commands_id get_command(FILE* inf, char* command, int* ptr) {
    if(fscanf(inf, "%s", command) == EOF)
        return HLT;
    if (get_label(command, *ptr) != -1)
        return LBL;

    if(strcmp(command, "in") == 0) {
            return IN;
        } else if(strcmp(command, "push") == 0) {
            return PUSH;
        } else if(strcmp(command, "pop") == 0)  {
            return POP;
        } else if(strcmp(command, "add") == 0) {
            return ADD;
        } else if(strcmp(command, "div") == 0) {
            return DIV;
        } else if(strcmp(command, "mul") == 0) {
            return MUL;
        } else if(strcmp(command, "sup") == 0) {
            return SUP;
        } else if(strcmp(command, "hlt") == 0) {
            return HLT;
        } else if(strcmp(command, "sqrt") == 0) {
            return SQRT;
        } else if(strcmp(command, "sin") == 0) {
            return SIN;
        } else if(strcmp(command, "cos") == 0) {
            return COS;
        } else if(strcmp(command, "out") == 0) {
            return OUT;
        } else {
            return WRONG_COMMAND;
        }
}

static cpu_error_type read_commands(FILE* inf, const CPU_OP* operations, CPU_OP* op_buffer[NUMBER_OF_CMD], int* number_of_lines) {
    char command [MAX_LENGTH_OF_CMD] = "";
    int counter = 0;
    cpu_error_type err = CPU_NO_ERR;

    cpu_commands_id command_id = get_command(inf, command, &counter);
    print_command_info(stdout, command_id);
    while(command_id != HLT) {
        op_buffer[counter]->name = command;
        op_buffer[counter]->com_id = command_id;
        for(int i = 0; i < operations[command_id].argn; i++) {
            err = get_arg(inf, operations[command_id].cpu_argvt[i], op_buffer[counter]->cpu_regv, &op_buffer[counter]->cpu_argv[i]);
            printf("GET ARG\n");
        }
        if(err != CPU_NO_ERR)
            return err;
        command_id = get_command(inf, command, &counter);
        counter++;
    }

    *number_of_lines = counter;
    return CPU_NO_ERR;
}

static cpu_error_type print_assemble_commands(FILE* outf, CPU_OP* op_buffer[NUMBER_OF_CMD], int number_of_lines, FILE* listing) {
    cpu_error_type err = CPU_NO_ERR;

    for(int i = 0; i < number_of_lines; i++) {
        fprintf(outf, "%d", op_buffer[i]->com_id);

        for(int j = 0; j < op_buffer[i]->argn; j++)
            fprintf(outf, " %d", op_buffer[i]->cpu_argv[j]);
        fprintf(outf, "\n");
    }

    if(listing != NULL) {
        for(int i = 0; i < number_of_lines; i++) {
            fprintf(listing, "command:%s was assembled to code : %d\n", op_buffer[i]->name, op_buffer[i]->com_id);
            
            fprintf(listing, "Number of arguments: %d", op_buffer[i]->argn);

            for(int j = 0; j < op_buffer[i]->argn; j++)
                fprintf(outf, "Argument[%d]: %d\n", j, op_buffer[i]->cpu_argv[j]);
        }
    }

    return err;
}



void assembler(FILE* inf, FILE* outf, FILE* log) {
    printf("Starting assembler\n");
    int lines = 0;

    CPU_OP* commands[NUMBER_OF_CMD] = {};

    read_commands(inf, ALL_COMMANDS, commands, &lines);

    printf("Reading commands finished/n");

    print_assemble_commands(outf, commands, lines, log);

    printf("Assembler finished\n");
}



int main(/*int argc, char *argv[]*/) {
    FILE* in = nullptr;
    FILE* out = nullptr;
    FILE* listing = nullptr;

    if ((in = fopen("source.txt", "r")) == NULL) {
        printf("File reading error");
        return 1;
    }

    if ((out = fopen("listing.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    if ((listing = fopen("bytecode.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    assembler(in, out, listing);


    fclose(listing);
    fclose(in);
    fclose(out);
}