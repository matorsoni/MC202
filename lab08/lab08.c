#include "hashtable.h"

/* Mestre dos Magos solicita uma pedra e imprime seu nome (se esta for encontrada) */
void commandM(HashTable* ht, bool* success);

/* Presto cria novas pedras */
void commandP(HashTable* ht);

/* Tiamat afasta o vingador e destrói algumas pedras */
void commandT(HashTable* ht, int* vingador);

int main()
{
    int vingador, maxStones, currentStones;
    scanf("%d", &vingador);
    scanf("%d", &maxStones);
    scanf("%d", &currentStones);
    
    // Aloca a hash table e a preenche com as pedras dadas na entrada 
    HashTable hashtable;
    constructHashTable(&hashtable, 17);

    for (int i = 0; i < currentStones; ++i)
    {
        int key;
        char stone[MAX_NAME];
        scanf("%d %s", &key, stone);
        insertStone(&hashtable, key, stone);
    }

    // Loop que realiza cada comando do Mestre dos Magos
    int commands;
    scanf("%d", &commands);
    for (int i = 0; i < commands; ++i)
    {
        // Checa se a distância do vingador é zero
        if (vingador == 0)
        {
            printf("F\n");
            return 0;
        }

        char c;
        scanf(" %c", &c);
        if (c == 77) // M
        {
            // Vingador anda uma unidade de distância
            vingador--;

            // Finaliza o programa se a função commandM falhar
            bool success;
            commandM(&hashtable, &success);
            if (!success)
            {
                printf("F\n");
                return 0;
            }
        }
        else if (c == 80) // P
            commandP(&hashtable);

        else // T
            commandT(&hashtable, &vingador);  
    }

    // Caso o programa não tenha encerrado até aqui, imprimir T 
    printf("T\n");

    destructHashTable(&hashtable);

    return 0;
}

void commandM(HashTable* ht, bool* success)
{
    int key;
    scanf("%d", &key);
    Node* node = findStone(ht, key);
    if (node == NULL)
        *success = false;
    else
    {
        *success = true;
        printf("%s\n", node->stone);
    }
}

void commandP(HashTable* ht)
{
    int stones;
    scanf("%d", &stones);
    for (int s = 0; s < stones; s++)
    {
        int key;
        char stone[MAX_NAME];
        scanf("%d %s", &key, stone);
        insertStone(ht, key, stone);
    }
}

void commandT(HashTable* ht, int* vingador)
{
    int deltaVingador;
    scanf("%d", &deltaVingador);
    *vingador += deltaVingador;

    int stones;
    scanf("%d", &stones);
    for (int s = 0; s < stones; s++)
    {
        int key;
        scanf("%d", &key);
        deleteStone(ht, key);
    }
}