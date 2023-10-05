#include "stack.h"
#include <inttypes.h>

const int MIN_CAPACITY = 5;
const int POISON = 12321;

// static void print_int_stack(Stack *stk) {
//     for(int i = 0; i < stk->capacity; i++) {
//         if(stk->data[i] == VOID_ELEM)
//             printf("[%d] = (void)\n", i);
//         else
//             printf("[%d] = %d\n", i, stk->data[i]);
//     }
// }



static stack_error_type check_canaries(Stack* stk) {
    if(stk->left_canary == LEFT_PARROT && stk->right_canary == RIGHT_PARROT)
        return NO_ERR;

    return STACK_CANARY_ERR;
}

static stack_error_type hash_checker(Stack* stk) {

    // printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // printf("%s:Hasher: %lu\n", __PRETTY_FUNCTION__, hasher(stk));

    if(stk->hash == hasher(stk)) {
        return NO_ERR;
    }
    // printf("Hash - %lu Real - %lu in hash checker\n", stk->hash, hasher(stk));
    return STACK_HASH_ERR;
}

 int stack_verificator(Stack* stk) {
    int counter = 0;
    // printf("%s:Hash stk ver: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // printf("%s:Hasher stk ver: %lu\n", __PRETTY_FUNCTION__, hasher(stk));
    assert(stk != NULL);
    
    if (stk->is_exist == 0) {
        put_error(stk, STACK_IS_NOT_EXIST);
        STK_DUMP(stk);
        abort();
        counter++;
        //stk->hash = hasher(stk);
    } else if (stk->capacity < 0 || stk->size > stk->capacity) {
        put_error(stk, STACK_SIZE_ERR);
        counter++;
        //stk->hash = hasher(stk);
    } else if (stk->data == NULL) {
        put_error(stk, MEM_ALLOC_ERR);
        counter++;
        //stk->hash = hasher(stk);
    } else if(hash_checker(stk) != NO_ERR) {
        put_error(stk, STACK_HASH_ERR);
        counter++;
        //stk->hash = hasher(stk);
    } else if(check_canaries(stk) != NO_ERR) {
        put_error(stk, STACK_CANARY_ERR);
        counter++;
        //stk->hash = hasher(stk);
    } else if(stk->size < 0) {
        put_error(stk, OUT_OF_INDEX_ERR);
        counter++;
        //stk->hash = hasher(stk);
    }

    return counter;
}

static stack_error_type stack_resize_capacity(Stack* stk) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }

    Elem_t* temp = NULL;

    if ((stk->size == stk->capacity / 2 - 1) && (stk->capacity / 2 >= MIN_CAPACITY)) {
        temp = (Elem_t*)realloc(stk->data, stk -> capacity  / 2 * sizeof(Elem_t));
        if(temp == NULL)
            return MEM_ALLOC_ERR;
        stk->data = temp;
        stk->capacity = stk->capacity /  2;
    } else if(stk->size == stk->capacity - 1) {
        temp = (Elem_t*)realloc(stk->data, stk->capacity * 2 * sizeof(Elem_t));
        if(temp == NULL)
            return MEM_ALLOC_ERR;
        stk->data = temp;
        for(int i = 0; i < stk->size + 2; i++)
            stk->data[stk->size  + i] = VOID_ELEM;
        stk->capacity *= 2;
    }

    stk->hash = hasher(stk);
    return NO_ERR;
}

stack_error_type stack_ctor(Stack* stk, const char* name, int line, const char* func, const char* file) {
    // printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // printf("sizeof(Stack): %u\n", sizeof(Stack));
    // for (size_t i = 0; i < sizeof(Stack) / sizeof(uint32_t); i++)
    // {
    //     printf("%u:%x ", i, ((uint32_t*)(stk))[i]);
    // }
    // printf("\n");

    if(stk == NULL || name == NULL || func == NULL || file == NULL)
        return NULL_PTR_ERR;
    if(stk->is_exist == 1) 
        return CRITICAL_ERR;
    stk->is_exist  = 1;
    stk->capacity  = MIN_CAPACITY;
    stk->size      = 0;

    stk->name      = name;
    stk->line      = line;
    stk->file_name = file;
    stk->func_name = func;

    stk->data = (Elem_t*)calloc(MIN_CAPACITY, sizeof(Elem_t));
    if(stk->data == NULL)
        return MEM_ALLOC_ERR;
    for(int i = 0; i < stk->capacity; i++)
        stk->data[i] = VOID_ELEM;
    stk->hash = hasher(stk);
    // printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // printf("%s:Hasher: %lu\n", __PRETTY_FUNCTION__, hasher(stk));

    return NO_ERR;
}

stack_error_type stack_dtor(Stack* stk) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }
    stk->is_exist = 0;
    stk->size = POISON;
    stk->capacity = POISON;
    free(stk->data);

    return NO_ERR;
}

stack_error_type stack_push(Stack* stk, Elem_t value) {
    //printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // for (size_t i = 0; i < sizeof(Stack) / 4; i++)
    // {
    //     printf("%x ", ((uint32_t*)(stk))[i]);
    // }
    //printf("\n");
    // printf("%s:Hash: %lu\n", __PRETTY_FUNCTION__, stk->hash);
    // printf("%s:Hasher: %lu\n", __PRETTY_FUNCTION__, hasher(stk));

    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }

    stack_resize_capacity(stk);
    stk->data[stk->size] = value;
    stk->size += 1;

    stk->hash = hasher(stk);
    
    return NO_ERR;
}

stack_error_type stack_pop(Stack* stk, Elem_t* poped) {
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }

    stk->size--;
    stk->hash = hasher(stk);
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }

    *poped = stk->data[(stk->size)];
    stk->data[(stk->size)] = VOID_ELEM;
    stk->hash = hasher(stk);
    if(stack_verificator(stk) != 0) {
        if(check_error(stk) == 1) {
            STK_DUMP(stk);
            abort();
        }
    }
    if(stack_resize_capacity(stk) == NO_ERR) {
        return NO_ERR;
    }

    return CRITICAL_ERR;
}

static stack_error_type error_show(Stack* stk) {
    int tmp = stk->errors;

    if(tmp & MEM_ALLOC_ERR)
        printf("Memory allocation error\n");
    if (tmp & NULL_PTR_ERR)
        printf("Null ptr error\n");
    if (tmp & OUT_OF_INDEX_ERR)
        printf("Out of index error\n");
    if (tmp & STACK_IS_NOT_EXIST)
        printf("Stack is not exist\n");
    if (tmp & CRITICAL_ERR)
        printf("Critical error\n");
    if (tmp & STACK_CANARY_ERR)
        printf("Stack canary error\n");
    if (tmp & STACK_SIZE_ERR)
        printf("Stack size error\n");
    if (tmp & STACK_HASH_ERR)
        printf("Stack hash error\n"
        "expected - %lu hash - %lu\n", stk->hash, hasher(stk));
    return NO_ERR;     //drugie bity 1 prover
}

stack_error_type stack_dump(Stack* stk, const char* file, const char* func, const int line) {
    printf("Dump called in file - %s function  - %s on line - %d\n", file, func, line);
    if(stk->is_exist == 0) {
        printf("Stack is not exist\n");
        return STACK_IS_NOT_EXIST;
    } else {
        printf("\nPointer on stack named(%s)- %p\n", stk->name, stk);
        printf("Created in file - %s in function - %s on line - %d\n", stk->file_name, stk->func_name, stk->line);
        printf("Pointer on data - %p\n", stk->data);
        printf("Capacity of stack - %d\n", stk->capacity);
        printf("Size - %d\n", stk->size);
        printf("Hash = %lu\n", stk->hash);
        printf("Errors:\n");
        error_show(stk);
        printf("\n");

        for(int i = 0; i < stk->capacity; i++) {
            if(stk->data[i] == VOID_ELEM)
                printf("[%d] = (void)\n", i);
            else
                printf("[%d] = %d\n", i, stk->data[i]);
        }

        return NO_ERR;
    }

    assert(0 && "fallthrough");
}

stack_error_type print_stack(Stack* stk) {
    for(int i = 0; i < stk->capacity; i++) {
        if(stk->data[i] == VOID_ELEM)
            printf("[%d] = (void)\n", i);
        else
            printf("[%d] = %d\n", i, stk->data[i]);
    }
    return NO_ERR;
}

stack_error_type print_error(stack_error_type error) {
    if(error == MEM_ALLOC_ERR) {
        printf("Memory allocation error\n");
        return error;
    } else if(error == NULL_PTR_ERR) {
        printf("Pointer is Null\n");
        return error;
    } else if(error == OUT_OF_INDEX_ERR) {
        printf("Index is out of range\n");
        return error;
    } else if(error == STACK_IS_NOT_EXIST) {
        printf("Stack is not exist\n");
        return error;
    } else if(error == STACK_HASH_ERR) {
        printf("Hash error\n");
        return error;
    }

    return NO_ERR;
}

stack_error_type put_error(Stack* stk, stack_error_type error) {
    if(stk == NULL)
        return NULL_PTR_ERR;
    if(stk->is_exist == 0) {
        stk->errors |= STACK_IS_NOT_EXIST;
        STK_DUMP(stk);
        abort();
    }
    stk->errors |= error;
    //stk->hash = hasher(stk);

    return NO_ERR;
}

unsigned long hasher (Stack* stk) {
    unsigned long hash = 0;
    //if we make stk->hash = 0; so we can return new value of hash and rewright stk->hash
    //because in we will rewright stk->hash to new_hash and compare it wis new hash (always true)
    //printf("sizeof stack%p - %d\n", stk,  sizeof(Stack));
    unsigned long hash_data = 0;
    unsigned long old_hash = stk->hash;
    stk->hash = 0;

    for(int i = 0; i < stk->capacity - 1; i++) {
        hash_data += (*(char*)((char*)stk + i)) % 7 + ((*(char*)((char*)stk + i + 1)))  % 9;
    }

    for(unsigned int i = 0; i < sizeof(Stack) - 1; i++) { 
        //printf("%s: i: %u\n", __PRETTY_FUNCTION__, i);
        //printf("first number %p - %d\n", (char*)stk + i, *(unsigned char*)((char*)stk + i));
        //printf("second number %p - %d\n",(char*)stk + i + 1, *(unsigned char*)((char*)stk + i + 1));
        hash += (*(char*)((char*)stk + i)) % 7 + ((*(char*)((char*)stk + i + 1)))  % 9;
        //printf("%lu\n", hash);
    }

    stk->hash = old_hash ;

    return hash + hash_data;
}

int check_error (Stack* stk) {
    if(stk == NULL) {
        put_error(stk, NULL_PTR_ERR);
        printf("Cant detect because stk is nullptr\n");

        return 1;
    }
    if(stk->is_exist == 0) {
        put_error(stk, STACK_IS_NOT_EXIST);
        printf("Cant detect because stk is not exist\n");

        return 1;
    }

    int tmp = stk->errors >> 1;

    if (tmp == 0)
        return 0;
    else
        return 1;
}

void execution(Stack* stk) {
    //char* left_executor = (char*)stk;
    //char* right_executor = (char*)stk + stk->capacity - 1;

    //destroy canaries
    // *(left_executor + 2) = 21;
    // *(right_executor - 2) = 21;
    printf("Destroing...\n");
    for(int i = 0; i < 10; i++){
        stack_push(stk, rand() % 100);
    }

    printf("Destroy finished\n");
    // for(int i = 0; i < stk->capacity; i++) { //to trash stack
    //     *(left_executor + rand() % stk->capacity) = *(left_executor + rand() % stk->capacity) + 1;
        
    // }
}