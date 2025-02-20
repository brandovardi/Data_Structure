#include "Stack.h"

int main(int argc, char* argv[])
{
    Stack *stack = CreateStack(int);
    int data = 10;
    int g = 3;
    int j = 4;
    Push(stack, data);
    Push(stack, g);
    Push(stack, j);
    PrintStack(stack);
    Pop(stack);
    PrintStack(stack);

    Stack *stack2 = Copy(stack);
    PrintStack(stack2);

    Reverse(stack2);

    PrintStack(stack2);

    return 0;
}