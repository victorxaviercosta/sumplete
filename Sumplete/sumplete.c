//Victor Xavier Costa - 23.1.4003

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "utilidades.h"
#include "sumpletelib.h"

int main(){
	
	//Criando e alocando a variável do tipo Jogo
	Jogo *jogoAtual = malloc(sizeof(Jogo));
	jogoAtual->tamTabuleiro = 0;
	
	//Imprimindo mensagem de boas vindas
	printf(GREEN("\n\n\t\tBem vindo ao Jogo") BOLD(YELLOW(" SUMPLETE!\n\n")));

	//Abre o menu inicial, lê a opção escolhida e chama a função correspondente
	menuInicial(jogoAtual);
	
	//Liberação da memória
	if(jogoAtual->tabuleiro.matriz != NULL)
		liberaMatriz(jogoAtual->tabuleiro.matriz, jogoAtual->tamTabuleiro);
	if(jogoAtual->tabuleiro.mantem != NULL)
		liberaMatriz(jogoAtual->tabuleiro.mantem, jogoAtual->tamTabuleiro * jogoAtual->tamTabuleiro);
	if(jogoAtual->tabuleiro.remove != NULL)
		liberaMatriz(jogoAtual->tabuleiro.remove, jogoAtual->tamTabuleiro * jogoAtual->tamTabuleiro);
	if(jogoAtual->resposta != NULL)
		liberaMatriz(jogoAtual->resposta, TAM_RESP);
	if(jogoAtual->tabuleiro.somaL != NULL)
		free(jogoAtual->tabuleiro.somaL);
	if(jogoAtual->tabuleiro.somaC != NULL)
		free(jogoAtual->tabuleiro.somaC);
	if(jogoAtual->tabuleiro.somaLaux != NULL)
		free(jogoAtual->tabuleiro.somaLaux);
	if(jogoAtual->tabuleiro.somaCaux != NULL)
		free(jogoAtual->tabuleiro.somaCaux);
	
	free(jogoAtual);
	
	return 0;
}