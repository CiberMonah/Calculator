#include "stack.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* source = nullptr;
    
    if ((source = fopen("proc_dump.txt", "w")) == NULL) {
        printf("File reading error");
        return 1;
    }

    CPU cpu = {};
    
    cpu_init(&cpu);

    read_comands(&cpu, "binary.bin");

    CPU_DUMP(&cpu, source);

    cpu_dtor(&cpu);

    fclose(source);
}