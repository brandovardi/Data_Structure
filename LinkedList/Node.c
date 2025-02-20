#include "Node.h"

struct Node
{
    Node *prev;
    void *data;
    Node *next;
};

static void validate_memory_allocation(void *);

static void validate_memory_allocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
}

Node *create_node(void *data, size_t size, char *data_type)
{
    Node *node = (Node *)malloc(sizeof(Node));
    validate_memory_allocation(node);
    node->data = malloc(size);
    validate_memory_allocation(node->data);
    memcpy(node->data, data, (!strcmp(data_type, "char *") ? (strlen((char *)data) + 1) : size));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void setPrev(Node *node, Node *prev)
{
    (node != NULL) ?: (printf("Failed to set Previuos Node...\n"), exit(EXIT_FAILURE));
    node->prev = prev;
}

void setNext(Node *node, Node *next)
{
    (node != NULL) ?: (printf("Failed to set Next Node...\n"), exit(EXIT_FAILURE));
    node->next = next;
}

void setData(Node *node, void *data, size_t size, char *data_type)
{
    (node != NULL && data != NULL) ?: exit(EXIT_FAILURE);

    if (node->data != NULL)
    {
        free(node->data);
        node->data = NULL;
    }

    node->data = malloc(size);
    validate_memory_allocation(node->data);
    memcpy(node->data, data, (!strcmp(data_type, "char *") ? (strlen((char *)data) + 1) : size));
}

Node *getPrev(Node *node)
{
    return (node != NULL) ? node->prev : NULL;
}

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
    if (node->prev != NULL)
        free(node->data);
    if (node->next != NULL)
        free(node->next);

    free(node);
}
