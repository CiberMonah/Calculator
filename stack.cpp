#include "stack.h"
#include <inttypes.h>

const int MIN_CAPACITY = 5;

static stack_error_type check_canaries(Stack* stk) {
    if(stk->left_canary == LEFT_PARROT && stk->right_canary == RIGHT_PARROT)
        return STACK_NO_ERR;

    return STACK_CANARY_ERR;
}

static stack_error_type hash_checker(Stack* stk) {
    if(stk->hash == hasher(stk)) {
        return STACK_NO_ERR;
    }
    return STACK_HASH_ERR;
}

static stack_error_type void_elem_checker(Stack* stk) {
    for(int i = stk->size; i < stk->capacity; i++) {
        if(stk->data[i] != VOID_ELEM) 
            return STACK_NO_VOID_ELEM_ERR;
    }
    return STACK_NO_ERR;
}
 int stack_verificator(Stack* stk) {
    int counter = 0;
    assert(stk != NULL);
    
    put_error(stk, void_elem_checker(stk));

    if (stk->is_exist == 0) {
        put_error(stk, STACK_IS_NOT_EXIST);
        STK_DUMP(stk);
        return STACK_VERIFICATION_ERR;
        counter++;
    } else if (stk->capacity < 0 || stk->size > stk->capacity) {
        put_error(stk, STACK_SIZE_ERR);
        counter++;
    } else if (stk->data == NULL) {
        put_error(stk, STACK_MEM_ALLOC_ERR);
        counter++;
    } else if(hash_checker(stk) != STACK_NO_ERR) {
        put_error(stk, STACK_HASH_ERR);
        counter++;
    } else if(check_canaries(stk) != STACK_NO_ERR) {
        put_error(stk, STACK_CANARY_ERR);
        counter++;
    } else if(stk->size < 0) {
        put_error(stk, STACK_OUT_OF_INDEX_ERR);
        counter++;
    }
    return counter;
}

static stack_error_type stack_resize_capacity(Stack* stk) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
        }
    }

    Elem_t* temp = NULL;
    

    if ((stk->size == stk->capacity / CAPACITY_MULTIPLIER - CAPACITY_GISTERESIS - 1) && (stk->capacity / CAPACITY_MULTIPLIER>= MIN_CAPACITY)) {
        temp = (Elem_t*)realloc(stk->data, stk -> capacity  / CAPACITY_MULTIPLIER * sizeof(Elem_t) - CAPACITY_GISTERESIS);
        if(temp == NULL)
            return STACK_MEM_ALLOC_ERR;
        stk->data = temp;
        stk->capacity = stk->capacity / CAPACITY_MULTIPLIER;
        stk->hash = hasher(stk);
        return STACK_NO_ERR;
    } else if(stk->size == stk->capacity - 1) {
        temp = (Elem_t*)realloc(stk->data, stk->capacity * CAPACITY_MULTIPLIER * sizeof(Elem_t));
        if(temp == NULL)
            return STACK_MEM_ALLOC_ERR;
        stk->data = temp;
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = VOID_ELEM;
        stk->capacity *= CAPACITY_MULTIPLIER;
        stk->hash = hasher(stk);
        return STACK_NO_ERR;
    }
    return STACK_NO_ERR;
}

stack_error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file) {
    if(stk == NULL || name == NULL || func == NULL || file == NULL)
        return STACK_NULL_PTR_ERR;
    if(stk->is_exist == 1) 
        return STACK_IS_NOT_EXIST;
    stk->is_exist  = 1;
    stk->capacity  = MIN_CAPACITY;
    stk->size      = 0;
    stk->errors    = STACK_NO_ERR;

    stk->name      = name;
    stk->line      = line;
    stk->file_name = file;
    stk->func_name = func;

    stk->data = (Elem_t*)calloc(MIN_CAPACITY, sizeof(Elem_t));
    if(stk->data == NULL)
        return STACK_MEM_ALLOC_ERR;
    for(int i = 0; i < stk->capacity; i++)
        stk->data[i] = VOID_ELEM;
    stk->hash = hasher(stk);

    return STACK_NO_ERR;
}

stack_error_type stack_dtor(Stack* stk) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
        }
    }
    stk->is_exist = 0;
    stk->size = VOID_ELEM;
    stk->capacity = VOID_ELEM;
    free(stk->data);

    return STACK_NO_ERR;
}

stack_error_type stack_push(Stack* stk, Elem_t value) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
            abort();
        }
    }

    stack_resize_capacity(stk);
    stk->data[stk->size] = value;
    stk->size += 1;

    stk->hash = hasher(stk);
    
    return STACK_NO_ERR;
}

stack_error_type stack_pop(Stack* stk, Elem_t* poped) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
        }
    }
    
    *poped = stk->data[(stk->size) - 1];
    stk->data[(stk->size) - 1] = VOID_ELEM;
    stk->size--;
    stk->hash = hasher(stk);

    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
        }
    }

    stack_error_type error = stack_resize_capacity(stk);
    put_error(stk, error);

    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            return STACK_VERIFICATION_ERR;
        }
    }
    if(error == STACK_NO_ERR) {
        return STACK_NO_ERR;
    }

    assert(0 && "fallthrough");
    return STACK_VERIFICATION_ERR;
}

static stack_error_type error_show(Stack* stk) {
    int tmp = stk->errors;

    if(tmp & STACK_MEM_ALLOC_ERR)
        printf("Memory allocation error\n");
    if(tmp & STACK_NULL_PTR_ERR)
        printf("Null ptr error\n");
    if(tmp & STACK_OUT_OF_INDEX_ERR)
        printf("Out of index error\n");
    if(tmp & STACK_IS_NOT_EXIST)
        printf("Stack is not exist\n");
    if(tmp & STACK_CANARY_ERR)
        printf("Stack canary error\n");
    if(tmp & STACK_SIZE_ERR)
        printf("Stack size error\n");
    if(tmp & STACK_HASH_ERR)
        printf("Stack hash error\n"
        "expected - %lu hash - %lu\n", stk->hash, hasher(stk));
    if(tmp & STACK_VERIFICATION_ERR)
        printf("Verification error\n");
    if(tmp & STACK_NO_VOID_ELEM_ERR)
        printf("Void element is not void_elem\n");
    return STACK_NO_ERR;
}



stack_error_type stack_dump(Stack* stk, bool only_data, const char* file, const char* func, const int line) {
    printf("Dump called in file - %s function  - %s on line - %d\n", file, func, line);
    if(stk->is_exist == 0) {
        printf("Stack is not exist\n");
        return STACK_IS_NOT_EXIST;
    } else {
        if (!only_data)
        {
            printf("\nPointer on stack named(%s)- %p\n", stk->name, stk);
            printf("Created in file - %s in function - %s on line - %d\n", stk->file_name, stk->func_name, stk->line);
            printf("Pointer on data - %p\n", stk->data);
            printf("Capacity of stack - %d\n", stk->capacity);
            printf("Size - %d\n", stk->size);
            printf("Hash = %lu\n", stk->hash);
            printf("Errors:\n");
            error_show(stk);
            printf("\n");
        }

        for(int i = 0; i < stk->capacity; i++) {
            if(stk->data[i] == VOID_ELEM)
                printf("[%d] = (void)\n", i);
            else
                printf("[%d] = %d\n", i, stk->data[i]);
        }

        return STACK_NO_ERR;
    }

    assert(0 && "fallthrough");
}

stack_error_type print_stack(Stack* stk, FILE* fp) {
    for(int i = 0; i < stk->capacity; i++) {
        if(stk->data[i] == VOID_ELEM)
            fprintf(fp, "[%d] = (void)\n", i);
        else
            fprintf(fp, "[%d] = %d\n", i, stk->data[i]);
    }
    return STACK_NO_ERR;
}

// static stack_error_type print_error(FILE* dumpfile, stack_error_type error) {
//     if(error == STACK_MEM_ALLOC_ERR) {
//         fprintf(dumpfile, "Memory allocation error\n");
//         return error;
//     } else if(error == STACK_NULL_PTR_ERR) {
//         fprintf(dumpfile, "Pointer is Null\n");
//         return error;
//     } else if(error == STACK_OUT_OF_INDEX_ERR) {
//         fprintf(dumpfile, "Index is out of range\n");
//         return error;
//     } else if(error == STACK_IS_NOT_EXIST) {
//         fprintf(dumpfile, "Stack is not exist\n");
//         return error;
//     } else if(error == STACK_HASH_ERR) {
//         fprintf(dumpfile, "Hash error\n");
//         return error;
//     } else if(error == STACK_NO_VOID_ELEM_ERR) {
//         fprintf(dumpfile, "Not all void elems have NO_ELEM value\n");
//     }

//     return STACK_NO_ERR;
// }

stack_error_type put_error(Stack* stk, stack_error_type error) {
    assert(stk->is_exist == 1);
    stk->errors |= error;

    return STACK_NO_ERR;
}

long hasher (Stack* stk) {
    unsigned long hash = 0;
    unsigned long hash_data = 0;
    unsigned long old_hash = stk->hash;
    stk->hash = 0;

    for(int i = 0; i < stk->capacity; i++) {
        hash_data += (*(char*)((char*)stk + i)) % 11;
    }

    for(unsigned int i = 0; i < sizeof(Stack); i++) { 
        hash += (*(char*)((char*)stk + i)) % 11;
    }

    stk->hash = old_hash ;

    return hash + hash_data;
}

bool check_error(Stack* stk) {
    if(stk == NULL) {
        put_error(stk, STACK_NULL_PTR_ERR);
        printf("Cant detect because stk is nullptr\n");

        return 1;
    }
    if(stk->is_exist == 0) {
        put_error(stk, STACK_IS_NOT_EXIST);
        printf("Cant detect because stk is not exist\n");

        return 1;
    }

    if (stk->errors == STACK_NO_ERR)
        return 0;
    else
        return 1;
}