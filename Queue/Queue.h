#pragma once

#include "Node.h"
#include <stdbool.h>

#ifndef _QUEUE_H
#define _QUEUE_H

#define CreateQueue(type) \
    create_queue(sizeof(*((type *)0)), #type)

#define Push(queue, data)                                      \
    {                                                          \
        __typeof__(data) _tmp = (data);                        \
        enqueue(CheckQueue(queue), &_tmp, GetTypeOf(_tmp)); \
    }

#define Pop(queue) \
    dequeue(CheckQueue(queue))

#define Peek(queue) \
    peek(CheckQueue(queue))

#define IsEmpty(queue) \
    is_empty(CheckQueue(queue))

#define Size(queue) \
    size(CheckQueue(queue))

#define FreeQueue(queue) \
    free_queue(CheckQueue(queue))

#define Copy(queue) \
    copy(CheckQueue(queue))

#define PrintQueue(queue) \
    print_queue(CheckQueue(queue))

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

#define CheckQueue(queue) \
    (SameType(queue, Queue *) ? ((Queue *)(queue)) : (NULL))

typedef struct Queue Queue;

Queue *create_queue(size_t, char *);

void enqueue(Queue *, void *, char *);
void *dequeue(Queue *);
void *peek(Queue *);
bool is_empty(Queue *);
size_t size(Queue *);
void free_queue(Queue *);
Queue *copy(Queue *);

void print_queue(Queue *);

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

#define BASE_TYPES(T) _Generic((T),   \
    DECLARE_TYPE(char),               \
    DECLARE_TYPE(signed char),        \
    DECLARE_TYPE(unsigned char),      \
    DECLARE_TYPE(short),              \
    DECLARE_TYPE(unsigned short),     \
    DECLARE_TYPE(int),                \
    DECLARE_TYPE(unsigned int),       \
    DECLARE_TYPE(long),               \
    DECLARE_TYPE(unsigned long),      \
    DECLARE_TYPE(long long),          \
    DECLARE_TYPE(unsigned long long), \
    DECLARE_TYPE(float),              \
    DECLARE_TYPE(double),             \
    DECLARE_TYPE(long double),        \
    DECLARE_POINTER_TYPE(Node *),     \
    DECLARE_POINTER_TYPE(Queue *),    \
    void *: "void *",                 \
    void **: "void **",               \
    void ***: "void ***",             \
    void ****: "void ****",           \
    default: "undefined")

#ifdef USER_TYPES
#define GetTypeOf(T) _Generic((T), \
    USER_TYPES,                    \
    default: BASE_TYPES(T))
#else
#define GetTypeOf(T) BASE_TYPES(T)
#endif

#endif /* _QUEUE_H */
