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
        //printf("%d -> %s\n", currentNode->key, currentNode->stone);
        printf("|prev: %p | %d -> %s | next: %p |\n", (void*)currentNode->prev, currentNode->key, currentNode->stone, (void*)currentNode->next);
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

void enqueue(LinkedList* list, int key, char* stone)
{
    if (list->first == NULL)
    {
        list->first = malloc(sizeof(Node));
        strcpy(list->first->stone, stone);
        list->first->key = key;
        list->first->prev = NULL;
        list->first->next = NULL;
    }
    else
    {
        Node* newNode = malloc(sizeof(Node));
        strcpy(newNode->stone, stone);
        newNode->key = key;
        newNode->prev = NULL;
        newNode->next = list->first;
        list->first->prev = newNode;
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

void removeStone(LinkedList* list, int key)
{
    Node* node = findKey(list, key);
    if (node == NULL)
        return;
    // Caso seja o primeiro nó elemento da lista
    if (node->prev == NULL){
        dequeue(list);
        return;
    }
    // Caso seja o último nó da lista
    if (node->next == NULL){
        node->prev->next = NULL;
        free(node);
        return;
    }
    
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

void destructList(LinkedList* list)
{
    while (list->first != NULL)
        dequeue(list);
}

Node* findKey(LinkedList* list, int key)
{
    if (list->first == NULL)
        return NULL;
    
    Node* returnNode = NULL; // Retorna NULL caso não seja encontrado o nome dado como entrada.
    Node* currentNode = list->first;
    while (currentNode != NULL)
    {
        if (currentNode->key ==  key){
            returnNode = currentNode;
            break;
        }
        currentNode = currentNode->next;
    }

    return returnNode;
}

// ---- Métodos de Hash Table ----
void printHashTable(HashTable* ht)
{
    for (int i = 0; i < ht->slots; i++){
        printf("Slot %d ", i);
        printList(&(ht->slotBuffer[i]));
    }
}

int hashFunction(int key, int slots)
{
    return key % slots;
}

void constructHashTable(HashTable* ht, int slots)
{
    ht->slots = slots;
    ht->slotBuffer = malloc(slots * sizeof(LinkedList));
    for (int i = 0; i < slots; i++)
        (ht->slotBuffer[i]).first = NULL;
}

void destructHashTable(HashTable* ht)
{
    for (int i = 0; i < ht->slots; i++)
        destructList(&(ht->slotBuffer[i]));
    free(ht->slotBuffer);
}

void insertStone(HashTable* ht, int key, char* stone)
{
    int slot = hashFunction(key, ht->slots);
    enqueue(&(ht->slotBuffer[slot]), key, stone);
}

void deleteStone(HashTable* ht, int key)
{
    int slot = hashFunction(key, ht->slots);
    removeStone(&(ht->slotBuffer[slot]), key);
}

Node* findStone(HashTable* ht, int key)
{
    int slot = hashFunction(key, ht->slots);
    return findKey(&(ht->slotBuffer[slot]), key);
}

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