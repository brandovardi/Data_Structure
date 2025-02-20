#include "Stack.h"

struct Stack
{
    Node *bottom;
    Node *top;
    size_t size;      // length of the stack
    size_t data_size; // Size of each element
    char *data_type;
};

static void init_head(Stack *, void *);

static void validate_memory_allocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
}

static void init_head(Stack *stack, void *data)
{
    Node *newNode = create_node(data, stack->data_size, stack->data_type);

    stack->bottom = newNode;
    stack->top = stack->bottom;

    stack->size = 1;
}

Stack *create_stack(size_t data_size, char *data_type)
{
    if (data_size <= 0 || data_type == NULL || !strcmp(data_type, ""))
    {
        fprintf(stderr, "Error while creating the stack!\nPossible errors: invalid data type or data size.\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    validate_memory_allocation(stack);
    stack->bottom = NULL;
    stack->top = NULL;
    stack->size = 0;
    stack->data_size = data_size;
    stack->data_type = data_type;
    return stack;
}

void push(Stack *stack, void *data, char *data_type)
{
    if (stack == NULL || data == NULL || strcmp(stack->data_type, data_type) || data_type == NULL)
        return;

    if (stack->bottom == NULL)
        init_head(stack, data);
    else
    {
        Node *newNode = create_node(data, stack->data_size, data_type);

        setPrev(newNode, stack->top);
        stack->top = newNode;

        stack->size++;
    }
}

void *pop(Stack *stack)
{
    if (stack == NULL || stack->top == NULL)
        return NULL;

    Node *top = stack->top;
    void *data = malloc(stack->data_size);
    validate_memory_allocation(data);
    memcpy(data, getData(top), stack->data_size);

    stack->top = getPrev(stack->top);

    if (stack->top == NULL)
        stack->bottom = NULL;

    free(getData(top));
    free(top);
    stack->size--;

    return data;
}

void *peek(Stack *stack)
{
    if (stack == NULL || stack->top == NULL)
        return NULL;

    return getData(stack->top);
}

bool is_empty(Stack *stack)
{
    return (stack != NULL) ? (stack->size == 0) : (printf("The Stack is NULL.\n"), true);
}

size_t size(Stack *stack)
{
    return (stack != NULL) ? stack->size : (printf("The Stack is NULL.\n"), 0);
}

void free_stack(Stack *stack)
{
    if (stack == NULL)
        return;

    Node *curr = stack->top;
    while (curr != NULL)
    {
        Node *prev = getPrev(curr);
        free(getData(curr));
        free(curr);
        curr = prev;
    }

    free(stack->data_type);
    free(stack);
}

Stack *copy(Stack *stack)
{
    if (stack == NULL)
    {
        printf("The Stack is NULL.\n");
        exit(EXIT_FAILURE);
    }

    Stack *newstack = create_stack(stack->data_size, stack->data_type);

    if (stack->top == NULL)
        return newstack;

    Node *curr = stack->top;

    void *data_copy = malloc(stack->data_size);
    validate_memory_allocation(data_copy);
    memcpy(data_copy, getData(curr), stack->data_size);

    newstack->top = create_node(data_copy, stack->data_size, stack->data_type);
    newstack->bottom = newstack->top;
    newstack->size = 1;

    Node *new_curr = newstack->top;
    curr = getPrev(curr);

    while (curr != NULL)
    {
        data_copy = malloc(stack->data_size);
        validate_memory_allocation(data_copy);
        memcpy(data_copy, getData(curr), stack->data_size);

        Node *newNode = create_node(data_copy, stack->data_size, stack->data_type);

        setPrev(new_curr, newNode);
        newstack->bottom = newNode;
        newstack->size++;

        new_curr = getPrev(new_curr);
        curr = getPrev(curr);
    }

    return newstack;
}

void print_stack(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "Error while printing the Stack...\n");
        exit(EXIT_FAILURE);
    }

    if (stack->size == 0)
        printf("Stack is empty.\n");

    Node *curr = stack->top;
    int i = 0;

    printf("Stack elements:\n");
    while (curr)
    {
        // qui ho i tipi base
        if (!strcmp(stack->data_type, "char"))
            printf("%c\n", *(char *)getData(curr));
        else if (!strcmp(stack->data_type, "signed char"))
            printf("%hhd\n", *(signed char *)getData(curr));
        else if (!strcmp(stack->data_type, "unsigned char"))
            printf("%hhu\n", *(unsigned char *)getData(curr));
        else if (!strcmp(stack->data_type, "short"))
            printf("%hd\n", *(short *)getData(curr));
        else if (!strcmp(stack->data_type, "unsigned short"))
            printf("%hu\n", *(unsigned short *)getData(curr));
        else if (!strcmp(stack->data_type, "int"))
            printf("%d\n", *(int *)getData(curr));
        else if (!strcmp(stack->data_type, "unsigned int"))
            printf("%u\n", *(unsigned int *)getData(curr));
        else if (!strcmp(stack->data_type, "long"))
            printf("%ld\n", *(long *)getData(curr));
        else if (!strcmp(stack->data_type, "unsigned long"))
            printf("%lu\n", *(unsigned long *)getData(curr));
        else if (!strcmp(stack->data_type, "long long"))
            printf("%lld\n", *(long long *)getData(curr));
        else if (!strcmp(stack->data_type, "unsigned long long"))
            printf("%llu\n", *(unsigned long long *)getData(curr));
        else if (!strcmp(stack->data_type, "float"))
            printf("%f\n", *(float *)getData(curr));
        else if (!strcmp(stack->data_type, "double"))
            printf("%lf\n", *(double *)getData(curr));
        else if (!strcmp(stack->data_type, "long double"))
            printf("%Lf\n", *(long double *)getData(curr));
        else
            printf("%d- %s: 0x%0llX\n", ++i, stack->data_type, getData(curr));

        curr = getPrev(curr);
    }
}
