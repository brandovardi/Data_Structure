#define USER_TYPES DECLARE_TYPE(Car), DECLARE_TYPE(Bike), DECLARE_TYPE(Gatto)
#include "LinkedList.h"

typedef int Gatto;

typedef struct Car
{
    int tipo;
} Car;

typedef struct Bike
{
    int tipo;
} Bike;

int main(int argc, char const *argv[])
{
    LinkedList *list = CreateList(char *);
    LinkedList *ls = CreateList(Gatto);
    char *data = "Hello, World!";
    PushFront(list, data);
    PushBack(list, "Hello, World! 2");
    PushBack(list, "Hello, World! 3");

    char *last = *(char **)Get(list, 0);
    printf("Last element: %s\n", last);

    PrintList(list);

    FreeList(list);

    PrintList(list);

    return EXIT_SUCCESS;
}