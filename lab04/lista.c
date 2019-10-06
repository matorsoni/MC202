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

void juntarListas(Lista *lista_1, Lista *lista_2)
{
    if (lista_2->primeiro == NULL)
        return;
    
    No* currentNode_2;
    for (currentNode_2 = lista_2->primeiro; currentNode_2 != NULL; currentNode_2 = currentNode_2->prox)
    {
        char* itemName_2 = currentNode_2->produto.nome;
        int itemQuantity_2 = currentNode_2->produto.quantidade;
        No* foundNode_1 = findItem(lista_1, itemName_2);

        if (foundNode_1 == NULL)
            append(lista_1, currentNode_2->produto);
        else
            foundNode_1->produto.quantidade += itemQuantity_2;        
    }
}

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

No* findItem(Lista* lista, char* itemName)
{
    if (lista->primeiro == NULL)
        return NULL;
    
    No* returnNode = NULL;
    No* currentNode = lista->primeiro;
    while (currentNode != NULL)
    {
        if (compareStrings(currentNode->produto.nome, itemName))
        {
            returnNode = currentNode;
            break;
        }
        currentNode = currentNode->prox;
    }

    return returnNode;
}

// ----------------------- Utilidades para o struct Item ------------------------
Item constructItem(char* name, int quantity)
{
    Item item;
    item.quantidade = quantity;
    strcpy(item.nome, name);
    return item;
}

// ----------------------- Utilidades gerais ------------------------
bool compareStrings(char* p_string1, char* p_string2)
{
    // Retorna "true" se ambas as strings são iguais, "false" caso contrário.
    bool returnValue = true;
    int i=0;
    while(p_string1[i] != '\0')
    {
        if(p_string1[i] != p_string2[i])
        {
            returnValue = false;
            break;
        }
        i++;
    }
    // Compara se o último char de ambas strings é '\0'
    if(p_string1[i] != p_string2[i])
        returnValue = false;

    return returnValue;
}