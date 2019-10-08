/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_MERCADOS 30
#define MAX_NOME 60

typedef struct Item {
char nome[MAX_NOME];
int quantidade;
} Item;

typedef struct No {
struct No *prox;
Item produto;
} No;

typedef struct Lista {
No *primeiro;
} Lista;

void imprimirLista(Lista *lista);

void juntarListas(Lista *lista_1, Lista *lista_2);

void trocarItens(Lista *lista_1, Lista *lista_2, char *nome_item1, char *nome_item2);

void adicionarFim(Lista *lista, Item item);

void adicionarAntes(Lista *lista, Item item, char *nome_item);

void adicionarDepois(Lista*lista, Item item, char *nome_item);

void diminuirQuantidade(Lista *lista, char *nome_item, int qtd);

void excluirItem(Lista *lista, char *nome_item);

void inverterLista(Lista *lista);

// ----------------------- Utilidades para o struct Lista ------------------------
/* Retorna o endereço do último nó da lista */
No* getLastElement(Lista* lista);

/* Adiciona ao final da lista o item dado como argumento */
void append(Lista* lista, Item item);

/* Remove o último item da lista */
void popLast(Lista* lista);

/* Destroi o objeto Lista, liberando toda a memória alocada no heap */
void destructList(Lista* lista);

/* Retorna o endereço do nó que contém o item especificado na entrada */
No* findItem(Lista* lista, char* itemName);

// ----------------------- Utilidades para o struct Item ------------------------
/* Constroi e retorna um objeto Item à partir do nome e da quantidade fornecidos como entrada */
Item constructItem(char* name, int quantity);

/* Imprime o objeto Item conforme esperado na saída do programa */
void printItem(Item item);

// ----------------------- Utilidades gerais ------------------------
/* Retorna 1 se as strings são iguais, 0 caso contrário */
bool compareStrings(char* p_string1, char* p_string2);

/* Recebe uma rawString no formato "(x," ou "y)" e escreve apenas "x" ou "y" na outputString */
void cleanStringInput(char* rawString, char* outputString);

/* Captura uma entrada "(x, y)" e retorna o objeto Item correspondente */
Item parseItemInput();