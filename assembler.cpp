#include "commons.h"
#include <string.h>
#include <assert.h>
#include "assembler.h"
#include "processor.h"
#include "stack.h"
#include <stdlib.h>

LABEL LABELS[NUMBER_OF_LABELS] = {};

static cpu_error_type ctor_op(CPU_OP* operation) {
    operation->name = "";
    operation->com_id = WRONG_COMMAND;
    operation->argn = 0;

    for(int i = 0; i < MAX_ARGN; i++) {
        operation->cpu_argv[i] = POISON_VALUE;
    }

    return CPU_NO_ERR;
}


// static cpu_error_type dtor_op(CPU_OP* operation) {
//     operation->com_id = WRONG_COMMAND;
//     operation->argn = -1;

//     for(int i = 0; i < MAX_ARGN; i++) {
//         operation->cpu_argv[i] = POISON_VALUE;
//     }

//     return CPU_NO_ERR;
// }

static cpu_error_type get_arg(FILE* inf, cpu_arguments argt, cpu_registers* reg, Elem_t* argv, char* lbl) {
    char* str = (char*)calloc(3, sizeof(char));
    if(str == nullptr)
        return CPU_MEM_ALLOC_ERR;

    if(argt == N) {
        if(fscanf(inf, "%d", argv) == 0)
            return CPU_WRONG_ARGUMENT_ERR;
        else 
            return CPU_NO_ERR;
    }
    if (argt == R) {
        fscanf(inf, "%s", str);
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
        if(fscanf(inf, "%d", argv) == 1) {
            return CPU_NO_ERR;
        } else {
            fscanf(inf, "%s", str);
            if      (strcmp(str, "rax") == 0) {
                (*reg) = RAX;
                free(str);
                return CPU_NO_ERR;
            } else if (strcmp(str, "rbx") == 0) {
                (*reg) = RBX;
                free(str);
                return CPU_NO_ERR;
            } else if (strcmp(str, "rcx") == 0) {
                (*reg) = RCX;
                free(str);
                return CPU_NO_ERR;
            } else if (strcmp(str, "rdx") == 0) {
                (*reg) = RDX;
                free(str);
                return CPU_NO_ERR;
            } else {
                free(str);
                return CPU_WRONG_REGISTER_ERR;
            }
        free(str);
        return CPU_WRONG_ARGUMENT_ERR;
        }
    } else if(argt == L) {
        fscanf(inf, "%s", lbl);
    }
    free(str);
    return CPU_NO_ERR;
}

// Premature optimization is the root of all evil (c)

static int get_comment(char* str, FILE* source) {
    if(str[0] == '#'){
        char comment[100] = "";
        fgets(comment, 100, source);
        return 1;
    }
    else    
        return 0;
}


int ptr_lbl = 0;

static int get_label(char* str, int* ptr) {                  //Parse command and look number of arguments;
    int k = 0;

    if(ptr == nullptr) {         //to detect labels in reading comands
        while(str[k] != ':' && str[k] != '\n' && str[k] != '\0') 
            k++;                     
        if(str[k] == ':') 
            return 1;
        else 
            return 0;
    }

    int i = 0;

    //printf("%lld\n", sizeof(ALL_COMMANDS) / sizeof(ALL_COMMANDS[0]));
    //printf("Command - %s\n", str);
    for(size_t m = 0; m < sizeof(ALL_COMMANDS) / sizeof(ALL_COMMANDS[0]); m++) {
        if(!ALL_COMMANDS[m].name) 
            break;
        if(strncmp(str, ALL_COMMANDS[m].name, 3) == 0) {
            *ptr += ALL_COMMANDS[m].argn;
            //printf("Command - %s Num of args - %d\n", ALL_COMMANDS[m].name, ALL_COMMANDS[m].argn);
        }
    } 

    

    if(str[0] == '\n' || str[0] == '#') return 1;
    while(str[i] != ':' && str[i] != '\n' && str[i] != '\0') i++;                     
    if(str[i] == ':')  {
        int j = i;
        while(str[j] != '\n' && str[j] != '\0')
            j++;
        str[j] = '\0';

        LABELS[ptr_lbl].name = strdup(str + 1 + i);        

        LABELS[ptr_lbl].ptr  = *ptr;      

        ptr_lbl++;

        return 1;
    }
    return -1;
}

static void get_all_labels(FILE* source_file) {
    char str[100] = "";
    int ptr = 0;

    while(fgets(str, 100, source_file) != NULL) {
        if(get_label(str, &ptr) == 1) ptr--;
        ptr++;
    }

    rewind(source_file);
}

static cpu_commands_id get_command(FILE* inf, char** command) {
    *command = (char*)calloc(MAX_LENGTH_OF_CMD, sizeof(char));        //ALLOC memory for new pointer to name

    if(fscanf(inf, "%s", *command) == EOF)
        return WRONG_COMMAND;
    if(strcmp(*command, "in") == 0) {
        return IN;
    } else if(strcmp(*command, "push") == 0) {
        return PUSH;
    } else if(strcmp(*command, "pop") == 0)  {
        return POP;
    } else if(strcmp(*command, "add") == 0) {
        return ADD;
    } else if(strcmp(*command, "div") == 0) {
        return DIV;
    } else if(strcmp(*command, "mul") == 0) {
        return MUL;
    } else if(strcmp(*command, "sup") == 0) {
        return SUP;
    } else if(strcmp(*command, "hlt") == 0) {
        return HLT;
    } else if(strcmp(*command, "sqrt") == 0) {
        return SQRT;
    } else if(strcmp(*command, "sin") == 0) {
        return SIN;
    } else if(strcmp(*command, "cos") == 0) {
        return COS;
    } else if(strcmp(*command, "out") == 0) {
        return OUT;
    } else if(strcmp(*command, "rpush") == 0) {
        return RPUSH;
    } else if(strcmp(*command, "rpop") == 0) {
        return RPOP;
    } else if(strcmp(*command, "jmp") == 0) {
        return JMP;
    } else if (get_label(*command, nullptr) == 1) {
        return LBL;
    } else if (strcmp(*command, "call") == 0) {
        return CALL;
    } else if (strcmp(*command, "ret") == 0) {
        return RET;
    } else {
        return WRONG_COMMAND;
    }
    free(command);
}

static cpu_error_type read_commands(FILE* inf, const CPU_OP* operations, CPU_OP** op_buffer, int* number_of_lines) {
    int counter = 0;
    char* command = nullptr;
    char lbl[100] = "";

    cpu_error_type err = CPU_NO_ERR;
    cpu_commands_id command_id = get_command(inf, &command);

    if(get_comment(command, inf) == 1) 
        command_id = LBL;           //ignore this string

    while(command_id != WRONG_COMMAND) {
        op_buffer[counter]->name        = command;
        op_buffer[counter]->com_id      = command_id;
        op_buffer[counter]->argn        = operations[command_id].argn;
        

        for(int i = 0; i < operations[command_id].argn; i++) { 
            err = get_arg(inf, operations[command_id].cpu_argvt[i], op_buffer[counter]->cpu_regv, &op_buffer[counter]->cpu_argv[i], lbl);
        }

        if(command_id == LBL) 
            counter--;

        if(operations[command_id].cpu_argvt[0] == L) {
            for(int i = 0; i < NUMBER_OF_LABELS; i++) {
                // printf("%s - %s\n", LABELS[i].name, lbl);
                if(strcmp(LABELS[i].name, lbl) == 0) {
                    op_buffer[counter]->cpu_argv[0] = LABELS[i].ptr;
                    break;
                }
            }
        }

        if(op_buffer[counter]->cpu_argv[0] == POISON_VALUE && op_buffer[counter]->argn > 0 ) {
            if(command_id == PUSH) op_buffer[counter]->com_id = RPUSH;
            else if (command_id == RPUSH) op_buffer[counter]->com_id = RPOP;
        }
        if(err != CPU_NO_ERR)
            return err;
        

        counter++;

        command_id = get_command(inf, &command);

        if(get_comment(command, inf) == 1) 
            command_id = LBL;
    } 
    *number_of_lines = counter;
    return CPU_NO_ERR;
}

static cpu_error_type print_assemble_commands(FILE* outf, CPU_OP* op_buffer[NUMBER_OF_CMD], int number_of_lines, FILE* listing, FILE* binary) {
    cpu_error_type err = CPU_NO_ERR;

    for(int i = 0; i < number_of_lines; i++) {
        fprintf(outf, "%d ", op_buffer[i]->com_id);

        if(op_buffer[i]->argn > 0) {
            if(op_buffer[i]->cpu_argv[0] != POISON_VALUE) {                     //ЕСЛИ АРГУМЕНТ ЧИСЛО ТО ВЫВОДИ ЧИСЛА
                for(int j = 0; j < op_buffer[i]->argn; j++)
                    fprintf(outf, "%d ", op_buffer[i]->cpu_argv[j]);
            } else {
                for(int j = 0; j < op_buffer[i]->argn; j++)                     //ЕСЛИ АРГУМЕНТ РЕГСИТЕР ТО ВЫВОДИ РЕГИСТРЫ
                    fprintf(outf, "%d ", op_buffer[i]->cpu_regv[j]);
            }   
        }
        fprintf(outf, "\n");
    }

    if(listing != NULL) {
        fprintf(listing,     "|    id    |       name       |        code        |  arguments  |\n");
        for(int i = 0; i < number_of_lines; i++) {
            fprintf(listing, "    %*d      %*s                 %*d               ", 3 ,i, 10, op_buffer[i]->name, 3, op_buffer[i]->com_id);
            

            if(op_buffer[i]->argn > 0) {
                if(op_buffer[i]->cpu_argv[0] != POISON_VALUE) {                     //ЕСЛИ АРГУМЕНТ ЧИСЛО ТО ВЫВОДИ ЧИСЛА
                    for(int j = 0; j < op_buffer[i]->argn; j++)
                        fprintf(listing, "%d ", op_buffer[i]->cpu_argv[j]);
                    
                } else {
                    for(int j = 0; j < op_buffer[i]->argn; j++)                     //ЕСЛИ АРГУМЕНТ РЕГСИТЕР ТО ВЫВОДИ РЕГИСТРЫ
                        fprintf(listing, "%d ", op_buffer[i]->cpu_regv[j]);
                }
            }
            fprintf(listing, "\n");
        }
    }

    if(binary != NULL) {
        char buf[NUMBER_OF_CMD] = {};
        int k = 0;
        for(int i = 0; i < number_of_lines; i++) {
            buf[k] = op_buffer[i]->com_id;
            k++;
            if(op_buffer[i]->cpu_argv[0] != POISON_VALUE) {
                for(int j = 0; j < op_buffer[i]->argn; j++ ) {
                    buf[k] = (char)op_buffer[i]->cpu_argv[j];
                    k++;
                }
            } else {
                for(int j = 0; j < op_buffer[i]->argn; j++ ) {
                    buf[k] = (char)op_buffer[i]->cpu_regv[j];
                    k++;
                }
            }

        }
        fwrite(buf, sizeof(char), k, binary);
    }

    return err;
}



void assembler(FILE* inf, FILE* outf, FILE* log, FILE* binary) {
    printf("Starting assembler\n");
    int lines = 0;

    // If number of commands is not fixed, use calloc only.
    // If number is fixed, use static buffer and check if real number of commands in file is less than size of buffer.
    CPU_OP* commands[NUMBER_OF_CMD] = {};

    CPU_OP* buffer = (CPU_OP*)calloc(NUMBER_OF_CMD, sizeof(CPU_OP));    //create memory for commands

    for(int i = 0; i < NUMBER_OF_CMD; i++) {
        commands[i] = buffer + i;
    }

    for(int i = 0; i < NUMBER_OF_CMD; i++) {                            //Ctor of commands structs
        ctor_op(commands[i]);
    }

    read_commands(inf, ALL_COMMANDS, commands, &lines);

    // for(int i = 0; i < NUMBER_OF_CMD; i++) {    
    //                                                                      //print buf
    //     printf("COMMAND[%d]\nName: %s\nId: %d\n", i, commands[i]->name, commands[i]->com_id);
    // }

    print_assemble_commands(outf, commands, lines, log, binary);

    free(buffer);

    printf("Assembler finished\n");
}



int main(/*int argc, char *argv[]*/) {
    FILE* in = nullptr;
    FILE* out = nullptr;
    FILE* listing = nullptr;
    FILE* binary = nullptr;

    if ((in = fopen("source.src", "r")) == NULL) {
        printf("File reading error");
        return 1;
    }

    get_all_labels(in);

    // for(int i = 0; i < NUMBER_OF_LABELS; i++) {
    //     printf("NAME: %s PTR: %d\n", LABELS[i].name, LABELS[i].ptr);
    // }

    if ((out = fopen("bytecode.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    if ((listing = fopen("listing.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    if ((binary = fopen("binary.bin", "wb")) == NULL) {
        printf("File creating error");
        return 1;
    }

    assembler(in, out, listing, binary);

    fclose(binary);
    fclose(listing);
    fclose(in);
    fclose(out);
}