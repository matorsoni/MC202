/*
Aluno: Mateus Orsoni Cabral
RA: 147349
Disciplina: MC202 turma H
Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int value;
    struct Node* prev;
    struct Node* next;
}Node;

typedef struct Sequence{
    Node* first;
}Sequence;

// ----------------------- Utilidades para o struct Sequence ------------------------
void printSequence(Sequence* seq);
Node* getLast(Sequence* seq);
void removeLast(Sequence* seq);
void enqueue(Sequence* seq, int value);
void dequeue(Sequence* seq);
void destructSequence(Sequence* seq);

/* Bubble sort para ordenar uma sequencia em order crescente */
void bubbleSort(Sequence* seq);

/* Remove o primeiro elemento e o adiciona ao fim da sequencia */
void cycle(Sequence* seq);

/* Cria uma Sequence à partir de valores lidos do teclado */
Sequence readSequence();

/* Calcula o número de acertos de uma dada tentativa */
int computeScore(Sequence* seq, Sequence* guess);

// ----------------------- Jogadas -----------------------
void keepSafe(Sequence* seq, Sequence* evenStack, Sequence* oddStack);
void out(Sequence* seq);
void comeBack(Sequence* seq, Sequence* evenStack, Sequence* oddStack);
void trap(Sequence* trapQueue);

// ------ Utilidades para o gerenciamento das armadilhas ------
/* Verifica se neste turno existe uma armadilha pronta para ser ativada */
bool trapIsAvailable(Sequence* trapQueue);

/* Atualiza a fila de armadilhas no fim de um turno */
void updateTrapQueue(Sequence* trapQueue);

// ======================= Main =======================
int main()
{
    // Sequencia principal de inteiros
    Sequence current;
    current.first = NULL;

    int size;
    scanf("%d", &size);
    for (int i=0; i<size; i++)
    {
        int value;
        scanf("%d", &value);
        enqueue(&current, value);
    }

    // Pilhas onde são inseridas as peças removidas temporariamente
    // Fila que guarda e gerencia as armadilhas  
    Sequence evenStack, oddStack, trapQueue;
    evenStack.first = NULL;
    oddStack.first = NULL;
    trapQueue.first = NULL;

    // Loop onde acontece o jogo
    char move = 0;
    while (move != 88) // move != "X"
    {
printSequence(&current);
        scanf(" %c", &move);
printf("move = %c\n", move);
        if (trapIsAvailable(&trapQueue))
        {
printf("Trap is available\n");
            switch (move)
            {
            case 75: // K
                keepSafe(&current, &evenStack, &oddStack);
                break;

            // Caso T apenas lê o número inteiro que segue e detona a armadilha
            case 84: // T
            {
                int trapNumber;
                scanf("%d", &trapNumber);
                dequeue(&current);
                break;
            }

            case 88: // X
                break;
            
            // Ativar armadilha
            default:
                dequeue(&current);
            }
        }
        else
        {
            switch (move)
            {
            case 67: // C
                comeBack(&current, &evenStack, &oddStack);
                break;
            
            case 75: // K
                keepSafe(&current, &evenStack, &oddStack);
                break;
            
            case 79: // O
                out(&current);
                cycle(&current);
                break;
        
            case 84: // T
                trap(&trapQueue);
                cycle(&current);
                break;
        
            default: // X 
                break;
            }
        }

        updateTrapQueue(&trapQueue);
    }

printSequence(&current);

    Sequence playerP = readSequence();
    Sequence playerI = readSequence();
    int scoreP = computeScore(&current, &playerP);
    int scoreI = computeScore(&current, &playerI);

    if (scoreP > scoreI)
        printf("P\n");
    else if (scoreP < scoreI)
        printf("I\n");
    else
        printf("E\n");
    
    destructSequence(&trapQueue);
    destructSequence(&evenStack);
    destructSequence(&oddStack);
    destructSequence(&current);
    destructSequence(&playerP);
    destructSequence(&playerI);
    return 0;
}

// ----------------------- Utilidades para o struct Sequence ------------------------
void printSequence(Sequence* seq)
{
    if (seq->first == NULL)
        return;

    printf("Current sequence:\n");
    Node* currentNode = seq->first;
    while (currentNode != NULL)
    {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
}

Node* getLast(Sequence* seq)
{
    if (seq->first == NULL)
        return NULL;

    Node* lastNode = seq->first;
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    
    return lastNode;
}

void removeLast(Sequence* seq)
{
    if (seq->first == NULL)
        return;
    
    if (seq->first->next == NULL)
    {
        free(seq->first);
        seq->first = NULL;
        return;
    }

    Node* beforeLast = getLast(seq)->prev;
    free(beforeLast->next);
    beforeLast->next = NULL;
}

void enqueue(Sequence* seq, int value)
{
    Node* lastNode = getLast(seq);
    if (lastNode == NULL)
    {
        seq->first = malloc(sizeof(Node));
        seq->first->value = value;
        seq->first->prev = NULL;
        seq->first->next = NULL;
        return;
    }

    lastNode->next = malloc(sizeof(Node));
    lastNode->next->value = value;
    lastNode->next->prev = lastNode;
    lastNode->next->next = NULL;
    return;
}

void dequeue(Sequence* seq)
{
    if (seq->first == NULL)
        return;
    
    if (seq->first->next == NULL){
        removeLast(seq);
        return;
    }

    Node* second = seq->first->next;
    free(seq->first);
    seq->first = second;
    seq->first->prev = NULL;
}

void destructSequence(Sequence* seq)
{
    //Node* lastNode = getLast(seq);
    //while (lastNode != NULL)
    //{
    //    removeLast(seq);
    //    lastNode = getLast(seq);
    //}

    while (seq->first != NULL)
        dequeue(seq);
}

void bubbleSort(Sequence* seq)
{
    if (seq->first == NULL)
        return;
    if (seq->first->next == NULL)
        return;
    
    Node* lastNode = getLast(seq);
    while (lastNode != seq->first)
    {
        for (Node* iterator = seq->first; iterator != getLast(seq); iterator = iterator->next)
            if (iterator->value > iterator->next->value)
            {
                int aux = iterator->value;
                iterator->value = iterator->next->value;
                iterator->next->value = aux;
            }
        
        lastNode = lastNode->prev;
    }
}

void cycle(Sequence* seq)
{
    if (seq->first == NULL)
        return;
    if (seq->first->next == NULL)
        return;

    int firstValue = seq->first->value;
    dequeue(seq);
    enqueue(seq, firstValue);
}

Sequence readSequence()
{
    Sequence seq;
    seq.first = NULL;

    int input = 0;
    while (true)
    {
        scanf("%d", &input);
        if (input == -1)
            break;
        else
            enqueue(&seq, input);
    }

    return seq;
}

int computeScore(Sequence* seq, Sequence* guess)
{
    if ((seq->first == NULL) || (guess->first == NULL))
        return 0;
    
    int score = 0;
    Node* iterator_1 = seq->first;
    Node* iterator_2 = guess->first;
    while ((iterator_1 != NULL) && (iterator_2 != NULL))
    {
        if (iterator_1->value == iterator_2->value)
            score++;

        iterator_1 = iterator_1->next;
        iterator_2 = iterator_2->next;
    }

    return score;
}


// ----------------------- Jogadas -----------------------
void keepSafe(Sequence* seq, Sequence* evenStack, Sequence* oddStack)
{
    if (seq->first == NULL)
        return;
    
    int firstValue = seq->first->value;
    dequeue(seq);
    if (firstValue % 2 == 0)
        enqueue(evenStack, firstValue);
    else
        enqueue(oddStack, firstValue);
}

void out(Sequence* seq)
{
    if (seq->first == NULL)
        return;
    if (seq->first->next == NULL)
        return;

    // Condição 1: peça corrente maior que o próximo número
    // Condição 2: próximo número pertence ao adversário
    bool condition_1 = seq->first->value > seq->first->next->value;
    bool condition_2 = seq->first->next->value % 2 != seq->first->value % 2;
    if (condition_1 && condition_2)
    {
        // Remove o segundo elemento
        if (seq->first->next->next == NULL){
            free(seq->first->next);
            seq->first->next = NULL;
        }
        else
        {
            Node* thirdElement = seq->first->next->next;
            free(seq->first->next);
            seq->first->next = thirdElement;
            thirdElement->prev = seq->first;
        }
    }
}

void comeBack(Sequence* seq, Sequence* evenStack, Sequence* oddStack)
{
    if (seq->first == NULL)
        return;

    int firstValue = seq->first->value;
    int comebackValue;
    if (firstValue % 2 == 0)
    {
        if (evenStack->first == NULL)
            return;
        
        comebackValue = getLast(evenStack)->value;
        removeLast(evenStack);
    }
    else
    {
        if (oddStack->first == NULL)
            return;
        
        comebackValue = getLast(oddStack)->value;
        removeLast(oddStack);
    }
    
    // Operação "cycle" já imbutida na jogada "comeBack"
    dequeue(seq);
    enqueue(seq, firstValue);
    enqueue(seq, comebackValue);
}

void trap(Sequence* trapQueue)
{
    int trapTime;
    scanf("%d", &trapTime); 
    enqueue(trapQueue, trapTime);
    bubbleSort(trapQueue);
}

// ------ Utilidades para o gerenciamento das armadilhas ------
bool trapIsAvailable(Sequence* trapQueue)
{
    if (trapQueue->first == NULL)
        return false;
    if (trapQueue->first->value == 0)
        return true;

    return false;
}

void updateTrapQueue(Sequence* trapQueue)
{
    if (trapQueue->first == NULL)
        return;
    
    int zeroCount = 0;
    // Diminuir 1 turno de espera de todas as armadilhas
    Node* iterator = trapQueue->first;
    while (iterator != NULL)
    {
        if (iterator->value == 0)
            zeroCount++;

        iterator->value -= 1;
        iterator = iterator->next;
    }

    // Eliminar todas as armadilhas já ativadas 
    for (int i=0; i < zeroCount; i++)
        dequeue(trapQueue);
}