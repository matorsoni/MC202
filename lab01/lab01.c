/*
Aluno: Mateus Orsoni Cabral
RA: 147349
2s2019: MC202 turmas G e H

Os nomes de variáveis e de funções são em inglês apenas por uma questão de costume. Os comentários ao longo do código serão sempre em português.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Classroom
{
    int rows;
    int cols;
    bool* buffer;

}Classroom;

typedef enum Direction{East, NorthEast, North, NorthWest, West, SouthWest, South, SouthEast} Direction;

void constructor(Classroom* p_classroom, int p_rows, int p_cols);
bool isInsideClassroom(Classroom* p_classroom, int p_row, int p_col);
void setState(Classroom* p_classroom, int p_row, int p_col, bool state);
bool getState(Classroom* p_classroom, int p_row, int p_col);
bool isClassroomSafe(Classroom* p_classroom);
void castLine(Classroom* p_classroom, int p_monitorRow, int p_monitorCol, int p_monitorRange, Direction p_direction);
void printClassroom(Classroom* p_classroom);

int main()
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    Classroom classroom;
    constructor(&classroom, rows, cols);

    int monitors;
    scanf("%d", &monitors);

    for(int i=0; i<monitors; i++)
    {
        int monitorRow, monitorCol, monitorRange;
        // Ver como fazer isso com o formato "(x, y, z)"
        scanf("%d", &monitorRow);
        scanf("%d", &monitorCol);
        scanf("%d", &monitorRange);
    
        // Linhas e colunas entre 0 e N-1 
        monitorRow--;
        monitorCol--;

        for (Direction d = 0; d < 8; d++)
            castLine(&classroom, monitorRow, monitorCol, monitorRange, d);
    }

    if(isClassroomSafe(&classroom))
        printf("T\n");
    else
        printf("F\n");

printClassroom(&classroom);

    free(classroom.buffer);

    return 0;
}

void constructor(Classroom* p_classroom, int p_rows, int p_cols)
{
    p_classroom->rows = p_rows;
    p_classroom->cols = p_cols;
    // Todos os lugares inicializados como false
    p_classroom->buffer = calloc(p_rows*p_cols, sizeof(bool));
}

bool isInsideClassroom(Classroom* p_classroom, int p_row, int p_col)
{
    return ((p_row >= 0) && (p_row < p_classroom->rows) && (p_col >= 0) && (p_col < p_classroom->cols));
}

void setState(Classroom* p_classroom, int p_row, int p_col, bool state)
{
    if (isInsideClassroom(p_classroom, p_row, p_col))
        p_classroom->buffer[p_col + (p_classroom->cols)*p_row] = state;
    else
        printf("Erro: Aluno fora da classe\n");
}

bool getState(Classroom* p_classroom, int p_row, int p_col)
{
    if (isInsideClassroom(p_classroom, p_row, p_col))
        return p_classroom->buffer[p_col + (p_classroom->cols)*p_row];
    else
    {
        printf("Erro: Aluno fora da classe\n");
        return false;
    }
}

bool isClassroomSafe(Classroom* p_classroom)
{
    bool returnValue = true;
    for (int row=0; row<p_classroom->rows; row++)
        for (int col=0; col<p_classroom->cols; col++)
            if(getState(p_classroom, row, col) == false)
                returnValue = false;
    return returnValue;
}

void castLine(Classroom* p_classroom, int p_monitorRow, int p_monitorCol, int p_monitorRange, Direction p_direction)
{
    if(!isInsideClassroom(p_classroom, p_monitorRow, p_monitorCol))
    {
        printf("Erro: Monitor fora da classe...");
        return;
    }

    int deltaRow = 0;
    int deltaCol = 0;

    switch (p_direction)
    {    
    case East:
        deltaRow = 0;
        deltaCol = 1;
        break;
    
    case NorthEast:
        deltaRow = -1;
        deltaCol = 1;
        break;

    case North:
        deltaRow = -1;
        deltaCol = 0;
        break;
    
    case NorthWest:
        deltaRow = -1;
        deltaCol = -1;
        break;

    case West:
        deltaRow = 0;
        deltaCol = -1;
        break;

    case SouthWest:
        deltaRow = 1;
        deltaCol = -1;
        break;
    
    case South:
        deltaRow = 1;
        deltaCol = 0;
        break;
    
    case SouthEast:
        deltaRow = 1;
        deltaCol = 1;
        break;

    default: // North
        deltaRow = -1;
        deltaCol = 0;
        break;
    
    }

    // A posição do monitor é segura por definição
    setState(p_classroom, p_monitorRow, p_monitorCol, true);
    int currentRow = p_monitorRow;
    int currentCol = p_monitorCol;
    for (int i=0; i<p_monitorRange; i++)
    {
        currentRow += deltaRow;
        currentCol += deltaCol;

        if(isInsideClassroom(p_classroom, currentRow, currentCol))
            setState(p_classroom, currentRow, currentCol, true);
        else
            break;
    }
}

void printClassroom(Classroom* p_classroom)
{
    for (int row=0; row<p_classroom->rows; row++)
    {
        for (int col=0; col < p_classroom->cols; col++)
        {
            if (getState(p_classroom, row, col))
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}
