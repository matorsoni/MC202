/*
Aluno: Mateus Orsoni Cabral
RA: 147349
2s2019: MC202 turmas G e H

Os nomes de variáveis e de funções são escritos em inglês apenas por uma questão de costume. Os comentários ao longo do código serão sempre em português.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Struct representando a sala de aula, onde o array de booleans representa os lugares vigiados ("true") e nao vigiados ("false")
typedef struct Classroom
{
    int rows;
    int cols;
    bool* buffer;

}Classroom;

// enum usado para definir as direções que um monitor pode vigiar 
typedef enum Direction{East, NorthEast, North, NorthWest, West, SouthWest, South, SouthEast} Direction;

// Todas as funções usadas no código, com comentários nas respectivas implementações
int parseInput(char* p_input);
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
        // Para uma entrada no formato "(x, y, z)" temos:
        // input1 == "(x," ; input2 == "y," ; input3 == "z)"

        char input1[50], input2[50], input3[50];
        scanf("%s %s %s", input1, input2, input3);

        int monitorRow = parseInput(input1);
        int monitorCol = parseInput(input2);
        int monitorRange = parseInput(input3);
       
        // Linhas e colunas entre 0 e N-1, não entre 1 e N
        monitorRow--;
        monitorCol--;

        // Projeta a visão do monitor em todas as direções, com o alcance dado  
        for (Direction d = 0; d < 8; d++)
            castLine(&classroom, monitorRow, monitorCol, monitorRange, d);
    }

    if(isClassroomSafe(&classroom))
        printf("T\n");
    else
        printf("F\n");

    //printClassroom(&classroom);

    free(classroom.buffer);

    return 0;
}

// Retorna um inteiro dada uma string contendo digitos 
int parseInput(char* p_input)
{
	int returnValue = 0;
	int inputIndex = 0, outputIndex = 0;
	char outputString[50];

    // Copia para outputString apenas os digitos contidos em p_input, ignorando '(' , ',' e ')' 
	while(p_input[inputIndex] != '\0')
	{
		if((p_input[inputIndex] == '(') || (p_input[inputIndex] == ',') || (p_input[inputIndex] == ')'))
		{
			inputIndex++;
			continue;
		}   
		else
		{	
			outputString[outputIndex] = p_input[inputIndex];
			outputIndex++;
			inputIndex++;
		}
	}

	outputString[outputIndex] = '\0';
	
    // Converte char* em inteiro
	returnValue = atoi(outputString);
	return returnValue;
}

// Inicializa o struct Classroom
void constructor(Classroom* p_classroom, int p_rows, int p_cols)
{
    p_classroom->rows = p_rows;
    p_classroom->cols = p_cols;
    // Todos os lugares inicializados como false, por isso o uso de calloc ao invés de malloc
    p_classroom->buffer = calloc(p_rows*p_cols, sizeof(bool));
}

// Checa se uma dada posicao pertence as dimensoes da sala de aula
bool isInsideClassroom(Classroom* p_classroom, int p_row, int p_col)
{
    return ((p_row >= 0) && (p_row < p_classroom->rows) && (p_col >= 0) && (p_col < p_classroom->cols));
}

// Getters e setters do struct Classroom
void setState(Classroom* p_classroom, int p_row, int p_col, bool state)
{
    if (isInsideClassroom(p_classroom, p_row, p_col))
        p_classroom->buffer[p_col + (p_classroom->cols)*p_row] = state;
    else
        printf("Erro: Posicao fora da classe\n");
}

bool getState(Classroom* p_classroom, int p_row, int p_col)
{
    if (isInsideClassroom(p_classroom, p_row, p_col))
        return p_classroom->buffer[p_col + (p_classroom->cols)*p_row];
    else
    {
        printf("Erro: Posicao fora da classe\n");
        return false;
    }
}

// Verifica se todos os lugares da sala de aula estao sob vigia, i.e, se todos os valores sao "true"
bool isClassroomSafe(Classroom* p_classroom)
{
    bool returnValue = true;
    for (int row=0; row < p_classroom->rows; row++)
        for (int col=0; col < p_classroom->cols; col++)
            if(getState(p_classroom, row, col) == false)
                returnValue = false;
    return returnValue;
}

// Projeta a visao de um monitor na direcao dada como entrada, dando aos lugares vigiados o valor "true"
void castLine(Classroom* p_classroom, int p_monitorRow, int p_monitorCol, int p_monitorRange, Direction p_direction)
{
    if(!isInsideClassroom(p_classroom, p_monitorRow, p_monitorCol))
    {
        printf("Erro: Monitor fora da classe...");
        return;
    }

    // Define o vetor que aponta na direcao p_direction
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

        // Sai do loop no primeiro lugar fora da sala, pois todos os seguintes certamente estarão fora tambem
        if(isInsideClassroom(p_classroom, currentRow, currentCol))
            setState(p_classroom, currentRow, currentCol, true);
        else
            break;
    }
}

// Print da atual situacao da sala de aula, util para debug
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