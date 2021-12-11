#include "R_stacklib.h"

FILE* log_file = fopen("log.txt", "w");

void stackCtor (stack* stk, int cap)
{
    stk->size = 0;
    stk->capacity = cap;
    stk->cntrDtor = 0; 
    stk->error = NOT_ERROR;
    stk_elem_type* tmp_ptr  = (stk_elem_type*) (calloc (cap + 2, sizeof(stk_elem_type)));//recalc char every elem
    if (NULL == tmp_ptr)
    {
        stk->error = CALLOC_ERROR;
        stackDump (stk, __FILE__, "stackCtor", __LINE__);
        printf ("warning: failed to allocate memory");
        FRESH_THE_HASH (stk);
        return;
    }
    stk->start_ptr = tmp_ptr + 1;
    //canary not same type
    //llu canary
    *(stk->start_ptr - 1) = 228;
    *(stk->start_ptr + cap + 1) = 228;
    FRESH_THE_HASH(stk);
    
    stackCheck (stk, "stackCtor", __LINE__);
}           

void stackPush (stack *stk, stk_elem_type elem)
{
    stackCheck (stk, "stackPush", __LINE__);
    
    if (stk->size == stk->capacity / 2)
    {
        stackReSize (stk, "expand");
        stackCheck  (stk, "stackPush", __LINE__);
    }

    *(stk->start_ptr + stk->size) = elem;
    stk->size ++;

    FRESH_THE_HASH(stk);

    stackCheck (stk, "stackPush", __LINE__);
}

stk_elem_type stackPop (stack *stk)
{
    stackCheck (stk, "stackPop", __LINE__); 

    if (0 == stk->size)
    {
        stk->error = TRY_POP_VOID_STK;
        stackDump(stk,__FILE__ ,"stackPop",__LINE__ );
        FRESH_THE_HASH (stk);
        return POISON54;
    }
    
    stk_elem_type last_elem = *(stk->start_ptr + (stk->size - 1));
    if (POISON54 == last_elem)
    {
        stk->error = USE_POISENED_ELEM;
        FRESH_THE_HASH (stk);
        stackDump (stk, __FILE__, "stackPop", __LINE__);
    }
    stk->size -= 1;
    FRESH_THE_HASH (stk); 

    if (stk->size < stk->capacity / 4)
    {
        stackReSize (stk, "reduce");
    } 
    FRESH_THE_HASH(stk);

    stackCheck (stk, "stackPop", __LINE__);

    return last_elem;
}

void stackReSize (stack* stk, const char* mode)
{
    stackCheck (stk, "stackReSize", __LINE__);
    if (compare_str(mode, "expand") == S_equal)
    {
        if (stk->capacity < 10)
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity * 1.5 + 5 + 2);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            FRESH_THE_HASH (stk);
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            return;
          }

          stk->start_ptr = tmp_ptr + 1;
          stk->capacity = stk->capacity * 1.5 + 5;
          *(stk->start_ptr + stk->capacity + 1) = 228;
          FRESH_THE_HASH(stk);
          stackCheck (stk, "stackReSize", __LINE__);
          return;
        }
        if (stk->capacity > 10000)
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity * 1.5);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            FRESH_THE_HASH(stk);
            return;
          }

          stk->start_ptr = tmp_ptr + 1;
          stk->capacity = stk->capacity * 1.5;
          *(stk->start_ptr + stk->capacity + 1) = 228;
          FRESH_THE_HASH(stk);
          stackCheck (stk, "stackReSize", __LINE__);
          return;  
        }
        else 
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity * 2);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            FRESH_THE_HASH(stk);
            return;
          }

          stk->start_ptr = tmp_ptr + 1;
          stk->capacity = stk->capacity * 2;
          *(stk->start_ptr + stk->capacity + 1) = 228;
          FRESH_THE_HASH(stk);
          stackCheck (stk, "stackReSize", __LINE__);
          return;
        }
    }
    if (compare_str("reduce", mode) == S_equal)
    {
        if (stk->capacity < 10)
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity / 3);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            FRESH_THE_HASH (stk);
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            return;
          }

            stk->start_ptr = tmp_ptr + 1;
            stk->capacity = stk->capacity / 3;
            *(stk->start_ptr + stk->capacity + 1) = 228;
            FRESH_THE_HASH(stk);
            stackCheck (stk, "stackReSize", __LINE__);
            return;
        }
        if (stk->capacity > 10000)
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity / 3);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            FRESH_THE_HASH (stk);
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            return;
          }

          stk->start_ptr = tmp_ptr + 1;
          stk->capacity = stk->capacity / 3;
          *(stk->start_ptr + stk->capacity + 1) = 228;
          FRESH_THE_HASH(stk);
          stackCheck (stk, "stackReSize", __LINE__);
          return;  
        }
        else 
        {
          stk_elem_type* tmp_ptr = (stk_elem_type*) realloc (stk->start_ptr - 1, stk->capacity * 2 / 3);
          if (NULL == tmp_ptr)
          {
            stk->error = REALLOC_ERROR; 
            stackDump(stk, __FILE__, "stackResize", __LINE__);
            FRESH_THE_HASH(stk);
            return;
          }

          stk->start_ptr = tmp_ptr + 1;
          stk->capacity = stk->capacity * 2 / 3;
          *(stk->start_ptr + stk->capacity + 1) = 228;
          FRESH_THE_HASH(stk);
          stackCheck (stk, "stackReSize", __LINE__);
          return;
        }
    }
    else 
    {
        fprintf (log_file, "stackReSize called with wrong mode");
    }
}

void stackDtor (stack *stk)
{
    stackCheck (stk, "stackDtor", __LINE__);

    stk->size = -1;
    stk->capacity = -1;

    free (stk->start_ptr);
    stk->start_ptr = (stk_elem_type*)POISON54;

    stk->cntrDtor++;
}

void stackCheck (stack* stk, const char* func_name, const int line_num)
{
    if (stk->cntrDtor > 0)
    {
        stk->error = STK_DESTROYED;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (BIRD_CONST != stk->l_stk_bird)
    {
        stk->error = LEFT_BIRD_DIED;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }   
    if (BIRD_CONST != stk->r_stk_bird)
    {
        stk->error = RIGHT_BIRD_DIED;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (calc_hash_stk(stk) != stk->hash_stk)
    {
        stk->error = MISMATCHED_HASH_STK;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (NULL == stk->start_ptr)
    {
        stk->error = START_PTR_IS_NULL;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    } 
    if (*(stk->start_ptr - 1) != 228)//
    {
        stk->error = LEFT_BUFBIRD_DIED;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (*(stk->start_ptr + stk->capacity + 1) != 228)//
    {
        stk->error = RIGHT_BUFBIRD_DIED;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (calc_hash_buf(stk) != stk->hash_buf)
    {
        stk->error = MISMATCHED_HASH_BUF;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (0 > stk->capacity)
    {
        stk->error = CAPACITY_LESS_ZERO;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (0 > stk->size)
    {
        stk->error = SIZE_LESS_ZERO;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
    if (stk->size > stk->capacity)
    {
        stk->error = STACK_OVERFLOW;
        stackDump (stk, __FILE__, func_name, line_num);
        return;
    }
}

void stackDump (stack *stk, const char* file_name, const char* func_name, const int line_num)
{
    fprintf (log_file, "\n---------------------------------------------------------------------------------------------------\n");
    fprintf (log_file, "WARNING:\n");
    fprintf (log_file, "In  file \"%s\" in function \"%s\" in line %d\n", file_name, func_name, line_num);

    switch (stk->error)
    {
    case NOT_ERROR:
        fprintf (log_file, "\nfunction stackDump was called, but stk->error equal NOT_ERROR\n");
        stackPrint (stk);
        break;

    case CALLOC_ERROR:
        fprintf (log_file, "\nthere is imposible to allocate memory for stack with capacity == %d\n", stk->capacity);
        stackPrint (stk);
        break;

    case REALLOC_ERROR:
        fprintf (log_file, "\nthere is imposible to reallocate memory for stack\n");
        stackPrint (stk);
        break;

    case STACK_OVERFLOW:
        fprintf (log_file, "\nstack overflow\n");
        stackPrint (stk);
        break;

    case SIZE_LESS_ZERO:
        fprintf (log_file, "\nstacks size less zero\n");
        stackPrint (stk);
        break;

    case CAPACITY_LESS_ZERO:
        fprintf (log_file, "\nstacks capacity less zero\n");
        stackPrint (stk);
        break;

    case STK_DESTROYED:
        fprintf (log_file, "\nstack was destroeyed\n");
        break;

    case START_PTR_IS_NULL:
        fprintf (log_file, "\nstart pointer equal NULL\n");
        stackPrint (stk);
        break;
        
    case LEFT_BIRD_DIED:
        fprintf (log_file, "\nsomething killed left bird!!!!! What a pity!!!!\n");
        stackPrint (stk);
        break;

    case RIGHT_BIRD_DIED:
        fprintf (log_file, "\nsomething killed right bird!!!! What a pity!!!!\n");
        stackPrint (stk);
        break;

    case LEFT_BUFBIRD_DIED:
        fprintf (log_file, "\nsomething killed left bird!!!! I am crying!!!!!\n");
        stackPrint (stk);
        break;

    case RIGHT_BUFBIRD_DIED:
        fprintf (log_file, "\nsomething killed right bufbird!!! WHAT A PITY!!!\n");
        stackPrint (stk);
        break;

    case MISMATCHED_HASH_STK:
        fprintf (log_file, "\nstks hash mismatched\n");
        stackPrint (stk);
        break;

    case MISMATCHED_HASH_BUF:
        fprintf (log_file, "\nbufs hash mismatched\n");
        stackPrint (stk);
        break;

    case USE_POISENED_ELEM:
        fprintf (log_file, "\ntry to use poisened elem, this may be just a coincidence\n"); 
        stackPrint (stk);
        break; 

    case TRY_POP_VOID_STK:
        fprintf (log_file, "\ntry to Pop void stack\n");
        stackPrint (stk); 
        break;            

    default:
        fprintf (log_file, "\nfunction stackDump was called, but stk->error is not named problem\n");
        stackPrint (stk);
        break;
    }

    fprintf (log_file, "\n---------------------------------------------------------------------------------------------------\n");
}

void stackPrint (stack *stk)//MENTOR HELP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    fprintf (log_file, "\nstack:\n");
    fprintf (log_file, "r_stk_bird == %llu\n", stk->r_stk_bird);
    fprintf (log_file, "l_stk_bird == %llu\n", stk->l_stk_bird);
    fprintf (log_file, "hash_stk == %llu\n", stk->hash_stk);
    fprintf (log_file, "calalculated stks hash == %llu\n", calc_hash_stk (stk));

    
    fprintf (log_file, "\"stack was destructed\" == %s\n", ((stk->cntrDtor) ? "true" : "false"));
    
    fprintf (log_file, "size == %d\n", stk->size);
    fprintf (log_file, "capacity == %d\n", stk->capacity);

    fprintf (log_file, "hash_buf == %llu\n", stk->hash_buf);
    fprintf (log_file, "calalculated bufs hash == %llu\n", calc_hash_buf (stk));

    if (NULL != stk->start_ptr)
    {
        fprintf (log_file, "start_ptr == %d\n", stk->start_ptr);

        fprintf (log_file, "left_bufbird == %d\n", *(stk->start_ptr - 1));

        if (stk->size >= stk->capacity > 0)
        {
            fprintf (log_file, "maybe this is right_bufbird == %d\n", *(stk->start_ptr + stk->size + 1));
            fprintf (log_file, "or maybe this == %d\n", *(stk->start_ptr + stk->capacity + 1));
            for (int i = 0; i < stk->size; ++i)
            {
                fprintf (log_file, "%d: %d \n", i, *(stk->start_ptr + i)); // exchange scnd %d from anything 
            }
        }
        if (0 < stk->size < stk->capacity)
        {
            fprintf (log_file, "right_bufbird == %d\n", *(stk->start_ptr + stk->capacity + 1));
            for (int i = 0; i < stk->capacity; ++i)
            {
                fprintf (log_file, "%d: %d \n", i, *(stk->start_ptr + i)); // exchange %f from anything 
            }
        } 
    }
    fprintf(log_file, "\n");
}

uint64_t calc_hash_stk (stack* stk)
{
    uint64_t tmp_hash_stk = stk->hash_stk;
    uint64_t tmp_hash_buf = stk->hash_buf;
    stk->hash_stk = 0;
    stk->hash_buf = 0;

    uint64_t hash_stk = 0;
    char* tmp_ptr = (char*)stk;

    for (char i = sizeof (stk_elem_type) + 1; i < sizeof(*stk) - sizeof (stk_elem_type) - 1; ++i) 
    {
        hash_stk += hash_stk*i + *(tmp_ptr + i); 
    }
    
    stk->hash_stk = tmp_hash_stk;
    stk->hash_buf = tmp_hash_buf;
    return hash_stk; 
}

uint64_t calc_hash_buf (stack* stk)
{
    uint64_t tmp_hash_stk = stk->hash_stk;
    uint64_t tmp_hash_buf = stk->hash_buf;
    stk->hash_stk = 0;
    stk->hash_buf = 0;

    uint64_t hash_buf = 0;
    char* tmp_ptr = (char*)stk->start_ptr;

    for (char i = 1; i < stk->size * sizeof(stk_elem_type) - 2; ++i)
    {
        hash_buf += hash_buf*i + *(tmp_ptr - i); 
    }
    stk->hash_stk = tmp_hash_stk;
    stk->hash_buf = tmp_hash_buf;
    return hash_buf;
}

/*
void fresh_the_hash (stack* stk)
{
    uint64_t tmp_hash_stk = calc_hash_stk (stk);
    uint64_t tmp_hash_buf = calc_hash_buf (stk);

    stk->hash_stk = tmp_hash_stk;
    stk->hash_buf = tmp_hash_buf;

    return;
}
*/