#include "hashtable.h"

// ---- Métodos de LinkedList ligada ----
void printList(LinkedList* list)
{
    printf("List:\n");
    if (list->first == NULL)
        return;
    Node* currentNode = list->first;
    while (currentNode != NULL)
    {
        printf("%s\n", currentNode->stone);
        currentNode = currentNode->next;
    }
}

Node* getLastElement(LinkedList* list)
{
    if (list->first == NULL)
        return NULL;

    Node* lastNode = list->first;
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    
    return lastNode;
}

void enqueue(LinkedList* list, char* stone)
{
    if (list->first == NULL)
    {
        list->first = malloc(sizeof(Node));
        strcpy(list->first->stone, stone);
        list->first->prev = NULL;
        list->first->next = NULL;
    }
    else
    {
        Node* newNode = malloc(sizeof(Node));
        strcpy(newNode->stone, stone);
        newNode->prev = NULL;
        newNode->next = list->first;
        list->first = newNode;
    }
}

void dequeue(LinkedList* list)
{
    if (list->first == NULL)
        return;
    if (list->first->next == NULL)
    {
        free(list->first);
        list->first = NULL;
        return;
    }

    Node* second = list->first->next;
    free(list->first);
    list->first = second;
    list->first->prev = NULL;
}

void destructList(LinkedList* list)
{
    while (list->first != NULL)
        dequeue(list);
}

Node* findItem(LinkedList* list, char* stone)
{
    if (list->first == NULL)
        return NULL;
    
    Node* returnNode = NULL; // Retorna NULL caso não seja encontrado o nome dado como entrada.
    Node* currentNode = list->first;
    while (currentNode != NULL)
    {
        if (compareStrings(currentNode->stone, stone)){
            returnNode = currentNode;
            break;
        }
        currentNode = currentNode->next;
    }

    return returnNode;
}

// ---- Métodos de Hash Table ----

// ---- Utilidades gerais ----
bool compareStrings(char* p_string1, char* p_string2)
{
    bool returnValue = true;
    int i = 0;
    while(p_string1[i] != '\0')
    {
        if(p_string1[i] != p_string2[i]){
            returnValue = false;
            break;
        }
        i++;
    }
    // Verifica se o último char de ambas strings é '\0'
    if(p_string1[i] != p_string2[i])
        returnValue = false;

    return returnValue;
}