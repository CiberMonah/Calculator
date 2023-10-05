#include "stack.h"
#include "commons.h"
#include "calculator.h"

int main(void) {
    Stack stk = {};
    FILE* source = nullptr;

    if ((source = fopen("bytecode.txt", "r")) == NULL) {
        printf("File reading error");
        return 1;
    }

    STK_CTOR(&stk);

    int command = 0;
    Elem_t number = 0;

    // printf("welcome to cuclus clan command - %d", command);

    while(get_command(source, &command)) {
        switch(command){
            case add:
                command_add(&stk);
                break;
            case mul:
                command_mul(&stk);
                break;
            case push:
                fscanf(source, "%d", &number);
                command_push(&stk, number);
                break;
            case pop:
                command_pop(&stk, &number);
                number = 0;
                break;
            case out:
                command_out(&stk);
                break;
            case div_:
                command_div(&stk);
                break;
            case cos_:
                command_cos(&stk);
                break;
            case sin_:
                command_sin(&stk);
                break;
            case sup:
                command_sup(&stk);
                break;
            case sqrt_:
                command_sqrt(&stk);
                break;
            case in:
                command_in(&stk);
                break;
            case hlt:
                return 0;
            default:
                printf("Command - %d is not exist\n", command);
                return 0;
        }
    }
    stack_dtor(&stk);
}