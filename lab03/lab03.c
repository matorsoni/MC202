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

// Struct que representa uma rota, i.e, uma matrix de entradas inteiras 
typedef struct Bitmap
{
    int rows;
    int cols;
    int* buffer;
}Bitmap;

// Declaração de funções pertinentes ao struct Bitmap
void constructor(Bitmap* p_bitmap, int p_rows, int p_cols);
bool isInsideBitmap(Bitmap* p_bitmap, int p_row, int p_col);
void setState(Bitmap* p_bitmap, int p_row, int p_col, int p_state);
int getState(Bitmap* p_bitmap, int p_row, int p_col);
void printBitmap(Bitmap* p_bitmap);

// Declaração das funções que calculam o número de tropas de uma rota 
void recursiveCluster(Bitmap* p_bitmap, int p_row, int p_col);
int countTroops(Bitmap* p_bitmap);

int main()
{
    // Número de testes de entrada
    int T;
    scanf("%d", &T);

    for (int t=0; t<T; t++)
    {
        int M, N;
        scanf("%d %d", &M, &N);
        int width = N/3;

        // Inicialização com valores 0 dos três Bitmaps: rotas superior, intermediaria e inferior
        Bitmap topLane;
        constructor(&topLane, M, width);
        Bitmap midLane;
        constructor(&midLane, M, width);
        Bitmap botLane;
        constructor(&botLane, M, width);

        // Leitura das linhas de entrada do terminal.
        // Cada linha de entrada preenche uma linha de todas as 3 rotas. 
        for (int row = 0; row < M; row++)
            for (int col = 0; col < N; col++)
            {
                int bit;
                scanf("%d", &bit);

                if (col < width)
                    setState(&topLane, row, col, bit);
                else if (col < 2*width)
                    setState(&midLane, row, col-width, bit);
                else
                    setState(&botLane, row, col-2*width, bit);
            }

        // Cálculo do número de tropas de cada rota
        int topTroops = countTroops(&topLane);
        int midTroops = countTroops(&midLane);
        int botTroops = countTroops(&botLane);

        // Saída
        printf("Teste: %d\n", t+1);
        printf("Rota superior: %d\n", topTroops);
        printf("Rota intermediaria: %d\n", midTroops);
        printf("Rota inferior: %d\n", botTroops);

        // Limpar toda memória alocada dinamicamente
        free(topLane.buffer);
        free(midLane.buffer);
        free(botLane.buffer);
    }

    return 0;
}


// Inicializa o struct Bitmap
void constructor(Bitmap* p_bitmap, int p_rows, int p_cols)
{
    p_bitmap->rows = p_rows;
    p_bitmap->cols = p_cols;
    // Todas posições inicializadas como 0, por isso o uso de calloc ao invés de malloc
    p_bitmap->buffer = calloc(p_rows*p_cols, sizeof(int));
}

// Checa se uma dada posição pertence as dimensões do Bitmap
bool isInsideBitmap(Bitmap* p_bitmap, int p_row, int p_col)
{
    return ((p_row >= 0) && (p_row < p_bitmap->rows) && (p_col >= 0) && (p_col < p_bitmap->cols));
}

// Getters e setters do struct Bitmap
void setState(Bitmap* p_bitmap, int p_row, int p_col, int p_state)
{
    if (isInsideBitmap(p_bitmap, p_row, p_col))
        p_bitmap->buffer[p_col + (p_bitmap->cols)*p_row] = p_state;
    else
        printf("getState erro: Posicao (%d, %d) fora do Bitmap\n", p_row, p_col);
}

int getState(Bitmap* p_bitmap, int p_row, int p_col)
{
    if (isInsideBitmap(p_bitmap, p_row, p_col))
        return p_bitmap->buffer[p_col + (p_bitmap->cols)*p_row];
    else
    {
        printf("setState erro: Posicao (%d, %d) fora do Bitmap\n", p_row, p_col);
        return -1;
    }
}

// Imprime a situação atual de um Bitmap, útil para debug
void printBitmap(Bitmap* p_bitmap)
{
    for (int row=0; row<p_bitmap->rows; row++)
    {
        for (int col=0; col < p_bitmap->cols; col++)
            printf("%d ",(getState(p_bitmap, row, col)));

        printf("\n");
    }
}

// Função recursiva que escreve -1 em todas as posições de uma tropa, ou seja, 
// quando o valor inicial armazenado na posição dada é 1.
void recursiveCluster(Bitmap* p_bitmap, int p_row, int p_col)
{
    // Checa se a posição está dentro do Bitmap
    if (!isInsideBitmap(p_bitmap, p_row, p_col))
        return;

    if(getState(p_bitmap, p_row, p_col) == 1)
    {
        setState(p_bitmap, p_row, p_col, -1);

        // Checar posição ao leste
        recursiveCluster(p_bitmap, p_row, p_col+1);
        // Checar posição ao norte
        recursiveCluster(p_bitmap, p_row-1, p_col);
        // Checar posição ao oeste
        recursiveCluster(p_bitmap, p_row, p_col-1);
        // Checar posição ao sul
        recursiveCluster(p_bitmap, p_row+1, p_col);
    }
}

// Função que retorna o número de tropas de uma rota dada.
int countTroops(Bitmap* p_bitmap)
{
    int troops = 0;
    // Percorre as linhas do bitmap até encontrar o valor 1, posição (row,col).
    for (int row = 0; row < p_bitmap->rows; row++)
        for (int col = 0; col < p_bitmap->cols; col++)
        {
            if(getState(p_bitmap, row, col) == 1)
            {
                // Lança a função recursiva em (row,col) para escrever -1 em todas as posições que pertencem à esta tropa.
                // Deste modo, as posições com valores -1 serão ignoradas na busca das próximas tropas.
                recursiveCluster(p_bitmap, row, col);
                troops++;
            }
        }

    return troops;
}