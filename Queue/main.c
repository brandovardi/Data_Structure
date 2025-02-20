#include "Queue.h"

int main(int argc, char* argv[])
{
    Queue *queue = CreateQueue(int);
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        Push(queue, i);
    }
    PrintQueue(queue);

    Queue *queue2 = Copy(queue);
    PrintQueue(queue2);

    FreeQueue(queue);
    FreeQueue(queue2);
    
    return 0;
}