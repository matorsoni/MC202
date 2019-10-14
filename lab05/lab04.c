#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int value;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct LinkedList
{
    Node* first;
}LinkedList;

// ----------------------- Utilidades para o struct LinkedList ------------------------
void printList(LinkedList* list);
Node* getLast(LinkedList* list);
void append(LinkedList* list, int value);
void removeLast(LinkedList* list);
void destructList(LinkedList* list);

// ---------------------- Main -----------------------
int main()
{
    LinkedList l;
    l.first = NULL;

    append(&l, 1);
    append(&l, 2);
    append(&l, 3);

    printList(&l);

    destructList(&l);
    return 0;
}

// ----------------------- Utilidades para o struct LinkedList ------------------------
void printList(LinkedList* list)
{
    if (list->first == NULL)
        return;
    
    Node* currentNode = list->first;
    while (currentNode != NULL)
    {
        printf("%d\n", currentNode->value);
        currentNode = currentNode->next;
    }
}

Node* getLast(LinkedList* list)
{
    if (list->first == NULL)
        return NULL;

    Node* lastNode = list->first;
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    
    return lastNode;
}

void append(LinkedList* list, int value)
{
    Node* lastNode = getLast(list);
    if (lastNode == NULL)
    {
        list->first = malloc(sizeof(Node));
        list->first->value = value;
        list->first->prev = NULL;
        list->first->next = NULL;
        return;
    }

    lastNode->next = malloc(sizeof(Node));
    lastNode->next->value = value;
    lastNode->next->prev = lastNode;
    lastNode->next->next = NULL;
    return;
}

void removeLast(LinkedList* list)
{
    if (list->first == NULL)
        return;
    
    if (list->first->next == NULL)
    {
printf("remove %d\n", list->first->value);
        free(list->first);
        list->first = NULL;
        return;
    }

    Node* beforeLast = getLast(list)->prev;
printf("remove %d\n", beforeLast->next->value);
    free(beforeLast->next);
    beforeLast->next = NULL;
}

void destructList(LinkedList* list)
{
    Node* lastNode = getLast(list);
    while (lastNode != NULL)
    {
        removeLast(list);
        lastNode = getLast(list);
    }
}