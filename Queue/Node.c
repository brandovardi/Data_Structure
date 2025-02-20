#include "Node.h"

struct Node
{
    // Node *prev;
    void *data;
    Node *next;
};

static void validate_memory_allocation(void *);

static void validate_memory_allocation(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
}

Node *create_node(void *data, size_t data_size, char *data_type)
{
    Node *node = (Node *)malloc(sizeof(Node));
    validate_memory_allocation(node);
    node->data = malloc(data_size);
    validate_memory_allocation(node->data);
    if (!strcmp(data_type, "char *"))
        strcpy((char *)node->data, (char *)data);
    else
        memcpy(node->data, data, data_size);
    node->next = NULL;
    // node->prev = NULL;
    return node;
}

// void setPrev(Node *node, Node *prev)
// {
//     (node != NULL) ?: (fprintf(stderr, "Failed to set Previuos Node...\n"), exit(EXIT_FAILURE));
//     node->prev = prev;
// }

void setNext(Node *node, Node *next)
{
    (node != NULL) ?: (fprintf(stderr, "Failed to set Next Node...\n"), exit(EXIT_FAILURE));
    node->next = next;
}

void setData(Node *node, void *data, size_t data_size, char *data_type)
{
    (node != NULL) ?: (fprintf(stderr, "Impossible setting data to that Node...\n"), exit(EXIT_FAILURE));

    if (node->data != NULL)
        free(node->data);

    node->data = malloc(data_size);
    validate_memory_allocation(node->data);
    if (!strcmp(data_type, "char *"))
        strcpy((char *)node->data, (char *)data);
    else
        memcpy(node->data, data, data_size);
}

// Node *getPrev(Node *node)
// {
//     return (node != NULL) ? node->prev : NULL;
// }

Node *getNext(Node *node)
{
    return (node != NULL) ? node->next : NULL;
}

void *getData(Node *node)
{
    return (node != NULL) ? node->data : NULL;
}

void free_node(Node *node)
{
    if (node == NULL)
        return;

    if (node->data != NULL)
        free(node->data);
    // if (node->prev != NULL)
    //     free(node->data);
    if (node->next != NULL)
        free(node->next);

    free(node);
}
