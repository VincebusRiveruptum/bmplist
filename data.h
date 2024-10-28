// Generic Simple doubly linked list by vincebus riveruptum. 

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List{
    struct Node *firstNode;
    struct Node *lastNode;
    int length;
} List;

void addToList(List **list, Node *newNode);
Node *createNode(void *data);
Node *deleteNodeByIndex(List **list, int index);
Node *getNodeByIndex(List **list, int index);
int calculateListSize(List *list);
void freeList(List **list);

#endif