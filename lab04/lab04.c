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
    Lista lista1, lista2;
    lista1.primeiro = NULL;
    lista2.primeiro = NULL;

    Item item1 = constructItem("bla", 1);
    Item item2 = constructItem("ble", 10);
    Item item3 = constructItem("bli", 100);
    Item item4 = constructItem("blo", 1000);
    Item item5 = constructItem("blu", 10000);
    Item item6 = constructItem("cla", 2);
    Item item7 = constructItem("cle", 20);
    Item item8 = constructItem("cli", 200);
    Item item9 = constructItem("clo", 2000);
    Item item10 = constructItem("clu", 20000);

    append(&lista1, item1);
    append(&lista1, item2);
    append(&lista1, item3);
    append(&lista1, item4);
    append(&lista1, item5);
    imprimirLista(&lista1);
    printf("----\n");

    adicionarFim(&lista1, item7);
    adicionarAntes(&lista1, item6, "cle");
    adicionarDepois(&lista1, item8, "cle");
    imprimirLista(&lista1);
    printf("----\n");

    diminuirQuantidade(&lista1, "cli", 210);
    excluirItem(&lista1, "cle");
    imprimirLista(&lista1);
    printf("----\n");

    inverterLista(&lista1);
    imprimirLista(&lista1);
    printf("----\n");

    popLast(&lista1);
    popLast(&lista1);
    imprimirLista(&lista1);
    printf("----\n");

    destructList(&lista1);
    destructList(&lista2);

    return 0;
}