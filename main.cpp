#include "R_stacklib.h"

int main ()
{
    stack stk = {};

    stackCtor (&stk, 10);

    stackPush (&stk, 10);
    /*
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);
    stackPush (&stk, 10);*/
    
    /*for (int i = 0; i < 45; ++i)
    {
        stackPop (&stk);
    }*/
    
    int x = stackPop (&stk);

    printf ("%d", x);
    
    stackDtor (&stk);

    return 0;
}