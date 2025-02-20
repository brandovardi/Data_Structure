#include "Queue.h"

struct Queue
{
    Node *head;
    Node *tail;
    size_t size;      // length of the queue
    size_t data_size; // Size of each element
    char *data_type;
};

static void init_head(Queue *, void *);

static void validate_memory_allocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
}

static void init_head(Queue *queue, void *data)
{
    Node *newNode = create_node(data, queue->data_size, queue->data_type);

    queue->head = newNode;
    queue->tail = queue->head;

    queue->size = 1;
}

Queue *create_queue(size_t data_size, char *data_type)
{
    if (data_size <= 0 || data_type == NULL || !strcmp(data_type, ""))
    {
        fprintf(stderr, "Error while creating the queue!\nPossible errors: invalid data type or data size.\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    validate_memory_allocation(queue);
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->data_size = data_size;
    queue->data_type = data_type;
    return queue;
}

// Enqueue
void enqueue(Queue *queue, void *data, char *data_type)
{
    if (queue == NULL || data == NULL || strcmp(queue->data_type, data_type) || data_type == NULL)
        return;

    if (queue->head == NULL)
        init_head(queue, data);
    else
    {
        Node *newNode = create_node(data, queue->data_size, data_type);

        setNext(queue->tail, newNode);
        queue->tail = newNode;

        queue->size++;
    }
}

// Dequeue
void *dequeue(Queue *queue)
{
    if (queue == NULL || queue->head == NULL)
        return NULL;

    Node *head = queue->head;
    void *data = malloc(queue->data_size);
    validate_memory_allocation(data);

    memcpy(data, getData(head), queue->data_size);

    queue->head = getNext(queue->head);

    if (queue->head == NULL)
        queue->tail = NULL;

    free_node(head);
    queue->size--;

    return data;
}

void *peek(Queue *queue)
{
    if (queue == NULL || queue->head == NULL)
        return NULL;

    return getData(queue->head);
}

bool is_empty(Queue *queue)
{
    return (queue != NULL) ? (queue->size == 0) : (printf("The Queue is NULL.\n"), true);
}

size_t size(Queue *queue)
{
    return (queue != NULL) ? queue->size : (printf("The Queue is NULL.\n"), 0);
}

void free_queue(Queue *queue)
{
    if (queue == NULL)
        return;

    Node *curr = queue->head;
    while (curr != NULL)
    {
        Node *next = getNext(curr);
        free_node(curr);
        curr = next;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

Queue *copy(Queue *queue)
{
    if (queue == NULL)
    {
        printf("The Queue is NULL.\n");
        exit(EXIT_FAILURE);
    }

    Queue *newQueue = create_queue(queue->data_size, queue->data_type);

    if (queue->head == NULL)
        return newQueue;

    Node *curr = queue->head;

    void *data_copy = malloc(queue->data_size);
    validate_memory_allocation(data_copy);
    memcpy(data_copy, getData(curr), queue->data_size);

    newQueue->head = create_node(data_copy, queue->data_size, queue->data_type);
    newQueue->tail = newQueue->head;
    newQueue->size = 1;

    Node *new_curr = newQueue->head;
    curr = getNext(curr);

    while (curr != NULL)
    {
        data_copy = malloc(queue->data_size);
        validate_memory_allocation(data_copy);
        memcpy(data_copy, getData(curr), queue->data_size);

        Node *newNode = create_node(data_copy, queue->data_size, queue->data_type);

        setNext(new_curr, newNode);
        newQueue->tail = newNode;
        newQueue->size++;

        new_curr = getNext(new_curr);
        curr = getNext(curr);
    }

    return newQueue;
}

void print_queue(Queue *queue)
{
    if (!queue)
    {
        fprintf(stderr, "Error while printing the Queue...\n");
        exit(EXIT_FAILURE);
    }

    if (queue->size == 0)
    {
        printf("Queue is empty.\n");
        return;
    }

    Node *curr = queue->head;
    int i = 0;
    
    printf("Queue elements:\n");
    while (curr)
    {
        // qui ho i tipi base
        if (!strcmp(queue->data_type, "char"))
            printf("%c\n", *(char *)getData(curr));
        else if (!strcmp(queue->data_type, "signed char"))
            printf("%hhd\n", *(signed char *)getData(curr));
        else if (!strcmp(queue->data_type, "unsigned char"))
            printf("%hhu\n", *(unsigned char *)getData(curr));
        else if (!strcmp(queue->data_type, "short"))
            printf("%hd\n", *(short *)getData(curr));
        else if (!strcmp(queue->data_type, "unsigned short"))
            printf("%hu\n", *(unsigned short *)getData(curr));
        else if (!strcmp(queue->data_type, "int"))
            printf("%d\n", *(int *)getData(curr));
        else if (!strcmp(queue->data_type, "unsigned int"))
            printf("%u\n", *(unsigned int *)getData(curr));
        else if (!strcmp(queue->data_type, "long"))
            printf("%ld\n", *(long *)getData(curr));
        else if (!strcmp(queue->data_type, "unsigned long"))
            printf("%lu\n", *(unsigned long *)getData(curr));
        else if (!strcmp(queue->data_type, "long long"))
            printf("%lld\n", *(long long *)getData(curr));
        else if (!strcmp(queue->data_type, "unsigned long long"))
            printf("%llu\n", *(unsigned long long *)getData(curr));
        else if (!strcmp(queue->data_type, "float"))
            printf("%f\n", *(float *)getData(curr));
        else if (!strcmp(queue->data_type, "double"))
            printf("%lf\n", *(double *)getData(curr));
        else if (!strcmp(queue->data_type, "long double"))
            printf("%Lf\n", *(long double *)getData(curr));
        else
            printf("%d- %s: 0x%0llX\n", ++i, queue->data_type, getData(curr));

        curr = getNext(curr);
    }
}
