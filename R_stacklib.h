#ifndef R_STACKLIB_H
#define R_STACKLIB_H

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include "s_func.h"

// right bufbird replace, if u exchange capacity
// hash, resize, 

extern FILE* log_file;

const int BIRD_CONST = 228;

const int POISON54 = 1488;

enum type_of_error_with_stack
{
    NOT_STK_ERROR,
    STK_CALLOC_ERROR,
    STK_REALLOC_ERROR,
    STACK_OVERFLOW,
    SIZE_LESS_ZERO,
    CAPACITY_LESS_ZERO, 
    STK_DESTROYED,
    START_PTR_IS_NULL,
    LEFT_BIRD_DIED,
    RIGHT_BIRD_DIED,
    LEFT_BUFBIRD_DIED,
    RIGHT_BUFBIRD_DIED,
    MISMATCHED_HASH_STK,
    MISMATCHED_HASH_BUF,
    USE_POISENED_ELEM,
    TRY_POP_VOID_STK
};

enum modes_of_stackReSize
{
    EXPAND,
    REDUCE
};

//typedef int stk_elem_type; //you can exchange double for anything type
typedef int stk_elem_type; //you can exchange double for anything type
#define fomat_stk_elem %d //exchange specifier for ur type

struct stack
{
    const uint64_t r_stk_bird = BIRD_CONST;
    stk_elem_type *start_ptr;
    int size;
    int capacity;
    uint64_t hash_stk;
    uint64_t hash_buf;
    int cntrDtor;
    int error;
    const uint64_t l_stk_bird = BIRD_CONST;
}; 

void               stackCtor        (stack* stk, int cap);

void               stackPush        (stack *stk, stk_elem_type elem);

stk_elem_type      stackPop         (stack *stk);

void               stackReSize      (stack* stk, const int mode); // ebala sho pizdec

void               stackDtor        (stack *stk); 

void               stackCheck       (stack* stk, const char* func_name, const int line_num); 

void               stackDump        (stack *stk, const char* file_name, const char* func_name, const int line_num);

void               stackPrint       (stack* stk); //MENTOR HELP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void               stackPlaceCanary (stack* stk);

uint64_t           calc_hash_stk    (stack *stk);

uint64_t           calc_hash_buf    (stack *stk);

#define FRESH_THE_HASH(stck)                    \
do{                                             \
    uint64_t tmp_hash_stk = calc_hash_stk (stk);\
    uint64_t tmp_hash_buf = calc_hash_buf (stk);\
    stk->hash_stk = tmp_hash_stk;               \
    stk->hash_buf = tmp_hash_buf;               \
} while (false);
//cycle use because tmp_... redeclareted, when you use FRESH_THE_HASH twice in one function

#define DUMP(stk)  stackDump (stk, __FILE__, __func__, __LINE__);
#define CHECK(stk) stackCheck (stk, __func__, __LINE__);

#define PRINT_THE_HASH(stk)                                  \
fprintf (log_file, "stk->hash_stk == %llu\n", stk->hash_stk);\
fprintf (log_file, "calalculated stks hash == %llu", calc_hash_stk (stk));//db

#endif