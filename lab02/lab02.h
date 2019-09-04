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
