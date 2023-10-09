#include "commons.h"
#include <string.h>
#include <assert.h>


void disassembler(FILE* inf, FILE* outf);

void disassembler(FILE* inf, FILE* outf) {
    printf("Starting disassembler\n");
    
    int command  = 0, number = 0;

    while(fscanf(inf, "%d", &command) != EOF) {
        switch(command) {
            case IN: 
                fprintf(outf, "in\n");
                break;
            case PUSH:
                fscanf(inf, "%d", &number);
                fprintf(outf, "push %d\n", number);
                break;
            case POP:
                fprintf(outf, "pop\n");
                break;
            case ADD:
                fprintf(outf, "add\n");
                break;
            case DIV:
                fprintf(outf, "div\n");
                break;
            case MUL:
                fprintf(outf, "mul\n");
                break;
            case SUP:
                fprintf(outf, "sup\n");
                break;
            case HLT: 
                fprintf(outf, "hlt\n");
                break;
            case SQRT:
                fprintf(outf, "sqrt\n");
                break;
            case SIN:
                fprintf(outf, "sin\n");
                break;
            case COS:
                fprintf(outf, "cos\n");
                break;
            case OUT:
                fprintf(outf, "out\n");
                break;
            default:
                printf("Wrong command: %d\n", command);
                assert(0);
                break;
        }
    }
    printf("Disassembler finished\n");
}


int main(void) {
    FILE* in = nullptr;
    FILE* out = nullptr;

    if ((in = fopen("bytecode.txt", "r")) == NULL) {
        printf("File reading error");
        return 1;
    }

    if ((out = fopen("source.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    disassembler(in, out);

    fclose(in);
    fclose(out);
}