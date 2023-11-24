#ifndef CPU_COMANDS_INCLUDED
#define CPU_COMANDS_INCLUDED
#include "processor.h"

void comand_add (CPU* cpu);
void comand_out (CPU* cpu);
void comand_mul (CPU* cpu);
void comand_div (CPU* cpu);
void comand_sin (CPU* cpu);
void comand_cos (CPU* cpu);
void comand_sup (CPU* cpu);
void comand_sqrt(CPU* cpu);
void comand_in  (CPU* cpu);
void comand_pop (CPU* cpu);
void comand_push(CPU* cpu);
void comand_rpop (CPU* cpu);
void comand_rpush(CPU* cpu);
void comand_call(CPU* cpu, Stack* function_stack);
void comand_ret(CPU* cpu, Stack* function_stack);
void comand_je(CPU* cpu);
void comand_jbe(CPU* cpu);

#endif