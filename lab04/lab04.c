/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include "lista.h"

int main()
{
    Lista lista;
    lista.primeiro = NULL;

    Item item = constructItem("bla", 1);
    Item item2 = constructItem("bli", 10);

    append(&lista, item);
    append(&lista, item2);

    imprimirLista(&lista);
    destructList(&lista);
/*
    No* i = malloc(sizeof(No));
    printf("%p\n", (void*)i);
    free(i);
    i = NULL;
    printf("%p\n", (void*)i);
    return 0;
*/

}