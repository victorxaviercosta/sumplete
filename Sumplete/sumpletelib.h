//Victor Xavier Costa - 23.1.4003

#include <stdio.h>
#include "utilidades.h"

#ifndef SUMPLETELIB_H
#define SUMPLETELIB_H

#define TAM_NOME 30
#define TAM_COMANDO 8
#define TAM_RESP 81
#define TAM_INI 60
#define TAM_ARQUIVO 720
#define QPLAYERS 5

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define H_TAB_HOR "\u2501" // ━ (horizontal)
#define H_TAB_VER "\u2503" // ┃ (vertical)
#define H_TAB_TL  "\u250F" // ┏ (top-left)
#define H_TAB_ML  "\u2523" // ┣ (middle-left)
#define H_TAB_BL  "\u2517" // ┗ (bottom-left)
#define H_TAB_TJ  "\u2533" // ┳ (top-join)
#define H_TAB_MJ  "\u254B" // ╋ (middle-join)
#define H_TAB_BJ  "\u253B" // ┻ (bottom-join)
#define H_TAB_TR  "\u2513" // ┓ (top-right)
#define H_TAB_MR  "\u252B" // ┫ (middle-right)
#define H_TAB_BR  "\u251B" // ┛ (bottom-right)

#define TAB_HOR "\u2500" // ─ (horizontal)
#define TAB_VER "\u2502" // │ (vertical)
#define TAB_TL  "\u250C" // ┌ (top-left)
#define TAB_ML  "\u251C" // ├ (middle-left)
#define TAB_BL  "\u2514" // └ (bottom-left)
#define TAB_TJ  "\u252C" // ┬ (top-join)
#define TAB_MJ  "\u253C" // ┼ (middle-join)
#define TAB_BJ  "\u2534" // ┴ (bottom-join)
#define TAB_TR  "\u2510" // ┐ (top-right)
#define TAB_MR  "\u2524" // ┤ (middle-right)
#define TAB_BR  "\u2518" // ┘ (bottom-right)

//Struct de tempo
typedef struct{
	long totalSegundos;
	int hora;
	int min;
	int seg;
} Tempo;

//Struct dos elementos do Tabuleiro
typedef struct{
	int **matriz;
	int *somaL;
	int *somaC;
	int contm;
	int contr;
	int **mantem;
	int **remove;
	int *somaLaux;
	int *somaCaux;
} Tabuleiro;

//Struct das configurações do Jogo
typedef struct{
	char nome[TAM_NOME];
	int tamTabuleiro;
	char dificuldade;
	Tempo tempo;
	Tabuleiro tabuleiro;
	int tamResp;
	int **resposta; //Matriz resposta que armazena as posições a serem mantidas no jogo.
} Jogo;

//Struct de um Comando
typedef struct{
	char acao[TAM_COMANDO];
	int linha;
	int coluna;
} Comando;

typedef struct{
	int qsize;
	int size[7];
	int qplayers[7];
	char player[7][5][TAM_NOME];
	long time[7][5];
} Ini;

//Função que encontra em qual linha estão as coordenadas
int encontraLinhaMatriz(int **matriz, int n, int el1, int el2);

//Função que remove uma linha de uma matriz
void removeLinhaMatriz(int **matriz, int n, int m, int i);

//Função que separa os númeeos digitados pelo usuário em linha e coluna
void separaCoordenadas(int n, int *linha, int *coluna);

//Função que percorre as matrizes "mantem", "remove" e "resposta" para saber se as coordenada i e j estão salvas
int lecoordenadas(int **matriz, int n, int i, int j);

//Função que converte o tempo de segundos para hrs, mins e segs.
void calculaTempo(Tempo *tempo);

//Função que grava os dados do arquivo do jogo (.txt)
int gravaJogo(char *nomeArquivo, Jogo *sjogo);

//Função que lê um aqruivo de texto contendo um jogo (.txt)
int leJogo(char *nomeArquivo, Jogo *jogo);

//Função que compara tempos dos jogadores salvos com o tempo do jogo atual
//e adicona jogadores novos, caso haja espaço, no arquivo.
void comparaIni(Ini *dadosIni, Jogo *jogo, int tam);

//Função que lê o arquivo .ini
Ini leIni(FILE *config, Jogo *sjogo);

//Função que grava os dados do arquivo de configuração (.ini)
void gravaIni(Jogo *sjogo);

//Função que converte um inteiro em um binário
//Auxiliar para a função resolve a fim de testar as combinações de números possíveis
void binario(int n, int **bin, int i);

//função recursiva para a realização dos testes que resolvem o jogo
void testes(Jogo *jogo, int ***matBin, int i, int *conf);

//Função que resolve o jogo encontrando todas as posições a serem adicionadas ao vetor de resposta.
void resolve(Jogo *jogo);

//Função que termina o jogo encontrando todas as posições a serem removidas
void terminaJogo(Jogo *jogo, int *tamMR);

//Função apenas para a impressão do tabuleiro
void imprimeTabuleiro(Tabuleiro tabuleiro, int n);

//Função que efetivamente executa o jogo
void executaJogo(Jogo *jogo);

//Função que cira um novo jogo.
void novoJogo(Jogo *novoJogo);

//Exibe o Ranking de jogadores
void exibirRanking();

//Função que impime o menu inicial do jogo, e faz a leitura da opção.
int menuInicial(Jogo *jogo);

#endif
