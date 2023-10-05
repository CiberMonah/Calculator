#include "commons.h"
#include <string.h>
#include <assert.h>


void disassembler(FILE* inf, FILE* outf);

void disassembler(FILE* inf, FILE* outf) {
    printf("Starting disassembler\n");
    
    int command  = 0, number = 0;

    while(fscanf(inf, "%d", &command) != EOF) {
        switch(command) {
            case in: 
                fprintf(outf, "in\n");
                break;
            case push:
                fscanf(inf, "%d", &number);
                fprintf(outf, "push %d\n", number);
                break;
            case pop:
                fprintf(outf, "pop\n");
                break;
            case add:
                fprintf(outf, "add\n");
                break;
            case div_:
                fprintf(outf, "div\n");
                break;
            case mul:
                fprintf(outf, "mul\n");
                break;
            case sup:
                fprintf(outf, "sup\n");
                break;
            case hlt: 
                fprintf(outf, "hlt\n");
                break;
            case sqrt_:
                fprintf(outf, "sqrt\n");
                break;
            case sin_:
                fprintf(outf, "sin\n");
                break;
            case cos_:
                fprintf(outf, "cos\n");
                break;
            case out:
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