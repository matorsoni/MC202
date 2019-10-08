/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include "lista.h"

/* Funções que capturam as entradas do teclado e realizam as manipulações correspondentes */
void parseCodeA(Lista* listArray);
void parseCodeC(Lista* listArray, int* listCount);
void parseCodeD(Lista* listArray);
void parseCodeE(Lista* listArray);
void parseCodeF(Lista* listArray);
void parseCodeI(Lista* listArray);
void parseCodeJ(Lista* listArray);
void parseCodeT(Lista* listArray);
void parseCodeX(Lista* listArray);

int main()
{
    Lista listArray[MAX_MERCADOS];
    int listCount = 0;

    int N;
    scanf("%d", &N);

    for (int i=0; i<N; i++)
    {
        char code;
        scanf(" %c", &code);
        
        switch (code)
        {
        case 65: // A
            parseCodeA(listArray);
            break;
        
        case 67: // C
            parseCodeC(listArray, &listCount);
            break;
        
        case 68: // D
            parseCodeD(listArray);
            break;
        
        case 69: // E
            parseCodeE(listArray);
            break;
        
        case 70: // F
            parseCodeF(listArray);
            break;
        
        case 73: // I
            parseCodeI(listArray);
            break;

        case 74: // J
            parseCodeJ(listArray);
            break;
        
        case 84: // T
            parseCodeT(listArray);
            break;
        
        case 88: // X
            parseCodeX(listArray);
            break;
        
        default:
            break;
        }
    }

    for (int index=0; index < listCount; index++)
    {
        if (listArray[index].primeiro != NULL)
        {
            printf("Lista %d:\n", index);
            imprimirLista(&listArray[index]);
        }

        destructList(&listArray[index]);
    }
   
    return 0;
}

void parseCodeA(Lista* listArray)
{
    int index;
    char itemName[MAX_NOME];
    scanf("%d", &index);
    scanf("%s", itemName);
    Item item = parseItemInput();

    adicionarAntes(&listArray[index], item, itemName);
}

void parseCodeC(Lista* listArray, int* listCount)
{
    int index = *listCount;
    listArray[index].primeiro = NULL;
    Item item = parseItemInput();
    append(&listArray[index], item);
    (*listCount)++;
}

void parseCodeD(Lista* listArray)
{
    int index;
    char itemName[MAX_NOME];
    scanf("%d", &index);
    scanf("%s", itemName);
    Item item = parseItemInput();

    adicionarDepois(&listArray[index], item, itemName);
}

void parseCodeE(Lista* listArray)
{
    int index, quantity;
    char itemName[MAX_NOME];
    scanf("%d", &index);
    scanf("%s", itemName);
    scanf("%d", &quantity);

    diminuirQuantidade(&listArray[index], itemName, quantity);
}

void parseCodeF(Lista* listArray)
{
    int index;
    scanf("%d", &index);
    Item item = parseItemInput();

    adicionarFim(&listArray[index], item);
}

void parseCodeI(Lista* listArray)
{
    int index;
    scanf("%d", &index);

    inverterLista(&listArray[index]);
}

void parseCodeJ(Lista* listArray)
{
    int index_1, index_2;
    scanf("%d", &index_1);
    scanf("%d", &index_2);

    juntarListas(&listArray[index_1], &listArray[index_2]);
    destructList(&listArray[index_2]);
}

void parseCodeT(Lista* listArray)
{
    int index_1, index_2;
    char itemName_1[MAX_NOME], itemName_2[MAX_NOME];
    scanf("%d", &index_1);
    scanf("%d", &index_2);
    scanf("%s", itemName_1);
    scanf("%s", itemName_2);

    trocarItens(&listArray[index_1], &listArray[index_2], itemName_1, itemName_2);
}

void parseCodeX(Lista* listArray)
{
    int index;
    char itemName[MAX_NOME];
    scanf("%d", &index);
    scanf("%s", itemName);

    excluirItem(&listArray[index], itemName);
}