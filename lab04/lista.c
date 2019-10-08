/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include "lista.h"

void imprimirLista(Lista* lista)
{
    if (lista->primeiro == NULL)
        return;

    No* currentNode = lista->primeiro;
    while (currentNode != NULL)
    {
        printItem(currentNode->produto);
        currentNode = currentNode->prox;
    }
    
}

void juntarListas(Lista* lista_1, Lista* lista_2)
{
    if (lista_2->primeiro == NULL)
        return;
    
    No* currentNode_2;
    // Para cada item da lista 2, testar se este já pertence à lista 1
    for (currentNode_2 = lista_2->primeiro; currentNode_2 != NULL; currentNode_2 = currentNode_2->prox)
    {
        char* itemName_2 = currentNode_2->produto.nome;
        int itemQuantity_2 = currentNode_2->produto.quantidade;
        No* foundNode_1 = findItem(lista_1, itemName_2);

        // Se o item atual não pertence à lista 1, adicioná-lo ao fim da lista 1
        // Caso ele já pertença à lista 1, somar a sua quantidade  
        if (foundNode_1 == NULL)
            append(lista_1, currentNode_2->produto);
        else
            foundNode_1->produto.quantidade += itemQuantity_2;        
    }
}

void trocarItens(Lista* lista_1, Lista* lista_2, char* nome_item1, char* nome_item2)
{
    No* node_1 = findItem(lista_1, nome_item1);
    No* node_2 = findItem(lista_2, nome_item2);

    if ((node_1 != NULL) && (node_2 != NULL))
    {
        Item aux = node_1->produto;
        node_1->produto = node_2->produto;
        node_2->produto = aux;
    }
}

void adicionarFim(Lista* lista, Item item)
{
    append(lista, item);
}

void adicionarAntes(Lista* lista, Item item, char* nome_item)
{
    No* foundItem = findItem(lista, nome_item);
    if (foundItem == NULL)
        return;

    if (foundItem == lista->primeiro)
    {
        lista->primeiro = malloc(sizeof(No));
        lista->primeiro->produto = item;
        lista->primeiro->prox = foundItem;
        return;
    }

    // Encontrar o No* do item anterior ao item dado como entrada (nome_item)
    No* previousItem = lista->primeiro;
    while (previousItem->prox != NULL)
    {
        if (previousItem->prox == foundItem)
        {
            previousItem->prox = malloc(sizeof(No));
            previousItem->prox->produto = item;
            previousItem->prox->prox = foundItem;
            break;
        }

        previousItem = previousItem->prox;
    }
}

void adicionarDepois(Lista* lista, Item item, char* nome_item)
{
    No* foundItem = findItem(lista, nome_item);
    if (foundItem == NULL)
        return;

    if (foundItem->prox == NULL)
        append(lista, item);
    else
    {
        No* aux = foundItem->prox;
        foundItem->prox = malloc(sizeof(No));
        foundItem->prox->produto = item;
        foundItem->prox->prox = aux;
    } 
}

void diminuirQuantidade(Lista* lista, char* nome_item, int qtd)
{
    No* foundItem = findItem(lista, nome_item);
    if (foundItem == NULL)
        return;
    
    foundItem->produto.quantidade -= qtd;
    if (foundItem->produto.quantidade <= 0)
        excluirItem(lista, nome_item);
}

void excluirItem(Lista* lista, char* nome_item)
{
    if (lista->primeiro == NULL)
        return;
    
    if (lista->primeiro->prox == NULL)
    {
        if (compareStrings(lista->primeiro->produto.nome, nome_item))
            popLast(lista);
        return;
    }

    if (compareStrings(lista->primeiro->produto.nome, nome_item))
    {
        No* aux = lista->primeiro->prox;
        free(lista->primeiro);
        lista->primeiro = aux;
        return;
    }

    No* currentNode = lista->primeiro->prox;
    No* previousNode = lista->primeiro;
    while (currentNode != NULL)
    {
        if (compareStrings(currentNode->produto.nome, nome_item))
        {
            previousNode->prox = currentNode->prox;
            free(currentNode);
            break;
        }

        currentNode = currentNode->prox;
        previousNode = previousNode->prox;
    }    
}

void inverterLista(Lista* lista)
{
    if (lista->primeiro == NULL)
        return;
    if (lista->primeiro->prox == NULL)
        return;
    
    Lista inverted;
    inverted.primeiro = NULL;
    int lastItemQuantity = getLastElement(lista)->produto.quantidade;

    while (lista->primeiro != NULL)
    {
        if (getLastElement(lista)->produto.quantidade < lastItemQuantity)
        {
            char* itemName = getLastElement(lista)->produto.nome;
            int itemQuantity = getLastElement(lista)->produto.quantidade;
            append(&inverted, constructItem(itemName, itemQuantity + lastItemQuantity));
        }
        else
            append(&inverted, getLastElement(lista)->produto);    

        popLast(lista);
    }

    lista->primeiro = inverted.primeiro;
}

// ---------------------------------- Utilidades para o struct Lista ----------------------------------
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

void popLast(Lista* lista)
{
    if (lista->primeiro == NULL)
        return;

    if (lista->primeiro->prox == NULL)
    {
        free(lista->primeiro);
        lista->primeiro = NULL;
        return;
    }

    No* beforeLastNode = lista->primeiro;
    while (beforeLastNode->prox->prox != NULL)
        beforeLastNode = beforeLastNode->prox;

    free(beforeLastNode->prox);
    beforeLastNode->prox = NULL;
}

void destructList(Lista* lista)
{
    while (lista->primeiro != NULL)
        popLast(lista);
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

void setItem(No* node, Item item);

// ----------------------- Utilidades para o struct Item ------------------------
Item constructItem(char* name, int quantity)
{
    Item item;
    item.quantidade = quantity;
    strcpy(item.nome, name);
    return item;
}

void printItem(Item item)
{
    printf("item: %s, quantidade: %d\n", item.nome, item.quantidade);
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

void cleanStringInput(char* rawString, char* output)
{
    int inputIndex = 0, outputIndex = 0;
	char outputString[MAX_NOME];
    while(rawString[inputIndex] != '\0')
	{
		if((rawString[inputIndex] == '(') || (rawString[inputIndex] == ',') || (rawString[inputIndex] == ')'))
		{
			inputIndex++;
			continue;
		}   
		else
		{	
			outputString[outputIndex] = rawString[inputIndex];
			outputIndex++;
			inputIndex++;
		}
	}

	outputString[outputIndex] = '\0';
    strcpy(output, outputString);
}

Item parseItemInput()
{
    char string_1[MAX_NOME+2]; // MAX_NOME+2 para levar em conta os chars "(" e ","
    char string_2[MAX_NOME+1]; // MAX_NOME+1 para levar em conta o char ")"
    scanf("%s", string_1);
    scanf("%s", string_2);

    char itemName[MAX_NOME];
    char itemQuantityString[MAX_NOME];
    cleanStringInput(string_1, itemName);
    cleanStringInput(string_2, itemQuantityString);

    return constructItem(itemName, atoi(itemQuantityString));
}