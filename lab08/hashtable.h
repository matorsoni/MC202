#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 100

// ---- struct LinkedList ----
// Lista duplamente ligada
typedef struct Node
{
    int key;
    char stone[MAX_NAME];
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct LinkedList
{
    Node* first;
}LinkedList;

// ---- Métodos de LinkedList ligada ----
/* Imprime os elementos da lista (útil para debug) */
void printList(LinkedList* list);

/* Retorna o endereço do último nó da LinkedList */
Node* getLastElement(LinkedList* list);

/* Adiciona ao início da LinkedList a pedra dado como argumento */
void enqueue(LinkedList* list, int key, char* stone);

/* Remove o primeiro elemento da lista */
void dequeue(LinkedList* list);

/* Remove a pedra cuja chave é dada como entrada */
void removeStone(LinkedList* list, int key);

/* Destroi o objeto LinkedList, liberando toda a memória alocada no heap */
void destructList(LinkedList* LinkedList);

/* Retorna o endereço do nó que contém a pedra especificado na entrada */
Node* findKey(LinkedList* LinkedList, int key);

// ---- struct Hash Table ----
typedef struct HashTable
{
    int slots;
    LinkedList* slotBuffer;
} HashTable;

// ---- Métodos de Hash Table ----
/* Imprime todas as listas que compõem a hash table (útil para debug) */
void printHashTable(HashTable* ht);

/* Função de Hash */
int hashFunction(int key, int slots);

/* Aloca e inicializa a Hash table */
void constructHashTable(HashTable* ht, int slots);

/* Desaloca e limpa a memória de uma Hash table */
void destructHashTable(HashTable* ht);

/* Insere uma pedra e sua chave na Hash table */
void insertStone(HashTable* ht, int key, char* stone);

/* Remove uma pedra da Hash table */
void deleteStone(HashTable* ht, int key);

/* Busca uma pedra na Hash table e retorna o ponteiro do seu nó */
Node* findStone(HashTable* ht, int key);

// ---- Utilidades gerais ----
/* Retorna 1 se as strings são iguais, 0 caso contrário */
bool compareStrings(char* p_string1, char* p_string2);