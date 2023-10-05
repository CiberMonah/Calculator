#include "commons.h"
#include <string.h>
#include <assert.h>


void assembler(FILE* inf, FILE* outf);

void assembler(FILE* inf, FILE* outf) {
    printf("Starting assembler\n");

    char command [5] = "";
    int number = 0;

    while(fscanf(inf, "%s", command) != EOF) {
        if(strcmp(command, "in") == 0) {
            fprintf(outf, "%d\n", in);
        } else if(strcmp(command, "push") == 0) {
            fscanf(inf, "%d", &number);
            fprintf(outf, "%d %d\n", push, number);
        } else if(strcmp(command, "pop") == 0)  {
            fprintf(outf, "%d\n", pop);
        } else if(strcmp(command, "add") == 0) {
            fprintf(outf, "%d\n", add);
        } else if(strcmp(command, "div") == 0) {
            fprintf(outf, "%d\n", div_);
        } else if(strcmp(command, "mul") == 0) {
            fprintf(outf, "%d\n", mul);
        } else if(strcmp(command, "sup") == 0) {
            fprintf(outf, "%d\n", sup);
        } else if(strcmp(command, "hlt") == 0) {
            fprintf(outf, "%d\n", hlt);
        } else if(strcmp(command, "sqrt") == 0) {
            fprintf(outf, "%d\n", sqrt_);
        } else if(strcmp(command, "sin") == 0) {
            fprintf(outf, "%d\n", sin_);
        } else if(strcmp(command, "cos") == 0) {
            fprintf(outf, "%d\n", cos_);
        } else if(strcmp(command, "out") == 0) {
            fprintf(outf, "%d\n", out);
        } else {
            printf("Wrong command: %s\n", command);
            assert(0);
        }
    }
    printf("Assembler finished\n");
}


int main(void) {
    FILE* in = nullptr;
    FILE* out = nullptr;

    if ((in = fopen("source.txt", "r")) == NULL) {
        printf("File reading error");
        return 1;
    }

    if ((out = fopen("bytecode.txt", "w")) == NULL) {
        printf("File creating error");
        return 1;
    }

    assembler(in, out);

    fclose(in);
    fclose(out);
}