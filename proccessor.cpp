#include "commons.h"
#include "processor.h"
#include <stdlib.h>
#include <stdio.h>




int main () {
    FILE* inf = nullptr;

    if ((inf = fopen("binary.bin", "wb")) == NULL) {
        printf("File creating error");
        return 1;
    }

    //init
    //do commands
    //delete



    fclose(inf);
}