/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include "lista.h"

void imprimirLista(Lista *lista)
{
    if (lista->primeiro != NULL)
    {
        No* currentNode = lista->primeiro;
        while (currentNode != NULL)
        {
            char* name = currentNode->produto.nome;
            int quantity = currentNode->produto.quantidade;
            printf("item: %s, quantidade: %d\n", name, quantity);
            currentNode = currentNode->prox;
        }
    }
}

void juntarListas(Lista *lista_1, Lista *lista_2);

void trocarItens(Lista *lista_1, Lista *lista_2, char *nome_item1, char *nome_item2);

void adicionarFim(Lista *lista, Item item);

void adicionarAntes(Lista *lista, Item item, char *nome_item);

void adicionarDepois(Lista*lista, Item item, char *nome_item);

void diminuirQuantidade(Lista *lista, char *nome_item, int qtd);

void excluirItem(Lista *lista, char *nome_item);

void inverterLista(Lista *lista);

// ---------------------------------- Utilidades para o struct Lista ----------------------------------
void destructList(Lista* lista)
{
    if (lista->primeiro == NULL)
    { 
printf("empty list\n"); // Só pra debug, apagar depois
        return;
    }
    
    if (lista->primeiro->prox == NULL)
    {
printf("remove (%s, %d)\n", lista->primeiro->produto.nome, lista->primeiro->produto.quantidade); // Só pra debug, apagar depois
        free(lista->primeiro);
        lista->primeiro = NULL;
        return;
    }

    No* beforeLastNode = lista->primeiro;
    while (beforeLastNode->prox->prox != NULL)
        beforeLastNode = beforeLastNode->prox;

printf("remove (%s, %d)\n", beforeLastNode->prox->produto.nome, beforeLastNode->prox->produto.quantidade); // Só pra debug, apagar depois
    free(beforeLastNode->prox);
    beforeLastNode->prox = NULL;

    destructList(lista);
}

No* getLastElement(Lista* lista)
{
    if (lista->primeiro == NULL)
        return NULL;
    
    No* lastNode = lista->primeiro;
    while (lastNode->prox != NULL)
        lastNode = lastNode->prox;
    
    return lastNode;
}
void append(Lista* lista, Item item)
{
    if (lista->primeiro == NULL)
    {
        lista->primeiro = malloc(sizeof(No));
        lista->primeiro->produto = item;
        lista->primeiro->prox = NULL;
    }
    else
    {
        No* lastNode = getLastElement(lista);
        lastNode->prox = malloc(sizeof(No));
        lastNode->prox->produto = item;
        lastNode->prox->prox = NULL;
    }
}


// ----------------------- Utilidades para o struct Item ------------------------
Item constructItem(char* name, int quantity)
{
    Item item;
    item.quantidade = quantity;
    strcpy(item.nome, name);
    return item;
}