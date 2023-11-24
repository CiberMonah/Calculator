#include "stack.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* source = nullptr;
    
    if ((source = fopen("binary.bin", "rb")) == NULL) {
        printf("File reading error");
        return 1;
    }

    CPU cpu = {};
    
    cpu_init(&cpu);

    read_comands(&cpu, "binary.bin");

    do_comands(&cpu);

    CPU_DUMP(&cpu, source);

    cpu_dtor(&cpu);

    fclose(source);
}