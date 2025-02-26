#pragma once

#include <stdbool.h>
#include "Node.h"

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef struct LinkedList LinkedList;

// The passed type is forced to be a valid pointer, ensuring an implicit type check.
#define CreateList(type) \
    create_list(sizeof(*((type *)0)), #type)

#define InsertAt(list, data, index)                     \
    {                                                   \
        __typeof__(data) _tmp = (data);                 \
        insert_at(list, &_tmp, index, GetTypeOf(_tmp)); \
    }

#define PushFront(list, data)                     \
    {                                             \
        __typeof__(data) _tmp = (data);           \
        push_front(list, &_tmp, GetTypeOf(_tmp)); \
    }

#define PushBack(list, data)                     \
    {                                            \
        __typeof__(data) _tmp = (data);          \
        push_back(list, &_tmp, GetTypeOf(_tmp)); \
    }

#define RemoveAt(list, index) \
    remove_at(list, index)

#define Set(list, data, index)                    \
    {                                             \
        __typeof__(data) _tmp = (data);           \
        set(list, &_tmp, index, GetTypeOf(_tmp)); \
    }

#define PeekHead(list) \
    peek_head(list)

#define PeekLast(list) \
    peek_last(list)

#define GetNode(list, index) \
    get_node(list, index)

#define Get(list, index) \
    get(list, index)

#define Peek(list) \
    peek(list)

#define Pop(list) \
    pop(list)

/**
 * if you're trying to print a list of a custom type, or a char*
 * you have to build your own print function
 */
#define PrintList(list) \
    print_list(list)

#define FreeList(list) \
    free_list(list)

#define Size(list) \
    size(list)

#define IndexOf(list, data)                     \
    {                                           \
        __typeof__(data) _tmp = (data);         \
        index_of(list, &_tmp, GetTypeOf(_tmp)); \
    }

// #define SameType(a, b) \
//     (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

// #define CheckList(list) \
//     (SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL))

#define NULL_LIST printf("List is NULL.\n")
#define EMPTY_LIST printf("List has no element.\n")
#define NULL_DATA printf("Data is NULL.\n")
#define INVALID_DATA_TYPE printf("Data Type is not valid.\n")
#define INDEX_OUT_OF_BOUND printf("Index Out Of Bound.\n")

LinkedList *create_list(size_t, char *);

// insert a generic element in the list
void insert_at(LinkedList *, void *, size_t, char *);

// add an element in front of the list
void push_front(LinkedList *, void *, char *);

// append an element at the end of the list
void push_back(LinkedList *, void *, char *);

// remove an element in the list at the specified index
void remove_at(LinkedList *, size_t);

// replace an element in the list at the specified index
void set(LinkedList *, void *, size_t, char *);

// attemtp to print the list
void print_list(LinkedList *);

// return the node of the list from the given index
Node *get_node(LinkedList *, size_t);

// return the void * of the element at the specified index
void *get(LinkedList *, size_t);

// simply return the first element of the list
void *peek_head(LinkedList *);

// simply return the last element of the list
void *peek_last(LinkedList *);

// remove and return the last element of the list
void *pop(LinkedList *);

// return the size of the list, so the number of elements contained
size_t size(LinkedList *);

// return the index (if exist) of the element you want to find in the list
int index_of(LinkedList *, void *, char *);

// deallocate (free) all the memory assigned to the list
void free_list(LinkedList *);

#define DECLARE_TYPE(type)                          \
    type:                                           \
    #type,                                          \
        type * : #type " *",                        \
                 type ** : #type " **",             \
                           type *** : #type " ***", \
                                      type **** : #type " ****"

#define DECLARE_POINTER_TYPE(type)              \
    type * : #type " *",                        \
             type ** : #type " **",             \
                       type *** : #type " ***", \
                                  type **** : #type " ****"

#define BASE_TYPES(T) _Generic((T),     \
    DECLARE_TYPE(char),                 \
    DECLARE_TYPE(signed char),          \
    DECLARE_TYPE(unsigned char),        \
    DECLARE_TYPE(short),                \
    DECLARE_TYPE(unsigned short),       \
    DECLARE_TYPE(int),                  \
    DECLARE_TYPE(unsigned int),         \
    DECLARE_TYPE(long),                 \
    DECLARE_TYPE(unsigned long),        \
    DECLARE_TYPE(long long),            \
    DECLARE_TYPE(unsigned long long),   \
    DECLARE_TYPE(float),                \
    DECLARE_TYPE(double),               \
    DECLARE_TYPE(long double),          \
    DECLARE_POINTER_TYPE(Node *),       \
    DECLARE_POINTER_TYPE(LinkedList *), \
    void *: "void *",                   \
    void **: "void **",                 \
    void ***: "void ***",               \
    void ****: "void ****",             \
    default: "undefined")

#ifdef USER_TYPES
#define GetTypeOf(T) _Generic((T), \
    USER_TYPES,                    \
    default: BASE_TYPES(T))
#else
#define GetTypeOf(T) BASE_TYPES(T)
#endif

#endif /* _LINKEDLIST_H */
