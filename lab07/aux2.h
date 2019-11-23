#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME 14
#define MAX_CLASS 10

typedef struct _item{
    char champ_name[MAX_NAME];
    int damage;
    char champ_class[MAX_CLASS];
}Item;

typedef struct _champ{
    char name[MAX_NAME];
    char class[MAX_CLASS];
    int damage;
    int life;
    int level;
}Champion;

typedef struct _col {
    int size;
    int level;
    Champion *col;
}Collection;

/* Aloca a colecao e inicializa seus campos */
Collection *create_collection(const int K);

/* Comparador de campeoes. Sempre havera diferenca devido aos diferentes nomes
    retorna 1 se champ1 tem mais prioridade que champ2
    retorna 0 caso champ1 nao tem mais prioridade que champ2 */
int comp_champion(const Champion champ1, const Champion champ2);

/* Atualiza colecao de campeoes apos a modificacao de seus campos. Complexidade: O(log n) */
void update_collection(Collection *collection);

/* Insere novo campeao na colecao de campeoes. Após o término, esta funcao chama o update */
void add_champ_to_col(Collection *collection, const Champion champ);

/* Remove campeao com zero de vida da colecao de campeoes. Após o termino, esta funcao chama o update */
void rm_champ_from_col(Collection *collection);

// ---------------------- Outras funções -------------------------- //
Champion constructChamp(char* name, char* class, int dmg, int life);
void printCollection(Collection* collection);
int computeLevel(int damage, int life);