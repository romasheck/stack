#include "R_stacklib.h"

int main ()
{
    stack stk = {};

    stackCtor (&stk, 10);

    stackPush (&stk, 10);
    
    int x = stackPop (&stk);

    printf ("%d", x);
    
    stackDtor (&stk);

    return 0;
}
