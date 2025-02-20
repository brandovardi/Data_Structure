#include "Stack.h"

int main(int argc, char* argv[])
{
    Stack *stack = CreateStack(int);
    int data = 10;
    Push(stack, data);
    PrintStack(stack);

    Stack *stack2 = Copy(stack);
    PrintStack(stack2);

    return 0;
}