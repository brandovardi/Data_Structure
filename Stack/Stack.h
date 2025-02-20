#pragma once

#include "Node.h"
#include <stdbool.h>

#ifndef _STACK_H
#define _STACK_H

#define CreateStack(type) \
    create_stack(sizeof(*((type *)0)), #type)

#define Push(stack, data)                                \
    {                                                    \
        __typeof__(data) _tmp = (data);                  \
        push(CheckStack(stack), &_tmp, GetTypeOf(_tmp)); \
    }

#define Pop(stack) \
    pop(CheckStack(stack))

#define Peek(stack) \
    peek(CheckStack(stack))

#define IsEmpty(stack) \
    is_empty(CheckStack(stack))

#define Size(stack) \
    size(CheckStack(stack))

#define FreeStack(stack) \
    free_stack(CheckStack(stack))

#define Copy(stack) \
    copy(CheckStack(stack))

#define PrintStack(stack) \
    print_stack(CheckStack(stack))

#define Reverse(stack) \
    reverse(CheckStack(stack))

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

#define CheckStack(stack) \
    (SameType(stack, Stack *) ? ((Stack *)(stack)) : (NULL))

typedef struct Stack Stack;

Stack *create_stack(size_t, char *);

void push(Stack *, void *, char *);
void *pop(Stack *);
void *peek(Stack *);
bool is_empty(Stack *);
size_t size(Stack *);
void free_stack(Stack *);
Stack *copy(Stack *);
void reverse(Stack *);

void print_stack(Stack *stack);

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
    DECLARE_POINTER_TYPE(Stack *),    \
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

#endif /* _STACK_H */