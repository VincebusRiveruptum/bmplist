#include "data.h"

Node *createNode(void *data){
    Node *newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addToList(List **list, Node *newNode){
    Node *rec = NULL;

    if((*list) == NULL){
        (*list) = (List*)malloc(sizeof(List));
        (*list)->firstNode = NULL;
        (*list)->lastNode = NULL;
        (*list)->length = 0;
    }

    if ((*list)->firstNode == NULL){
        (*list)->firstNode = newNode;
    }
    else{
        rec = (*list)->firstNode;
        while (rec->next != NULL){
            rec = rec->next;
        }
        rec->next = newNode;
        (newNode)->prev = rec;
    }
    (*list)->lastNode = newNode;
    (*list)->length++;
}

Node *deleteNodeByIndex(List **list, int index){
    int i=0;
    Node *rec = (*list)->firstNode;

    if(rec != NULL && (index - 1 ) == 0){
        (*list)->firstNode = rec->next;
        if((*list)->firstNode != NULL){
            (*list)->firstNode->prev = NULL;
        }
        free((*list)->firstNode->data);
        return rec;
    }else{
        while(rec != NULL){
            if(rec->prev != NULL && i == (index - 1)){
                rec->prev->next = rec->next;
            }

            if(rec->next != NULL && i == (index - 1)){
                rec->next->prev = rec->prev;
            }
            i++;
            //free(rec->data);
            return rec;
        }
    }
    return NULL;
}

Node *getNodeByIndex(List **list, int index){
    Node *rec = (*list)->firstNode;
    int i=0;

    if((index - 1) < (*list)->length){
        while(rec != NULL){
            if(i == (index - 1)){
                return rec;
            }
            rec = rec->next;
            i++;
        }
    }
    return NULL;
}

int calculateListSize(List *list){
    int i = 0;
    Node *rec = (list)->firstNode;

    while(rec != NULL){
        i++;
        rec = rec->next;
    }
    return i;
}

void freeList(List **list){
    Node *current = (*list)->firstNode;
    Node *temp;
    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(*list);
}
