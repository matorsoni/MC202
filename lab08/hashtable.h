#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 100

// ---- struct LinkedList ----
// Lista duplamente ligada
typedef struct Node
{
    char stone[MAX_NAME];
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct LinkedList
{
    Node* first;
}LinkedList;

// ---- Métodos de LinkedList ligada ----
/* Imprime os elementos da lista */
void printList(LinkedList* list);

/* Retorna o endereço do último nó da LinkedList */
Node* getLastElement(LinkedList* LinkedList);

/* Adiciona ao início da LinkedList a pedra dado como argumento */
void enqueue(LinkedList* LinkedList, char* stone);

/* Remove o primeiro elemento da lista */
void dequeue(LinkedList* LinkedList);

/* Destroi o objeto LinkedList, liberando toda a memória alocada no heap */
void destructList(LinkedList* LinkedList);

/* Retorna o endereço do nó que contém a pedra especificado na entrada */
Node* findItem(LinkedList* LinkedList, char* stone);

// ---- struct Hash Table ----
typedef struct HashTable
{
    LinkedList* slots;
} HashTable;

// ---- Métodos de Hash Table ----

// ---- Utilidades gerais ----
/* Retorna 1 se as strings são iguais, 0 caso contrário */
bool compareStrings(char* p_string1, char* p_string2);