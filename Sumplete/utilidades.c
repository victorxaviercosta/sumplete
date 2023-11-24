//Victor Xavier Costa - 23.1.4003

#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função que aloca uma matriz dinâmicamente - Retorna NULL em caso de falha.
int** criaMatriz(int **matriz, int n, int m){

	matriz = NULL;
	matriz = malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++){
		matriz[i] = malloc(m * sizeof(int));
	}
	if(matriz)
		return matriz;
	else
		return NULL;
}

//Função que libera o espaço alocado para uma matriz
void liberaMatriz(int **matriz, int n){

	for(int i = 0; i < n; i++){
		free(matriz[i]);
	}
	free(matriz);
}

//Função que inicializa um vetor com zero
void inicializaVetor(int *vetor, int n){
	for(int i = 0; i < n; i++){
		vetor[i] = 0;
	}
}

//Função que copmpara o conteúdo de dois vetores de mesmo tamanho
int comparaVetores(int *vetor1, int *vetor2, int n){
	int cont = 0;
	for(int i = 0; i < n; i++){
		if(vetor1[i] == vetor2[i])
			cont++;
	}
	if(cont == n)
		return 1;
	else
		return 0;
}

//Função que inicaliza uma matriz com um valor definido
void inicializaMatriz(int **matriz, int n, int m, int valor){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			matriz[i][j] = valor;
		}
	}
}

//Função para remover o '/n' de uma string
void removeEnter(char *string, int n){
	for(int i = 0; i < n; i++){
		if(string[i] == '\n')
			string[i] = '\0';
	}

}

//Função para a limpeza do buffer para leitura de strings e caracteres
void limpaBuffer(){
	char limp;
	do{
		scanf("%c", &limp);
	} while(limp != '\n');
}