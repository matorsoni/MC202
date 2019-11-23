#include "aux2.h"

int main()
{
///* verdadeira main usada no lab07
    int champs;
    scanf("%d", &champs);

    Collection collection;
    collection.col = malloc(champs * sizeof(Champion));
    collection.size = 0;

    for (int c = 0; c < champs; c++)
    {
        char name[MAX_NAME], class[MAX_CLASS];
        int damage, life;
        scanf(" %s %s", name, class);
        scanf("%d %d", &damage, &life);

        Champion champ = constructChamp(name, class, damage, life);
        int index = collection.size;
        collection.col[index] = champ;
        collection.size++;
    }

    printCollection(&collection);
//*/

/* Testes em geral
    double d = 700.0/3;
    int i = floor(d);
    printf("floor(%lf) = %d\n", d, i);
*/
    return 0;
}

/* ----- Implementação das funções declaradas em aux.h ----- */
// Funções originais do header
Collection *create_collection(const int K);
int comp_champion(const Champion champ1, const Champion champ2);
void update_collection(Collection *collection);
void add_champ_to_col(Collection *collection, const Champion champ);
void rm_champ_from_col(Collection *collection);

// Outras funções
Champion constructChamp(char* name, char* class, int dmg, int life)
{
    Champion champ;
    strcpy(champ.name, name);
    strcpy(champ.class, class);
    champ.damage = dmg;
    champ.life = life;
    champ.level = computeLevel(dmg, life);
    return champ;
}

void printCollection(Collection* collection)
{
    for (int i=0; i < collection->size; i++)
    {
        printf("Champion: %s %s %d %d %d\n", collection->col[i].name, collection->col[i].class, collection->col[i].damage, collection->col[i].life, collection->col[i].level);
    }
}

int computeLevel(int damage, int life)
{
    return floor( 2*((double)damage + (double)life)/3.0 ); // algo ta errado
}
