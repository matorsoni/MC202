#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Bitmap
{
    int rows;
    int cols;
    int* buffer;
}Bitmap;

void constructor(Bitmap* p_bitmap, int p_rows, int p_cols);
bool isInsideBitmap(Bitmap* p_bitmap, int p_row, int p_col);
void setState(Bitmap* p_bitmap, int p_row, int p_col, int p_state);
int getState(Bitmap* p_bitmap, int p_row, int p_col);
void printBitmap(Bitmap* p_bitmap);

int main()
{
    int T;
    scanf("%d", &T);

    for (int t=0; t<T; t++)
    {
        int M, N;
        scanf("%d %d", &M, &N);
        int width = N/3;

        Bitmap topLane;
        constructor(&topLane, M, width);
        Bitmap midLane;
        constructor(&midLane, M, width);
        Bitmap botLane;
        constructor(&botLane, M, width);

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

        printBitmap(&topLane);
        printBitmap(&midLane);
        printBitmap(&botLane);

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

// Checa se uma dada posição pertence as dimensoes do Bitmap
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
        printf("Erro: Posicao fora do Bitmap\n");
}

int getState(Bitmap* p_bitmap, int p_row, int p_col)
{
    if (isInsideBitmap(p_bitmap, p_row, p_col))
        return p_bitmap->buffer[p_col + (p_bitmap->cols)*p_row];
    else
    {
        printf("Erro: Posicao fora do Bitmap\n");
        return -1;
    }
}

int countTroops(Bitmap* p_lane)
{
    /*
    Ideia inicial:
    Percorrer as linhas do bitmap até encontrar 1, posição (m,n).
    Lançar a função recursiva em (m,n) para encontrar todas as posições que pertencem à tropa.
    Retirar essas posições da tropa do seguinte vetor de LinkedList: vetor[i] = lista de índices da linha i que são 0.
    O bitmap é percorrido à partir dos índices contidos em "vetor", pra que a busca ignore tropas já encontradas.

    */
    return 0;
}

void printBitmap(Bitmap* p_bitmap)
{
    for (int row=0; row<p_bitmap->rows; row++)
    {
        for (int col=0; col < p_bitmap->cols; col++)
            printf("%d ",(getState(p_bitmap, row, col)));

        printf("\n");
    }
}