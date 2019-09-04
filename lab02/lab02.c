/*
Aluno: Mateus Orsoni Cabral
RA: 147349
2s2019: MC202 turmas G e H

Os nomes de variáveis e de funções são eventualmente escritos em inglês apenas por uma questão de costume. 
Os comentários ao longo do código serão sempre em português.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============== Cópia do arquivo lab02.h ==============

/* Laboratório 09: Pintando em 7 *
 * Arquivo de Cabeçalho: lab02.h *
 * Descrição:   Este arquivo contém o pragma/cabeçalho das funções a serem implementadas neste laboratório. Cada  *
 *              função contém uma breve descrição sobre o seu objetivo, a saída esperada e uma pequena explicação *
 *              dos parâmetros de entrada.                                                                        *
 */

/* -=-=-=-=-=-=-=-=-=-=-=-=-=- Cabeçalhos de Funções (à serem desenvolvidas) -=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define NOME_MAX 30

typedef struct _ponto {
double x;
double y;
char nome[NOME_MAX];
} ponto;

typedef struct _pintor {
char nome[NOME_MAX];
double area;
} pintor;

/* Inicia Pintores                                                                                         *
 * Objetivo:    Le os nomes dos pintores e os armazena em um vetor de structs                              *
 * Saída:       Não retorna nenhum valor como saida                                                        *
 * Parâmetros:                                                                                             *
 *      - pintor *pintores: Ponteiro para o vetor de pintores a ser preenchido                             *
 */
void inicia_pintores(pintor *pintores);

/* Le borda                                                                         *
 * Objetivo:    Ler a grade de pontos que compoe a borda da parede                  *
 * Saída:       Não retorna nenhum valor como saida                                 *
 * Parâmetros:                                                                      *
 *      - ponto borda: Ponteiro para o vetor de pontos da borda                     *
 */
void le_borda(ponto *borda, int n);

/* Computa Area                                                                             *
 * Objetivo:    Computar o valor da area a ser pintada por cada pintor                      *
 * Saída:       Não retorna nenhum valor como saida                                         *
 * Parâmetros:                                                                              *
 *      - ponto *superior: Vetor de pontos que representa a borda superior da parede        *
 *      - ponto *pintada: Vetor de pontos que representa a borda superior da area pintada   *
 *      - int n: Inteiro que representa o numero de pontos da discretizaçao das bordas      *
 *      - pintor *pintores: Vetor de structs dos pintores como nome e area                  * 
 */
void computa_area(ponto *superior, ponto *pintada, int n, pintor *pintores);

/* Imprime Areas                                                                                        *
 * Objetivo:    Imprimir a area a ser pintada por cada pintor                                           *
 * Saída:       Não retorna nenhum valor como saida                                                     *
 * Parâmetros:                                                                                          *
 *      - pintor *pintores:  Vetor de structs dos pintores como nome e area                             *
 */
void imprime_areas(pintor *pintores);

// ========================================================


#define MAX_PONTOS 200

// Declaração de funções auxiliares
bool compareStrings(char* p_string1, char* p_string2);
double computeAreaFromIndices(ponto* p_points, int p_first, int p_last);
int findIndices(ponto* p_points, int p_n, char* p_name, int* p_firstIndices, int* p_lastIndices);

int main()
{
    pintor pintores[7];

    inicia_pintores(pintores);

    // Número de pontos
    int nPontos = 0;
    scanf("%d", &nPontos);

    // Alocação e leitura dos vetores de pontos que representam as paredes
    ponto bordaParede[nPontos];
    ponto bordaPintada[nPontos];
    le_borda(bordaParede, nPontos);
    le_borda(bordaPintada, nPontos);

    computa_area(bordaParede, bordaPintada, nPontos, pintores);

    imprime_areas(pintores);

    return 0;
}

void inicia_pintores(pintor *pintores)
{
    for (int p=0; p<7; p++)
    {
        // Para cada um dos 7 pintores, lê o nome e inicializa a área com valor 0.0
        scanf("%s", pintores[p].nome);
        pintores[p].area = 0.0;
    }
}

void le_borda(ponto *borda, int n)
{
    // Inicializa um vetor de pontos à partir das entradas fornecidas
    for (int p=0; p<n; p++)
        scanf("%lf %lf %s", &(borda[p].x), &(borda[p].y), borda[p].nome);
}


void computa_area(ponto *superior, ponto *pintada, int n, pintor *pintores)
{
    for (int p=0; p < 7; p++)
    {       
        // Aloca os vetores que estocam os índices de ínicio e fim do trecho à ser pintado por cada pintor
        int firstIndices[MAX_PONTOS];
        int lastIndices[MAX_PONTOS];
        // Escreve nos vetores de índices e retorna quantos trechos pertecem ao pintor 
        int count = findIndices(superior, n, pintores[p].nome, firstIndices, lastIndices);
        for (int c=0; c < count; c++)
        {
            // Adiciona a área total e subtrai a área já pintada
            pintores[p].area += computeAreaFromIndices(superior, firstIndices[c], lastIndices[c]);
            pintores[p].area -= computeAreaFromIndices(pintada, firstIndices[c], lastIndices[c]);
        }
    }
}


void imprime_areas(pintor *pintores)
{
    // Printa com 2 casas decimais os valores de área de cada pintor
    for (int p=0; p < 7; p++)
    {
        printf("%s: %.2lf UA\n", pintores[p].nome, pintores[p].area);
    }
}

/* Funções auxiliares */ 

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

double computeAreaFromIndices(ponto* p_points, int p_first, int p_last)
{
    // Calcula a área de um trapézio definido pelos inteiros de entrada, que representam índices do vetor de pontos.
    int index;
    double returnArea = 0.0;

    for (index = p_first; index < p_last; index++)
    {
        // Notação : x = "x_{i}" ; x_ = "x_{i+1}"
        double x = p_points[index].x;
        double x_ = p_points[index+1].x;
        double y = p_points[index].y;
        double y_ = p_points[index+1].y;

        // Área segundo a regra dos trapezios
        returnArea += 0.5*(y_ + y)*(x_ - x);
    }

    return returnArea;
}

int findIndices(ponto* p_points, int p_n, char* p_name, int* p_firstIndices, int* p_lastIndices)
{
    // Percorre o vetor p_points e encontra quais trechos o pintor p_name deve pintar.
    // Um trecho é definido pelo par de índices de p_points que correspondem ao seu início e seu fim.
    // Como o mesmo pintor pode pintar mais de um trecho, a função escreve os índices de início no buffer p_firstIndices,
    // e os índices de fim em p_lastIndices.
    // A função retorna a variável "count", que é o número de trechos diferentes que o pintor em questão precisa pintar

    // A variável "consecutive" é "true" se na última iteração o nome do pintor correto foi encontrado no vetor p_points,
    // e "false" caso contrário. Um trecho começa quando o nome do pintor é encontrado e "consecutive" é "false", e termina quando
    // um nome diferente é encontrado enquanto "consecutive" tem valor "true".

    int count = 0; 
    bool consecutive = false;
    for (int p=0; p < p_n; p++)
    {
        if ((compareStrings(p_name, p_points[p].nome) == true) && (consecutive == false))
        {         
            // Começo de um trecho
            p_firstIndices[count] = p;
            consecutive = true;
        }   
        if ((compareStrings(p_name, p_points[p].nome) == false) && (consecutive == true))
        {         
            // Fim de um trecho
            p_lastIndices[count] = p;
            count++;
            consecutive = false;
        }
        // Caso o nome do pintor seja encontrado no fim do vetor de pontos, o critério de parada é a chagada ao fim do vetor
        if ((compareStrings(p_name, p_points[p].nome) == true) && (consecutive == true))
        {         
            if (p == (p_n - 1))
            {
                p_lastIndices[count] = p;
                count++;
            }
        }
    }

    return count;
}