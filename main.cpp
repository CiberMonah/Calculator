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
            case ADD:
                command_add(&stk);
                break;
            case MUL:
                command_mul(&stk);
                break;
            case PUSH:
                fscanf(source, "%d", &number);
                command_push(&stk, number);
                break;
            case POP:
                command_pop(&stk, &number);
                number = 0;
                break;
            case OUT:
                command_out(&stk);
                break;
            case DIV:
                command_div(&stk);
                break;
            case COS:
                command_cos(&stk);
                break;
            case SIN:
                command_sin(&stk);
                break;
            case SUP:
                command_sup(&stk);
                break;
            case SQRT:
                command_sqrt(&stk);
                break;
            case IN:
                command_in(&stk);
                break;
            case HLT:
                return 0;
            default:
                printf("Command - %d is not exist\n", command);
                return 0;
        }
    }
    stack_dtor(&stk);
}