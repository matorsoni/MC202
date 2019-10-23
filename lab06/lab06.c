#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================== aux.h ======================
#define MAX 30

/* Estrutura que define um competidor nos Jogos */
typedef struct _no
{
    char nome[MAX], pais[MAX];
    char g;
    int pontos;
    int tempototal;
    struct _no *esq;
    struct _no *dir;
} no;

/* Imprime o estado de um grupo de forma recursiva */
void exibe(no* grupo)
{
    printf("(");
    /* Caso o grupo nao seja vazio */
    if(grupo != NULL)
    {
        /* Imprime chave em questao */
        /* Imprime chaves subgrupo esquerdo */
        /* Imprime subgrupo direito */
        printf("%s ", grupo->nome);
        exibe(grupo->esq);
        exibe(grupo->dir);
    }

    printf(")");
}

/* Struct que contém o nó raiz da árvore binária que define as chaves (bracket) do campeonato */
typedef struct BinaryTree
{
    no* root;
    int height;
} BinaryTree;

// ====================== Declaração de utilidades de no ======================
void copyNode(no* src, no* dest);
// ====================== Declaração de utilidades de BinaryTree ======================
void printBracket(no* root);
void constructBracket(BinaryTree* bracket);
void destructBracket(BinaryTree* bracket);
no* findPlayerByIndex(BinaryTree* bracket, int index);
void insertPlayerByGroup(BinaryTree* bracket, int groupIndex, char* name, char* country, char group);
// ====================== Declaração de utilidades gerais ======================
int logBase2(int x);
int powerOf2(int exponent);
int* intToBinary(int n, int digits);

// ---------------------- função main ----------------------
int main()
{
    int players;
    scanf("%d", &players);

    BinaryTree bracket;
    bracket.root = NULL;
    bracket.height = logBase2(players);
    constructBracket(&bracket);

    // Insere os jogadores nos seus respectivos grupos, na ordem especificada na entrada
    int groupA = 0;
    int groupB = 0;
    for (int p = 0; p < players; p++)
    {
        char name[MAX], country[MAX], group;
        scanf("%s %s %c", name, country, &group);

        if (group == 65) // A
        {
            insertPlayerByGroup(&bracket, groupA, name, country, group);
            groupA++;
        }
        if (group == 66) // B
        {
            insertPlayerByGroup(&bracket, groupB, name, country, group);
            groupB++;
        }
    }



    printBracket(bracket.root);

    return 0;
}
// ====================== Implementação de utilidades de BinaryTree ======================
void printBracket(no* root)
{
    if (root == NULL)
        return;
    
    printBracket(root->esq);
    printBracket(root->dir);
    printf("Player:\n");
    printf("%s %s %c\n", root->nome, root->pais, root->g);
}

void constructBracket(BinaryTree* bracket)
{
    if (bracket->height <= 0)
        return;

    if (bracket->root == NULL)
    {
        bracket->root = malloc(sizeof(no));
        bracket->root->esq = NULL;
        bracket->root->dir = NULL;
        bracket->root->g = 88; // "X"
        constructBracket(bracket);
    }
    else
    {
        bracket->root->esq = malloc(sizeof(no));
        bracket->root->esq->esq = NULL;
        bracket->root->esq->dir = NULL;
        bracket->root->esq->g = 76; // "L"

        bracket->root->dir = malloc(sizeof(no));
        bracket->root->dir->esq = NULL;
        bracket->root->dir->dir = NULL;
        bracket->root->dir->g = 82; // "R"

        BinaryTree subTree_L;
        subTree_L.root = bracket->root->esq;
        subTree_L.height = bracket->height - 1;
        BinaryTree subTree_R;
        subTree_R.root = bracket->root->dir;
        subTree_R.height = bracket->height - 1;

        constructBracket(&subTree_L);
        constructBracket(&subTree_R);
    }
}

void destructBracket(BinaryTree* bracket)
{
    if (bracket->root == NULL)
        return;
    if ((bracket->root->esq == NULL) && (bracket->root->esq == NULL)){
        free(bracket->root);
        return;
    }

    // ....
}

no* findPlayerByIndex(BinaryTree* bracket, int index)
{
    // O índice deve ser um inteiro no intervalo [0, players-1], 
    // sendo "players" o número de competidores (folhas) da chave
    no* target = bracket->root;
    int digits = bracket->height;
    int players = powerOf2(digits);
    if ((index < 0) || (index >= players))
        return NULL;
    
    int* binary = intToBinary(index, digits);
    for (int i = 0; i < digits; i++)
    {
        if (binary[i] == 0)
            target = target->esq;
        if (binary[i] == 1)
            target = target->dir;
    }

    free(binary);
    return target;   
}

void insertPlayerByGroup(BinaryTree* bracket, int groupIndex, char* name, char* country, char group)
{
    BinaryTree subTree;
    subTree.height = bracket->height - 1;
    if (group == 65) // A
        subTree.root = bracket->root->esq;
    if (group == 66) // B
        subTree.root = bracket->root->dir;

    no* target = findPlayerByIndex(&subTree, groupIndex);
    strcpy(target->nome, name);
    strcpy(target->pais, country);
    target->g = group;
}

// ====================== Declaração de utilidades gerais ======================
int logBase2(int x)
{
    if (x < 2)
        return -1;

    int y = 2;
    int log = 1;
    while (y < x){
        y *= 2;
        log++;
    }
    
    return log;
}

int powerOf2(int exponent)
{
    int power = 1;
    for (int i = 0; i < exponent; i++)
        power *= 2;
    return power;
}

int* intToBinary(int n, int digits)
{
    int* binary = malloc(digits * sizeof(int));
    for (int index = digits - 1; index >=0; index--)
    {
        binary[index] = n % 2;
        n = n/2;
    }

    return binary;
}