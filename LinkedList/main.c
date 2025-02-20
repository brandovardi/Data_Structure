#define USER_TYPES DECLARE_TYPE(Car), DECLARE_TYPE(Bike)
#include "LinkedList.h"

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
    LinkedList *list = CreateList(int);
    
    return EXIT_SUCCESS;
}