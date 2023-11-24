//Victor Xavier Costa - 23.1.4003

#ifndef UTILIDADES_H
#define UTILIDADES_H

//Função que aloca uma matriz dinâmicamente - Retorna NULL em caso de falha.
int** criaMatriz(int **matriz, int n, int m);

//Função que libera o espaço alocado para uma matriz
void liberaMatriz(int **matriz, int n);

//Função que inicializa um vetor com zero
void inicializaVetor(int *vetor, int n);

//Função que compara o conteúdo de dois vetores de mesmo tamanho
int comparaVetores(int *vetor1, int *vetor2, int n);

//Função que inicaliza uma matriz com um valor definido
void inicializaMatriz(int **matriz, int n, int m, int valor);

//Função para remover o /n de uma string
void removeEnter(char *string, int n);

//Função para a limpeza do buffer para leitura de strings e caracteres
void limpaBuffer();

#endif