/******* Disciplina: ESTRUTURAS DE DADOS *******/
/**************** Turma: GH ********************/
/********** Tarefa de Laboratório 00 ***********/
/* Problema: Ordenar vetor de numeros inteiros */
/* Entrada: numero inteiro N *******************/
/* Saida: Vetor ordenado nao-decrescente *******/

#include<stdio.h>

int main(){
	int n,i,j,aux=0,v[100];

	/* Leitura do numero de elementos */
	scanf("%d", &n);

	/*Leitura dos elementos	*/
	for(i = 0; i < n; i++){
	   scanf("%d", &v[i]);		
	}

	/*Ordena o vetor assegurando que na iteração
	i, o (i+1)-esimo maior elemento esta na
	posicao correta*/
	for(i = 0; i < n; i++){
		for(j = 0; j < n-1; j++){
			if(v[j] > v[j+1]){
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;	
			}		
		}
	}

	/* Imprime os elementos ordenados */
	for(i = 0;i < n; i++){
		printf("%d ",v[i]);	
	}

	/* Imprime uma quebra de linha */
	printf("\n");

	return 0;
}