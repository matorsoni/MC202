/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

/* Laboratório 04: Organizando as compras *
* Arquivo de Cabeçalho: lista.h *
* Descrição:   Este arquivo contém o pragma/cabeçalho das funções a serem implementadas neste laboratório. Cada  *
*              função contém uma breve descrição sobre o seu objetivo, a saída esperada e uma pequena explicação *
*              dos parâmetros de entrada.                                                                        *
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

/* Imprimir Lista                                                                            *
* Objetivo:    Imprimir os itens uma lista                                                  *
* Saída:       Não retorna nenhum valor como saida                                          *
* Parâmetros:                                                                               *
*      - Lista * lista: Ponteiro para uma lista                                             *
*/
void imprimirLista(Lista *lista);

/* Juntar Listas                                                                             *
* Objetivo:    Juntar duas listas dando prioridade à primeira                               *
* Saída:       Não retorna nenhum valor como saida                                          *
* Parâmetros:                                                                               *
*      - Lista * lista_1: Ponteiro para a primeira lista                                    *
*      - Lista * lista_2: Ponteiro para a segunda lista                                     *
*/
void juntarListas(Lista *lista_1, Lista *lista_2);

/* Trocar Itens                                                                              *
* Objetivo:    Efetuar a troca de dois itens de listas distintas                            *
* Saída:       Não retorna nenhum valor como saida                                          *
* Parâmetros:                                                                               *
*      - Lista *lista_1: Ponteiro para a primeira lista                                     *
*      - Lista *lista_2: Ponteiro para a segunda lista                                      *
*      - char *nome_item1: Nome do item da primeira lista a ser trocado                     *
*      - char *nome_item2: Nome do item da segunda lista a ser trocado                      *
*/
void trocarItens(Lista *lista_1, Lista *lista_2, char *nome_item1, char *nome_item2);

/* Adicionar Fim                                                                             *
* Objetivo:    Adicionar um item no fim de uma lista                                        *
* Saída:       Não retorna nenhum valor como saida                                          *
* Parâmetros:                                                                               *
*      - Lista *lista: Ponteiro para a lista em que o item deve ser adicionado              *
*      - Item item: Novo item a ser adicionado na lista                                     *
*/
void adicionarFim(Lista *lista, Item item);

/* Adicionar Antes                                                                          *
* Objetivo:    Adicionar um item antes de um item especifico da lista                      *
* Saída:       Não retorna nenhum valor como saida                                         *
* Parâmetros:                                                                              *
*      - Lista *lista: Ponteiro para a lista em que o item deve ser adicionado             *
*      - Item item: Novo item a ser adicionado na lista                                    *
*      - char *nome_item: Nome do item ao qual o novo item deve ser adicionado antes       *
*/
void adicionarAntes(Lista *lista, Item item, char *nome_item);

/* Adicionar Depois                                                                         *
* Objetivo:    Adicionar um item depois de um item especifico da lista                     *
* Saída:       Não retorna nenhum valor como saida                                         *
* Parâmetros:                                                                              *
*      - Lista *lista: Ponteiro para a lista em que o item deve ser adicionado             *
*      - Item item: Novo item a ser adicionado na lista                                    *
*      - char *nome_item: Nome do item ao qual o novo item deve ser adicionado depois      *
*/
void adicionarDepois(Lista*lista, Item item, char *nome_item);

/* Diminuir Quantidade                                                                     *
* Objetivo:    Remover uma quantidade especifica de um item                               *
* Saída:       Não retorna nenhum valor como saida                                        *
* Parâmetros:                                                                             *
*      - Lista *lista: Ponteiro para a lista que o item pertence                          *
*      - char *nome_item: Nome do item cujas unidades serão removidas                     *
*      - int qtd: Quantidade de unidades a serem removidas                                *
*/
void diminuirQuantidade(Lista *lista, char *nome_item, int qtd);

/* Excluir Item                                                                            *
* Objetivo:    Excluir um item especifico de uma lista                                    *
* Saída:       Não retorna nenhum valor como saida                                        *
* Parâmetros:                                                                             *
*      - Lista *lista: Ponteiro para a lista que o item pertence                          *
*      - char *nome_item: Nome do item que será excluído                                  *
*/
void excluirItem(Lista *lista, char *nome_item);

/* Inverter Lista                                                                          *
* Objetivo:    Inverter uma lista adicionando unidades aos itens quando necessario        *
* Saída:       Nesta funcao fica a criterio do programador o tipo de retorno              *
* Parâmetros:                                                                             *
*      - Lista *lista: Ponteiro para a lista a ser invertida                              *
*/
void inverterLista(Lista *lista);


// ----------------------- Utilidades para o struct Lista ------------------------
No* getLastElement(Lista* lista);
void append(Lista* lista, Item item);
void popLast(Lista* lista);
void destructList(Lista* lista);
No* findItem(Lista* lista, char* itemName);
void setItem(No* node, Item item);

// ----------------------- Utilidades para o struct Item ------------------------
Item constructItem(char* name, int quantity);

// ----------------------- Utilidades gerais ------------------------
bool compareStrings(char* p_string1, char* p_string2);