#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

/* Struct que contém o nó raiz da árvore binária que define as chaves (brackets) do campeonato */
typedef struct BinaryTree
{
    no* root;
    int height;
} BinaryTree;

// ====================== Declaração de utilidades de BinaryTree ======================
/* Imprime as folhas da arvore, isto é, todos os jogadores. Útil para debug */
void printBracket(no* root);

/* Aloca todos os nós da árvore binária, que serão em seguida preenchidos com os dados de entrada */
void constructBracket(BinaryTree* bracket);

/* Desaloca todos os nós da árvore binária */
void destructBracket(BinaryTree* bracket);

/* Retorna a folha de um jogador à partir de um índice, tal que 0 <= index < número total de jogadores */
no* findPlayerByIndex(BinaryTree* bracket, int index);

/* Insere um jogador em uma folha da árvore, à partir dos dados de entrada */
void insertPlayerByGroup(BinaryTree* bracket, int groupIndex, char* name, char* country, char group);

/* Realiza a permutação de jogadores para que as mesmas nacionalidades se enfrentem na primeira rodada */
void balanceBracket(BinaryTree* bracket);

/* Dado um país e um nome, encontra o jogador de mesmo país e de nome diferente */
no* findCompatriot(BinaryTree* bracket, char* country, char* name);

/* Troca as informações dos nós dados como entrada */
void swapPlayers(BinaryTree* bracket, no* player, no* newPlayer);

/* Dados 2 nomes de jogadores, encontra o nó cujos filhos são esses jogadores */
void findParentNode(no* node, char* name_1, char* name_2, no** output);

/* Recebe os dados de uma partida e avança o vencedor para o próximo nó da árvore */
void updateBracket(BinaryTree* bracket, char* name_1, int score_1, int time_1, char* name_2, int score_2, int time_2);

/* Imprime o grupo especificado na entrada, no formato exigido no enunciado */
void printGroup(no* root, char group);

/* Imprime os dados do campeão, no formato exigido no enunciado */
void printFinalResult(BinaryTree* bracket);

// ====================== Declaração de utilidades gerais ======================
/* Retorna 1 se as strings são iguais, 0 caso contrário */
bool compareStrings(char* p_string1, char* p_string2);

/* Calcula o logaritmo na base 2 de um inteiro X (resultado exato apenas se X é potência de 2) */
int logBase2(int x);

/* Calcula 2 elevado ao expoente inteiro dado como entrada */
int powerOf2(int exponent);

/* Converte um inteiro n em sua representação binária, */
/* retornando um vetor de 0's e 1's cujo tamanho é dado como entrada */
int* intToBinary(int n, int digits);

// ---------------------- função main ----------------------
int main()
{
    int players;
    scanf("%d", &players);

    // Inicializa a chave do campeonato
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

    // Realiza as permutas para equilibrar as nacionalidades nas primeiras partidas
    balanceBracket(&bracket);

    // Faz evoluir os grupos à partir dos dados das partidas
    // Observação: número de partidas = número total de nós (menos a raíz) - número de folhas (número de jogadores)
    int totalNodes = powerOf2(bracket.height + 1) - 1;
    for (int match = 0; match < totalNodes - players; match++)
    {
        // Ler as entradas dos dados de cada partida
        char name_1[MAX], name_2[MAX];
        int score_1, time_1, score_2, time_2;
        scanf("%s %d %d %s %d %d", name_1, &score_1, &score_2, name_2, &time_1, &time_2);
        updateBracket(&bracket, name_1, score_1, time_1, name_2, score_2, time_2);
    }

    // Imprime o reultado final
    printFinalResult(&bracket);

    return 0;
}

// ====================== Implementação de utilidades de BinaryTree ======================
void printBracket(no* root)
{
    if (root == NULL)
        return;
    
    printBracket(root->esq);
    printBracket(root->dir);

    if ((root->g == 65) || (root->g == 66)){
        printf("Player:\n");
        printf("%s %s %c\n", root->nome, root->pais, root->g);
    }
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
    // sendo "players" o número de competidores (folhas) da chave.
    // O índice 0 corresponde ao primeiro jogador do grupo A,
    // enquanto o índice players-1 corresponde ao último do grupo B. 
    no* target = bracket->root;
    int digits = bracket->height;
    int players = powerOf2(digits);
    if ((index < 0) || (index >= players))
        return NULL;
    
    // Os dígitos da representação binária corresondem às direções nas quais exploramos a árvore
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

void balanceBracket(BinaryTree* bracket)
{
    if (bracket->root == NULL)
        return;

    int players = powerOf2(bracket->height);
    // Itera cada par de jogadores
    for (int pair = 0; pair < players; pair += 2)
    {
        no* player_1 = findPlayerByIndex(bracket, pair);
        no* player_2 = findPlayerByIndex(bracket, pair+1);
        if (compareStrings(player_1->pais, player_2->pais) == false)
        {
            // Caso o adversário 2 não seja o compatriota, encontrar o compatriota e realizar a troca
            no* newPlayer_2 = findCompatriot(bracket, player_1->pais, player_1->nome);
            swapPlayers(bracket, player_2, newPlayer_2);
        }
    }
}

no* findCompatriot(BinaryTree* bracket, char* country, char* name)
{
    if (bracket->root == NULL)
        return NULL;

    no* target = NULL;
    // Itera para cada jogador, testa o nome do país de cada jogador
    int players = powerOf2(bracket->height);
    for (int p = 0; p < players; p++)
    {
        no* currentPlayer = findPlayerByIndex(bracket, p);
        if (compareStrings(currentPlayer->pais, country) == true && compareStrings(currentPlayer->nome, name) == false)
        {
            // Se o jogador atual vier do país dado como entrada e seu nome for diferente do nome dado como entrada,
            // retornar este jogador.
            target = currentPlayer;
            break;
        }
    }

    return target;
}

void swapPlayers(BinaryTree* bracket, no* player, no* newPlayer)
{
    if (bracket->root == NULL)
        return;
    
    char auxName[MAX];
    char auxCountry[MAX];

    strcpy(auxName, player->nome);
    strcpy(auxCountry, player->pais);

    strcpy(player->nome, newPlayer->nome);
    strcpy(player->pais, newPlayer->pais);

    strcpy(newPlayer->nome, auxName);
    strcpy(newPlayer->pais, auxCountry);
}

void findParentNode(no* node, char* name_1, char* name_2, no** output)
{
    if (node->esq == NULL || node->dir == NULL)
        return;
    
    // Caso uma das condições é satisfeita, escreve o nó encontrado em "output"
    bool condition_1 = compareStrings(node->esq->nome, name_1) && compareStrings(node->dir->nome, name_2);
    bool condition_2 = compareStrings(node->esq->nome, name_2) && compareStrings(node->dir->nome, name_1);
    if (condition_1 || condition_2)
        *output = node;
    else
    {
        findParentNode(node->esq, name_1, name_2, output);
        findParentNode(node->dir, name_1, name_2, output);
    }
}

void updateBracket(BinaryTree* bracket, char* name_1, int score_1, int time_1, char* name_2, int score_2, int time_2)
{
    if (bracket->root == NULL)
        return;
    if (bracket->root->esq == NULL || bracket->root->dir == NULL)
        return;
    
    no* parentNode = NULL;
    findParentNode(bracket->root, name_1, name_2, &parentNode);
    if (parentNode == NULL)
        return;

    no* player_1;
    no* player_2;
    // Preencher as pontuações dos dois adversários
    if (compareStrings(parentNode->esq->nome, name_1))
    {
        parentNode->esq->pontos = score_1;
        parentNode->esq->tempototal = time_1;
        parentNode->dir->pontos = score_2;
        parentNode->dir->tempototal = time_2;   

        player_1 = parentNode->esq;
        player_2 = parentNode->dir;
    }
    if (compareStrings(parentNode->esq->nome, name_2))
    {
        parentNode->esq->pontos = score_2;
        parentNode->esq->tempototal = time_2;
        parentNode->dir->pontos = score_1;
        parentNode->dir->tempototal = time_1;

        player_1 = parentNode->dir;
        player_2 = parentNode->esq;
    }
    
    // Determina o vencedor
    no* winner;
    if (score_1 > score_2)
        winner = player_1;
    else if (score_1 < score_2)
        winner = player_2;
    else
    {
        if (time_1 < time_2)
            winner = player_1;
        else
            winner = player_2; 
    }
    
    // Avançar o jogador vencedor para a próxima posição na chave
    strcpy(parentNode->nome, winner->nome);
    strcpy(parentNode->pais, winner->pais);
    parentNode->g = winner->g;    
}

void printGroup(no* root, char group)
{
    printf("(");

    if (root == NULL)
    {
        printf(")");
        return;
    }

    // A ordem de impressão dos grupos A e B é invertida, de forma à respeitar o formato exigido
    printf("%s ", root->nome);
    if (group == 65) // A
    {
        printGroup(root->esq, group);
        printGroup(root->dir, group);
    }
    else // B
    {
        printGroup(root->dir, group);
        printGroup(root->esq, group);
    }
    
    printf(")");
}

void printFinalResult(BinaryTree* bracket)
{
    int totalScore = 0;
    char winner[MAX];
    strcpy(winner, bracket->root->nome);

    // Calcula a pontuação total do vencedor
    no* iterator = bracket->root;
    while (iterator->esq != NULL && iterator->dir != NULL)
    {
        if (compareStrings(iterator->esq->nome, winner) == true)
            iterator = iterator->esq;
        else
            iterator = iterator->dir;

        totalScore += iterator->pontos;
    }

    // imprime a primeira linha da saída
    printf("1 %s %s %c %d\n", bracket->root->nome, bracket->root->pais, bracket->root->g, totalScore);

    // Imprime a situação dos dois grupos
    char A = 65, B = 66;
    printGroup(bracket->root->esq, A);
    printf("\n");
    printGroup(bracket->root->dir, B);
    printf("\n");
}


// ====================== Declaração de utilidades gerais ======================
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