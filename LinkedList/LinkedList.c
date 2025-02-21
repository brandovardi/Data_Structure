#include "LinkedList.h"

// implementing the list in the .c file to avoid exposing the list structure
// it would be like making the struct "private" (encapsulation)
struct LinkedList
{
    Node *head;
    Node *last;
    size_t size;      // length of the list
    size_t data_size; // Size of each element
    char *data_type;
};

void validate_list(char *, LinkedList *, char *, size_t, char *, bool, bool, bool, bool);
static void validate_memory_allocation(void *);

static void init_head(LinkedList *, void *);
static void set_head(LinkedList *, void *, char *);
static void set_last(LinkedList *, void *, char *);
static void remove_last(LinkedList *);
static void remove_head(LinkedList *);
static Node *get_head_node(LinkedList *);
static Node *get_last_node(LinkedList *);

static void validate_memory_allocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Memory allocation failed!\nExiting...\n");
        exit(EXIT_FAILURE);
    }
}

LinkedList *create_list(size_t data_size, char *data_type)
{
    if (data_type == NULL || !strcmp(data_type, "") || data_size == 0)
    {
        fprintf(stderr, "Error while creating the list!\nPossible errors: invalid data type or data size.\nExiting...\n");
        exit(EXIT_FAILURE);
    }
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    validate_memory_allocation(list);
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    list->data_type = data_type;
    list->data_size = data_size;
    return list;
}

void insert_at(LinkedList *list, void *data, size_t index, char *data_type)
{
    validate_list("insert_at()", list, data, index, data_type, false, true, true, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = create_node(data, list->data_size, list->data_type);

        Node *curr = list->head;
        int cnt;
        for (cnt = 0; (cnt < index) && (getNext(curr) != NULL); curr = getNext(curr), cnt++)
            ;
        // if the user wants to insert the element at position zero
        if (curr == list->head)
            push_front(list, data, data_type);
        // if instead he wants to insert it at the end
        else if (getNext(curr) == NULL)
            push_back(list, data, data_type);
        // finally if he wants to insert it in an intermediate position
        else
        {
            setPrev(newNode, curr);
            setNext(newNode, getNext(curr));
            setNext(curr, newNode);
        }
    }
}

void push_front(LinkedList *list, void *data, char *data_type)
{
    validate_list("push_front()", list, data, 0, data_type, false, true, false, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = create_node(data, list->data_size, list->data_type);

        // check if the head exists, so if the list already has an element
        // if it already has a head then the newNode must become the head so
        // make its ->next point to the head which would now be the first element
        // so that the head becomes the second element
        if (list->head == NULL)
        {
            list->head = newNode;
            list->last = list->head;
        }
        else
        {
            setNext(newNode, list->head);
            list->head = newNode;
        }
        list->size++;
    }
}

void push_back(LinkedList *list, void *data, char *data_type)
{
    validate_list("push_back()", list, data, 0, data_type, false, true, false, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = create_node(data, list->data_size, list->data_type);

        setPrev(newNode, list->last);     // assign the previous of the new node to the last of the list
        setNext(list->last, newNode);     // assign the next of the last to the new node
        list->last = getNext(list->last); // make the new node the last of the list

        list->size++;
    }
}

static void init_head(LinkedList *list, void *data)
{
    validate_list("init_head()", list, data, 0, NULL, false, true, false, false);

    Node *newNode = create_node(data, list->data_size, list->data_type);

    list->head = newNode;
    list->last = list->head;

    list->size++;
}

static void remove_last(LinkedList *list)
{
    validate_list("remove_at()->remove_last()", list, NULL, 0, NULL, true, false, false, false);

    Node *last = list->last;
    // if the list has only one element, so there is only the head
    if (list->last == list->head)
        remove_head(list);
    else
    {
        list->last = getPrev(list->last);
        setNext(list->last, NULL);
        free(getData(last));
        free(last);
        (list->size <= 0) ?: (list->size--);
    }
}

static void remove_head(LinkedList *list)
{
    validate_list("remove_at()->remove_head()", list, NULL, 0, NULL, true, false, false, false);

    // if the list has only one element, so there is only the head
    if (getNext(list->head) == NULL)
    {
        free(getData(list->head));
        free(list->head);
        list->head = NULL;
        list->last = NULL;
        list->size = 0;
    }
    // if instead it has more than one element
    else
    {
        // save the second element of the list
        Node *head = list->head;
        // clear the head and delete it
        list->head = getNext(list->head);
        setPrev(list->head, NULL);
        free(getData(head));
        free(head);
        (list->size <= 0) ?: (list->size--);
    }
}

void remove_at(LinkedList *list, size_t index)
{
    validate_list("remove_at()", list, NULL, index, NULL, true, false, true, false);

    // immediately check if the user wants to delete the head, so if index == 0
    if (!index)
        remove_head(list);
    // and also immediately check if the user wants to delete the last element
    else if (index >= list->size - 1)
        remove_last(list);
    // finally if the user wants to delete an element in the middle
    else
    {
        int cnt;
        Node *curr = list->head;
        for (cnt = 0; (getNext(curr) != NULL) && (cnt < index); curr = getNext(curr), cnt++)
            ;
        // modify the list by deleting the desired element
        setPrev(getNext(curr), getPrev(curr));
        setNext(getPrev(curr), getNext(curr));
        setNext(curr, NULL);
        setPrev(curr, NULL);
        // finally free the memory of the deleted element
        free(getData(curr));
        free(curr);
        (list->size <= 0) ?: (list->size--);
    }
}

static void set_head(LinkedList *list, void *data, char *data_type)
{
    validate_list("set()->set_last()", list, data, 0, data_type, true, true, false, true);

    setData(list->head, data, list->data_size, list->data_type);
}

static void set_last(LinkedList *list, void *data, char *data_type)
{
    validate_list("set()->set_last()", list, data, 0, data_type, true, true, false, true);

    setData(list->last, data, list->data_size, list->data_type);
}

void set(LinkedList *list, void *data, size_t index, char *data_type)
{
    validate_list("set()", list, data, index, data_type, true, true, true, true);

    if (!index)
        set_head(list, data, data_type);
    else if (index == list->size - 1)
        set_last(list, data, data_type);
    else
    {
        int i;
        Node *curr;
        for (curr = list->head, i = 0; (i < index) && (getNext(curr) != NULL); curr = getNext(curr), i++)
            ;
        setData(curr, data, list->data_size, list->data_type);
    }
}

void print_list(LinkedList *list)
{
    validate_list("print_list()", list, NULL, 0, NULL, false, false, false, false);

    if (list->size == 0)
    {
        printf("List is empty.\n");
        return;
    }

    Node *curr = list->head;
    int i = 0;

    printf("List elements:\n");
    while (curr)
    {
        // qui ho i tipi base
        if (!strcmp(list->data_type, "char"))
            printf("%c\n", *(char *)getData(curr));
        else if (!strcmp(list->data_type, "signed char"))
            printf("%hhd\n", *(signed char *)getData(curr));
        else if (!strcmp(list->data_type, "unsigned char"))
            printf("%hhu\n", *(unsigned char *)getData(curr));
        else if (!strcmp(list->data_type, "short"))
            printf("%hd\n", *(short *)getData(curr));
        else if (!strcmp(list->data_type, "unsigned short"))
            printf("%hu\n", *(unsigned short *)getData(curr));
        else if (!strcmp(list->data_type, "int"))
            printf("%d\n", *(int *)getData(curr));
        else if (!strcmp(list->data_type, "unsigned int"))
            printf("%u\n", *(unsigned int *)getData(curr));
        else if (!strcmp(list->data_type, "long"))
            printf("%ld\n", *(long *)getData(curr));
        else if (!strcmp(list->data_type, "unsigned long"))
            printf("%lu\n", *(unsigned long *)getData(curr));
        else if (!strcmp(list->data_type, "long long"))
            printf("%lld\n", *(long long *)getData(curr));
        else if (!strcmp(list->data_type, "unsigned long long"))
            printf("%llu\n", *(unsigned long long *)getData(curr));
        else if (!strcmp(list->data_type, "float"))
            printf("%f\n", *(float *)getData(curr));
        else if (!strcmp(list->data_type, "double"))
            printf("%lf\n", *(double *)getData(curr));
        else if (!strcmp(list->data_type, "long double"))
            printf("%Lf\n", *(long double *)getData(curr));
        else
            printf("%d- %s: 0x%0llX\n", ++i, list->data_type, getData(curr));

        curr = getNext(curr);
    }
}

static Node *get_head_node(LinkedList *list)
{
    validate_list("get_node()->get_head_node()", list, NULL, 0, NULL, true, false, false, false);

    return create_node(getData(list->head), list->data_size, list->data_type);
}

static Node *get_last_node(LinkedList *list)
{
    validate_list("get_node()->get_last_node()", list, NULL, 0, NULL, true, false, false, false);

    return create_node(getData(list->last), list->data_size, list->data_type);
}

Node *get_node(LinkedList *list, size_t index)
{
    validate_list("get_node()", list, NULL, index, NULL, true, false, true, false);

    Node *newNode = NULL;
    Node *curr = NULL;
    int i;

    if (!index)
        newNode = get_head_node(list);
    else if (index == list->size - 1)
        newNode = get_last_node(list);
    else
    {
        curr = list->head;
        for (i = 0; i < index && getNext(curr) != NULL; curr = getNext(curr), i++)
            ;
        newNode = create_node(getData(curr), list->data_size, list->data_type);
    }

    return newNode;
}

void *peek_head(LinkedList *list)
{
    validate_list("peek_head()", list, NULL, 0, NULL, true, false, false, false);
    return getData(list->head);
}

void *peek_last(LinkedList *list)
{
    validate_list("peek_last()", list, NULL, 0, NULL, true, false, false, false);
    return getData(list->last);
}

void *get(LinkedList *list, size_t index)
{
    validate_list("get()", list, NULL, index, NULL, true, false, true, false);

    void *data = NULL;
    int i;
    if (!index)
        data = peek_head(list);
    else if (index == list->size - 1)
        data = peek_last(list);
    else
    {
        Node *curr = list->head;
        for (i = 0; i < index && getNext(curr) != NULL; curr = getNext(curr), i++)
            ;
        data = getData(curr);
    }
    return data;
}

void *pop(LinkedList *list)
{
    validate_list("pop()", list, NULL, 0, NULL, true, false, false, false);

    void *last = malloc(list->data_size);
    memcpy(last, getData(list->last), list->data_size);

    remove_last(list);

    return last;
}

size_t size(LinkedList *list)
{
    return (list != NULL) ? (list->size) : (NULL_LIST, 0);
}

// this function works only with primitive types
int index_of(LinkedList *list, void *data, char *data_type)
{
    validate_list("index_of()", list, data, 0, data_type, true, true, false, true);
    int index = -1;

    int i;
    Node *curr = list->head;
    for (i = 0; getNext(curr) != NULL && index != i; curr = getNext(curr), i++)
    {
        if (index == -1)
            if ((!strcmp(list->data_type, "char") && *(char *)getData(curr) == *(char *)data) || (!strcmp(list->data_type, "signed char") && *(signed char *)getData(curr) == *(signed char *)data) || (!strcmp(list->data_type, "unsigned char") && *(unsigned char *)getData(curr) == *(unsigned char *)data) || (!strcmp(list->data_type, "short") && *(short *)getData(curr) == *(short *)data) || (!strcmp(list->data_type, "unsigned short") && *(unsigned short *)getData(curr) == *(unsigned short *)data) || (!strcmp(list->data_type, "int") && *(int *)getData(curr) == *(int *)data) || (!strcmp(list->data_type, "unsigned int") && *(unsigned int *)getData(curr) == *(unsigned int *)data) || (!strcmp(list->data_type, "long") && *(long *)getData(curr) == *(long *)data) || (!strcmp(list->data_type, "unsigned long") && *(unsigned long *)getData(curr) == *(unsigned long *)data) || (!strcmp(list->data_type, "long long") && *(long long *)getData(curr) == *(long long *)data) || (!strcmp(list->data_type, "unsigned long long") && *(unsigned long long *)getData(curr) == *(unsigned long long *)data) || (!strcmp(list->data_type, "float") && *(float *)getData(curr) == *(float *)data) || (!strcmp(list->data_type, "double") && *(double *)getData(curr) == *(double *)data) || (!strcmp(list->data_type, "long double") && *(long double *)getData(curr) == *(long double *)data))
                index = i;
    }

    return index;
}

void free_list(LinkedList *list)
{
    validate_list("free_list()", list, NULL, 0, NULL, true, false, false, false);

    Node *curr = list->head;
    while (curr != NULL)
    {
        Node *next = getNext(curr);
        free(getData(curr));
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    list->data_size = 0;
    free(list);
}

void validate_list(char *funName, LinkedList *list, char *data, size_t index, char *datatype, bool checkhead, bool is_data, bool is_index, bool is_datatype)
{
    bool check = false;
    if (list == NULL || (checkhead && list->head == NULL))
    {
        (list == NULL) ? NULL_LIST : EMPTY_LIST;
        fprintf(stderr, "Invalid List! Exiting...\n");
        check = true;
    }
    if (is_data && data == NULL)
    {
        NULL_DATA;
        fprintf(stderr, "Invalid Data! Exiting...\n");
        check = true;
    }
    if (is_index && index > list->size)
    {
        INDEX_OUT_OF_BOUND;
        fprintf(stderr, "Invalid Index! Exiting...\n");
        check = true;
    }
    if (is_datatype && (datatype == NULL || strcmp(list->data_type, datatype)))
    {
        INVALID_DATA_TYPE;
        fprintf(stderr, "Invalid Data Type! Exiting...\n");
        check = true;
    }
    if (check)
    {
        printf("Exception from: %s; ", funName);
        exit(EXIT_FAILURE);
    }
}
