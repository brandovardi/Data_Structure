#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _NODE_H
#define _NODE_H

typedef struct Node Node;

Node *create_node(void *, size_t, char *);

// void setPrev(Node *, Node *);
void setNext(Node *, Node *);
void setData(Node *, void *, size_t, char *);

// Node *getPrev(Node *);
Node *getNext(Node *);
void *getData(Node *);

void free_node(Node *);

#endif /* _NODE_H */
