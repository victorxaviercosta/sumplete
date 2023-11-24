//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "utilidades.h"

//Função que encontra em qual linha estão as coordenadas
int encontraLinhaMatriz(int **matriz, int n, int el1, int el2){
	for(int i = 0; i < n; i++){
		if(matriz[i][0] == el1 && matriz[i][1] == el2)
			return i;
	}
	return 0;
}

//Função que remove uma linha de uma matriz (mantem, remove, ou resposta)
void removeLinhaMatriz(int **matriz, int n, int m, int i){
	int a, b;
	for(a = 0; a < (n - 1); a++){
		for(b = 0; b < m; b++){
			if(a == i){
				matriz[a][b] = matriz[a+1][b];
			}
		}
		if(a == i)
			i++;
	}
	matriz[a][0] = -1;
	matriz[a][1] = -1;
}

//Função que separa os númeeos digitados pelo usuário em linha e coluna
void separaCoordenadas(int n, int *linha, int *coluna){
	*linha = n / 10;
	*coluna = n % 10;
}

//Função para percorrer as matrizes "mantem", "remove" e "resposta" para saber se as coordenada i e j estão salvas
int lecoordenadas(int **matriz, int n, int i, int j){
	for(int a = 0; a < n; a++){
		if(matriz[a][0] == i && matriz[a][1] == j)
			return 1;
	}
	return 0;
}

//Função que converte o tempo de segundos para hrs, mins e segs.
void calculaTempo(Tempo *tempo){
	tempo->hora = tempo->totalSegundos / 3600;
	tempo->min = (tempo->totalSegundos % 3600) / 60;
	tempo->seg = (tempo->totalSegundos % 3600) % 60;
}

//Função que grava os dados do arquivo do jogo (.txt)
int gravaJogo(char *nomeArquivo, Jogo *sjogo){
	int coord;

	FILE *arquivo = NULL;
	arquivo = fopen(nomeArquivo, "w");
	if(!arquivo)
		return 0;

	//Imprimindo o tamnho do tabuleiro
	fprintf(arquivo, "%d\n", sjogo->tamTabuleiro);

	//Imprimindo a matriz do tabuleiro
	for(int i = 0; i < sjogo->tamTabuleiro; i++){
		for(int j = 0; j < sjogo->tamTabuleiro; j++){
			fprintf(arquivo, "%d ", sjogo->tabuleiro.matriz[i][j]);
		}
		fprintf(arquivo, "\n");
	}

	//Imprimindo soma das linhas
	for(int i = 0; i < sjogo->tamTabuleiro; i++){
		fprintf(arquivo, "%d ", sjogo->tabuleiro.somaL[i]);
	}
	fprintf(arquivo, "\n");
	
	//Imprimindo soma das colunas
	for(int i = 0; i < sjogo->tamTabuleiro; i++){
		fprintf(arquivo, "%d ", sjogo->tabuleiro.somaC[i]);
	}
	fprintf(arquivo, "\n");

	//imprindo o número de marcações para manter
	fprintf(arquivo, "%d\n", sjogo->tabuleiro.contm);

	//imprimindo coordenadas das manutenções
	for(int i = 0; i < sjogo->tabuleiro.contm; i++){
		for(int j = 0; j < 2; j++){
			coord = sjogo->tabuleiro.mantem[i][j] + 1;
			fprintf(arquivo, "%d ", coord);
		}
		fprintf(arquivo, "\n");
	}

	//imprimindo o número de marcações para remover
	fprintf(arquivo, "%d\n", sjogo->tabuleiro.contr);

	//imprimindo coordenadas das remoções
	for(int i = 0; i < sjogo->tabuleiro.contr; i++){
		for(int j = 0; j < 2; j++){
			coord = sjogo->tabuleiro.remove[i][j] + 1;
			fprintf(arquivo, "%d ", coord);
		}
		fprintf(arquivo, "\n");
	}

	//imprimindo o nome do jogador
	fprintf(arquivo, "%s\n", sjogo->nome);

	//imprindo o tempo de jogo
	fprintf(arquivo, "%ld", sjogo->tempo.totalSegundos);

	fclose(arquivo);
	return 1;
}

//Função que lê um aqruivo de texto contendo um jogo (.txt)
int leJogo(char *nomeArquivo, Jogo *jogo){
	int coord;

	FILE *arquivo = NULL;
	arquivo = fopen(nomeArquivo, "r");
	if(!arquivo)
		return 0;

	//lendo o tamnho do tabuleiro
	fscanf(arquivo, "%d", &jogo->tamTabuleiro);

	//Alocando os vetores de somas de linhas e colunas
	jogo->tabuleiro.somaL = malloc(jogo->tamTabuleiro * sizeof(int));
	jogo->tabuleiro.somaC = malloc(jogo->tamTabuleiro * sizeof(int));
	inicializaVetor(jogo->tabuleiro.somaL, jogo->tamTabuleiro);
	inicializaVetor(jogo->tabuleiro.somaC, jogo->tamTabuleiro);

	//Alocando e inicializando os vetores de soma atual
	jogo->tabuleiro.somaLaux = malloc(jogo->tamTabuleiro * sizeof(int));
	jogo->tabuleiro.somaCaux = malloc(jogo->tamTabuleiro * sizeof(int));
	inicializaVetor(jogo->tabuleiro.somaLaux, jogo->tamTabuleiro);
	inicializaVetor(jogo->tabuleiro.somaCaux, jogo->tamTabuleiro);
	
	//Alocando a matriz do tabuleiro
	jogo->tabuleiro.matriz = criaMatriz(jogo->tabuleiro.matriz, jogo->tamTabuleiro, jogo->tamTabuleiro);

	//Alocando e inicializando as matrizes mantem e remove com -1
	int tamMR = jogo->tamTabuleiro * jogo->tamTabuleiro;
	jogo->tabuleiro.mantem = criaMatriz(jogo->tabuleiro.mantem, tamMR, 2);
	jogo->tabuleiro.remove = criaMatriz(jogo->tabuleiro.mantem, tamMR, 2);
	inicializaMatriz(jogo->tabuleiro.mantem, tamMR, 2, -1);
	inicializaMatriz(jogo->tabuleiro.remove, tamMR, 2, -1);

	//Inicializando os vetores auxiliares de soma de linha e coluna
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			jogo->tabuleiro.somaLaux[i] += jogo->tabuleiro.matriz[i][j];
			jogo->tabuleiro.somaCaux[j] += jogo->tabuleiro.matriz[i][j];
		}
	}


	//lendo a matriz do tabuleiro
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			fscanf(arquivo, "%d ", &jogo->tabuleiro.matriz[i][j]);
		}

	}

	//lendo soma das linhas
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		fscanf(arquivo, "%d ", &jogo->tabuleiro.somaL[i]);
	}
	
	//lendo soma das colunas
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		fscanf(arquivo, "%d ", &jogo->tabuleiro.somaC[i]);
	}

	//lendo o número de marcações para manter
	fscanf(arquivo, "%d", &jogo->tabuleiro.contm);

	//lendo coordenadas das manutenções
	for(int i = 0; i < jogo->tabuleiro.contm; i++){
		for(int j = 0; j < 2; j++){
			fscanf(arquivo, "%d ", &coord);
			jogo->tabuleiro.mantem[i][j] = coord - 1;
		}

	}

	//lendo o número de marcações para remover
	fscanf(arquivo, "%d", &jogo->tabuleiro.contr);

	//lendo coordenadas das remoções
	for(int i = 0; i < jogo->tabuleiro.contr; i++){
		for(int j = 0; j < 2; j++){
			fscanf(arquivo, "%d ", &coord);
			jogo->tabuleiro.remove[i][j] = coord - 1;
		}

	}

	//lendo o nome do jogador
	fgets(jogo->nome, TAM_NOME, arquivo);
	removeEnter(jogo->nome, TAM_NOME);

	//lendo o tempo de jogo
	fscanf(arquivo, "%ld", &jogo->tempo.totalSegundos);

	fclose(arquivo);
	return 1;
}

//Função que compara tempos dos jogadores salvos com o tempo do jogo atual
//e adicona jogadores novos, caso haja espaço, no arquivo.
void comparaIni(Ini *dadosIni, Jogo *jogo, int tam){
	int pos = 0, timeaux, iaux, entra = 0;
	char aux[TAM_NOME];

	//Encontrando a posiação em que está salvo o tamanho atual do tabuleiro
	for(int i = 0; i < dadosIni->qsize; i++){
		if(dadosIni->size[i] == jogo->tamTabuleiro){
			pos = i;
			break;
		}
	}

	//Comparando o tempo do jogo atual com os tempos salvos
	for(int i = 0; i < dadosIni->qplayers[pos]; i++){
		if(jogo->tempo.totalSegundos < dadosIni->time[pos][i]){
			timeaux = dadosIni->time[pos][i];
			dadosIni->time[pos][i] = jogo->tempo.totalSegundos;

			strcpy(aux, dadosIni->player[pos][i]);
			strcpy(dadosIni->player[pos][i], jogo->nome);

			iaux = i;
			entra = 1;
			break;
		}
	}

	//deslocando os elementos
	if(entra){
		for(int i = QPLAYERS-1; i > iaux; i--){
			if(i != iaux+1){
				dadosIni->time[pos][i] = dadosIni->time[pos][i-1];
				strcpy(dadosIni->player[pos][i], dadosIni->player[pos][i-1]);
			}else{
				dadosIni->time[pos][i] = timeaux;
				strcpy(dadosIni->player[pos][i], aux);
			}
		}
		if(dadosIni->qplayers[pos] < QPLAYERS)
			dadosIni->qplayers[pos] +=  1;

	//se houver espaço sobrando
	} else if(dadosIni->qplayers[pos] < QPLAYERS && strcmp(dadosIni->player[pos][dadosIni->qplayers[pos] - 1], jogo->nome)){
		strcpy(dadosIni->player[pos][dadosIni->qplayers[pos]], jogo->nome);
		dadosIni->time[pos][dadosIni->qplayers[pos]] = jogo->tempo.totalSegundos;
		dadosIni->qplayers[pos] +=  1;
	}

}

//Função que lê o arquivo .ini
Ini leIni(FILE *config, Jogo *sjogo){
	//Criando o arquivo sumplete.ini caso não exista
	config = fopen("sumplete.ini", "a");
	fclose(config);

	//Abrindo o arquivo para leitura
	config = fopen("sumplete.ini", "r");

	char string[TAM_INI], aux[3];
	Ini dadosIni;
	
	//Inicializando o vetor de tempos com 0
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < QPLAYERS; j++){
			dadosIni.time[i][j] = 0;
		}
	}

	//Obtendo o tamanho atual do arquivo
	fseek(config, 0, SEEK_END);
	int tam = ftell(config);

	//Posicinando o indicador no inicio do arquivo.
	fseek(config, 0, SEEK_SET);

    //Inicializando as variáveis
	dadosIni.qsize = 0; 
	inicializaVetor(dadosIni.size, 7);
	inicializaVetor(dadosIni.qplayers, 7);

	//Lendo o arquivo
	if(tam > 0){
		while(!feof(config)){
			//lendo a primeira string da linha
			fscanf(config, "%s", string);
			//Lendo "="
			fscanf(config, "%s", aux);

			if(!strcmp(string, "size")){
				//lendo o tamanho do tabuleiro
				fscanf(config, "%d", &dadosIni.size[dadosIni.qsize]);
				dadosIni.qsize++;

				fscanf(config, "%s", string);

				//Lendo "="
				fscanf(config, "%s", aux);
			}

			//lendo o nome
			fgetc(config);
			fgets(dadosIni.player[dadosIni.qsize-1][dadosIni.qplayers[dadosIni.qsize-1]], TAM_NOME, config);
			removeEnter(dadosIni.player[dadosIni.qsize-1][dadosIni.qplayers[dadosIni.qsize-1]], TAM_NOME);

			//lendo "timeN" e "="
			fscanf(config, "%s", string);
			fscanf(config, "%s", aux);

			//lendo o tempo
			fscanf(config, "%ld ", &dadosIni.time[dadosIni.qsize-1][dadosIni.qplayers[dadosIni.qsize-1]]);
			dadosIni.qplayers[dadosIni.qsize-1]++;
		}

		//Verificando se o tamanho do tabuleiro do jogo atual já está gravado no arquivo quando ele é diferente de 0
		if(sjogo->tamTabuleiro){
			int ok = 0, pos = dadosIni.qsize;
			for(int i = 0; i < 7; i++){
				if(dadosIni.size[i] == sjogo->tamTabuleiro){
					ok = 1;
				}
			}
			//Se não estiver gravado:
			if(!ok){
				
				//Verificando em qual posição deve entrar o tamanho do tabuleiro atual
				for(int i = 0; i < dadosIni.qsize; i++){
					if(dadosIni.size[i] > sjogo->tamTabuleiro){
						pos = i;
						break;
					}
				}

				//Se não for a última posição
				if(pos != dadosIni.qsize){

					//deslocando os elementos
					for(int i = dadosIni.qsize; i > pos; i--){
						dadosIni.size[i] = dadosIni.size[i - 1];

						for(int j = 0; j < QPLAYERS; j++){
							strcpy(dadosIni.player[i][j], dadosIni.player[i - 1][j]);
							dadosIni.time[i][j] = dadosIni.time[i - 1][j];
						}
						dadosIni.qplayers[i] = dadosIni.qplayers[i - 1];
					}
					dadosIni.size[pos] = sjogo->tamTabuleiro;
					strcpy(dadosIni.player[pos][0], sjogo->nome);
					dadosIni.time[pos][0] = sjogo->tempo.totalSegundos;

				//Se for a última posição
				} else{
					dadosIni.size[dadosIni.qsize] = sjogo->tamTabuleiro;
					strcpy(dadosIni.player[dadosIni.qsize][0], sjogo->nome);
					dadosIni.time[dadosIni.qsize][0] = sjogo->tempo.totalSegundos;
				}

				dadosIni.qplayers[pos] = 1;
				dadosIni.qsize += 1;
			}
		}
	}

	fclose(config);

	return dadosIni;
}

//Função que grava os dados do arquivo de configuração (.ini)
void gravaIni(Jogo *sjogo){
	//Criando o arquivo sumplete.ini caso não exista
	FILE *config = fopen("sumplete.ini", "a");

	Ini dadosIni;

	//Obtendo o tamanho atual do arquivo
	fseek(config, 0, SEEK_END);
	int tam = ftell(config);

	fclose(config);

	//Lendo o arquivo atual
	dadosIni = leIni(config, sjogo);

	//Abrindo o arquivo para a escrita
	config = fopen("sumplete.ini", "w");

	//Se o arquivo estiver em branco
	if(tam == 0){
		fprintf(config, "size = %d\n", sjogo->tamTabuleiro);
		fprintf(config, "player1 = %s\n", sjogo->nome);
		fprintf(config, "time1 = %ld\n", sjogo->tempo.totalSegundos);

	//Se não estiver em branco
	}else{

		comparaIni(&dadosIni, sjogo, tam);

		//gravando no arquivo;
		for(int i = 0; i < dadosIni.qsize; i++){
			fprintf(config, "size = %d\n", dadosIni.size[i]);
			for(int j = 0; j < dadosIni.qplayers[i]; j++){
				fprintf(config, "player%d = %s\n", j+1, dadosIni.player[i][j]);
				fprintf(config, "time%d = %ld\n", j+1, dadosIni.time[i][j]);
			}
			if(i < dadosIni.qsize - 1)
				fprintf(config, "\n");
		}
	}

	fclose(config);
}

//Função que converte um inteiro em um binário
//Auxiliar para a função resolve a fim de testar as combinações de números possíveis
void binario(int n, int **bin, int i){
	if(n == 0){
		(*bin)[i] = n;
	} else{
		binario(n/2, bin, i-1);
		(*bin)[i] = n % 2;
	}
}

//função recursiva para a realização dos testes que resolvem o jogo
void testes(Jogo *jogo, int ***matBin, int i, int *conf){
	int *bin = malloc(jogo->tamTabuleiro * sizeof(int));
	inicializaVetor(bin, jogo->tamTabuleiro);

	//debug
	//printf(YELLOW("Linha atual: %d\n"), i);

	for(int a = 0; a < pow(2, jogo->tamTabuleiro); a++){
		*conf = 0;
		binario(a, &bin, jogo->tamTabuleiro - 1);

		//debug
		/*for(int e = 0; e < jogo->tamTabuleiro; e++){
			printf("%d", bin[e]);
		}
		printf("\n");*/
		
		//Percorrendo a dimensão do tabuleiro
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			if(bin[j]){
				jogo->tabuleiro.somaLaux[i] += jogo->tabuleiro.matriz[i][j];
				jogo->tabuleiro.somaCaux[j] += jogo->tabuleiro.matriz[i][j];
			}
		}

		//debug
		//printf("S linha: %d\n\n", jogo->tabuleiro.somaLaux[i]);

		if(jogo->tabuleiro.somaLaux[i] == jogo->tabuleiro.somaL[i]){
			if(i != (jogo->tamTabuleiro - 1)){
				//Testando a próxima linha
				testes(jogo, &(*matBin), i+1, conf);
			} else{
				for(int j = 0; j < jogo->tamTabuleiro; j++){
					if(jogo->tabuleiro.somaCaux[j] == jogo->tabuleiro.somaC[j]){
						*conf += 1;
					} else{
						*conf = 0;
						break;
					}
				}
			}
		}

		if(*conf == jogo->tamTabuleiro){
			//debug
			//printf("Linha tual: %d\n", i);

			for(int b = 0; b < jogo->tamTabuleiro; b++){
				(*matBin)[i][b] = bin[b];
			}
			break;
		} else{
			for(int j = 0; j < jogo->tamTabuleiro; j++){
				if(bin[j]){
					jogo->tabuleiro.somaLaux[i] -= jogo->tabuleiro.matriz[i][j];
					jogo->tabuleiro.somaCaux[j] -= jogo->tabuleiro.matriz[i][j];

					//debug
					/*printf("S linha: %d\n", jogo->tabuleiro.somaLaux[i]);
					printf("S coluna%d: %d\n",j, jogo->tabuleiro.somaCaux[j]);*/
				}
			}
		}
	}
	free(bin);
}

//Função que resolve o jogo encontrando todas as posições a serem adicionadas ao vetor de resposta.
void resolve(Jogo *jogo){

	int **matBin = NULL;
	matBin = criaMatriz(matBin, jogo->tamTabuleiro, jogo->tamTabuleiro);

	inicializaVetor(jogo->tabuleiro.somaLaux, jogo->tamTabuleiro);
	inicializaVetor(jogo->tabuleiro.somaCaux, jogo->tamTabuleiro);

	int conf = 0;
	testes(jogo, &matBin, 0, &conf);

	jogo->tamResp = 0;
	jogo->resposta = criaMatriz(jogo->resposta, TAM_RESP, 2);

	/*//debug
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			printf("%d ", matBin[i][j]);
		}
		printf("\n");
	}*/

	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			if(matBin[i][j]){
				jogo->resposta[jogo->tamResp][0] = i;
				jogo->resposta[jogo->tamResp][1] = j;
				jogo->tamResp++;
			}
		}
	}

	liberaMatriz(matBin, jogo->tamTabuleiro);
}

//Função que termina o jogo encontrando marcando as posições ainda não marcadas
void terminaJogo(Jogo *jogo, int *tamMR){
	for(int i = 0; i < jogo->tamResp; i++){
		//Verificando se as coordenas de resposta ainda não estão salvas em mantem e as salvando
		if(!lecoordenadas(jogo->tabuleiro.mantem, jogo->tabuleiro.contm, jogo->resposta[i][0], jogo->resposta[i][1])){
			jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0] = jogo->resposta[i][0];
			jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1] = jogo->resposta[i][1];

			//Eliminando a coordedada de remove se ela estiver salva
			if(lecoordenadas(jogo->tabuleiro.remove, *tamMR, jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0], jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1])){
				removeLinhaMatriz(jogo->tabuleiro.remove, *tamMR, 2, encontraLinhaMatriz(jogo->tabuleiro.remove, *tamMR, jogo->resposta[i][0], jogo->resposta[i][1]));
				jogo->tabuleiro.contr -= 1;
			}

			jogo->tabuleiro.contm += 1;
		}
	}
	
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			//Removendo coordenadas que não pertencem à resposta de mantem
			if(lecoordenadas(jogo->tabuleiro.mantem, *tamMR, i, j) && !lecoordenadas(jogo->resposta, jogo->tamResp, i, j)){
				removeLinhaMatriz(jogo->tabuleiro.mantem, jogo->tabuleiro.contm, 2, encontraLinhaMatriz(jogo->tabuleiro.mantem, *tamMR, i, j));
				jogo->tabuleiro.contm -= 1;
			}
			//Adicionando as coordenadas restantes à matriz remove
			if(!lecoordenadas(jogo->tabuleiro.mantem, *tamMR, i, j) && !lecoordenadas(jogo->tabuleiro.remove, *tamMR, i, j)){
				jogo->tabuleiro.remove[jogo->tabuleiro.contr][0] = i;
				jogo->tabuleiro.remove[jogo->tabuleiro.contr][1] = j;

				jogo->tabuleiro.contr += 1;
			}
		}
	}
}

//Função apenas para a impressão do tabuleiro
void imprimeTabuleiro(Tabuleiro tabuleiro, int n){

	printf("\n");

	//Imprimindo o índice das colunas
	printf("\t\t     " H_TAB_TL);
	for(int i = 0; i < n - 1; i++){
		printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TJ);
	}
	printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TR "\n");

	printf("\t\t     " H_TAB_VER);
	for(int i = 0; i < n; i++){
		printf(BOLD(YELLOW(" %3d ")), i+1);
		if(i < (n - 1))
			printf(H_TAB_VER);
	}
	printf(H_TAB_VER"\n");

	printf("\t\t" H_TAB_TL H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MJ);
	for(int i = 0; i < n; i++){
		if(i < (n - 1))
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BJ);
		else
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR);
	}
	printf(H_TAB_MJ H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TR);
	printf("\n");
	
	//imprimindo o índice das linhas, a matriz do tabuleiro e a coluna de somas das linhas
	for(int i = 0; i < n; i++){
		//Indice das linhas
		printf("\t\t" H_TAB_VER BOLD(YELLOW("%3d ")) H_TAB_VER, i+1);

		//matriz do tabuleiro
		for(int j = 0; j < n; j++){
			if(lecoordenadas(tabuleiro.mantem, n * n, i, j)){
				printf(BOLD(GREEN(" %3d ")), tabuleiro.matriz[i][j]);
			} else if(lecoordenadas(tabuleiro.remove, n * n, i, j)){
				printf(BOLD(RED(" %3d ")), tabuleiro.matriz[i][j]);
			} else{
				printf(" %3d ", tabuleiro.matriz[i][j]);
			}
			if(j < (n - 1))
				printf(TAB_VER);
		}

		//soma das linhas
		if(tabuleiro.somaL[i] == tabuleiro.somaLaux[i]){
			printf(H_TAB_VER CYAN(BOLD("%3d ")), tabuleiro.somaL[i]);
		}else{
			printf(H_TAB_VER CYAN("%3d "), tabuleiro.somaL[i]);
		}
		printf(H_TAB_VER "\n");

		if(i < (n - 1))
			printf("\t\t" H_TAB_ML H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MR);

		for(int j = 0; j < n; j++){
			if(i < (n - 1)){
				printf(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR);
				if(j < (n - 1))
					printf(TAB_MJ);
			}
		}
		
		if(i < (n - 1)){
			printf(H_TAB_ML H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MR);
			printf("\n");
		}
	}

	printf("\t\t" H_TAB_BL H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MJ);
	for(int i = 0; i < n; i++){
		if(i < (n - 1))
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TJ);
		else
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR);
	}
	printf(H_TAB_MJ H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BR);
	
	//impirmindo a linha de somas de colunas
	printf("\n\t\t     " H_TAB_VER);
	for(int i = 0; i < n; i++){
		if(tabuleiro.somaC[i] == tabuleiro.somaCaux[i]){
			printf(CYAN(BOLD(" %3d ")), tabuleiro.somaC[i]);
		} else{
			printf(CYAN(" %3d "), tabuleiro.somaC[i]);
		}
		if(i < (n - 1))
			printf(H_TAB_VER);
	}
	printf(H_TAB_VER "\n");

	printf("\t\t     " H_TAB_BL);
	for(int i = 0; i < n - 1; i++){
		printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BJ);
	}
	printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BR);
	printf("\n\n");
}

//Função que efetivamente executa o jogo
void executaJogo(Jogo *jogo){

	//Encontrando uma das soluções possíveis do jogo
	resolve(jogo);

	//Variável que indica o fim de jogo
	int fimDeJogo = 0;

	//Variável para armazenar o tempo no inicio do jogo
	long tempoInicial = time(NULL);

	//debug
	//printf("%ld\n", tempoInicial);

	//Variável que indica se o jogo foi resolvido automaticamente
	//Apenas para inidcar se a gravação do jogador no arquivo ini
	int resolver = 0;

	int tamMR = jogo->tamTabuleiro * jogo->tamTabuleiro;

	//Caso seja criado um novo jogo
	if(jogo->tempo.totalSegundos == 0){
		//Variáveis para marcação e remoção.
		jogo->tabuleiro.contm = 0, 	jogo->tabuleiro.contr = 0;
		inicializaMatriz(jogo->tabuleiro.mantem, jogo->tamTabuleiro, 2, -1);
		inicializaMatriz(jogo->tabuleiro.remove, jogo->tamTabuleiro, 2, -1);
	}

	//Verificando a soma atual dos termos baseado nas remoções do usuário.
	inicializaVetor(jogo->tabuleiro.somaLaux, jogo->tamTabuleiro);
	inicializaVetor(jogo->tabuleiro.somaCaux, jogo->tamTabuleiro);
	for(int i = 0; i < jogo->tamTabuleiro; i++){
		for(int j = 0; j < jogo->tamTabuleiro; j++){
			//Inicializando os vetores auxiliares de soma de linha e coluna
			jogo->tabuleiro.somaLaux[i] += jogo->tabuleiro.matriz[i][j];
			jogo->tabuleiro.somaCaux[j] += jogo->tabuleiro.matriz[i][j];

			for(int cont = 0; cont < jogo->tabuleiro.contr; cont++){
				if(i == jogo->tabuleiro.remove[cont][0] && j == jogo->tabuleiro.remove[cont][1]){
					jogo->tabuleiro.somaLaux[i] -= jogo->tabuleiro.matriz[i][j];
					jogo->tabuleiro.somaCaux[j] -= jogo->tabuleiro.matriz[i][j];
				}
			}
		}
	}
	
	//Variável para leitura do comando
	Comando comando;

	//Variável para leitura do nome do arquivo
	char nomeArquivo[TAM_NOME];

	imprimeTabuleiro(jogo->tabuleiro, jogo->tamTabuleiro);

	//Loop da partida
	while(!fimDeJogo){

		//Variável que recebe o "númeoro" da coordenada digitada pelo usuário
		int n;

		//Leitura do comando
		printf(GREEN("%s") CYAN(", digite o comando: "), jogo->nome);
		scanf("%s", comando.acao);

		//Verificando se comando = "manter" ou "remover"
		if(!strcmp(comando.acao, "manter") || !strcmp(comando.acao, "remover")){
			scanf("%d", &n);
			limpaBuffer();
			separaCoordenadas(n, &comando.linha, &comando.coluna);

			//Validação da entrada dos indices
			while(comando.linha < 0 || comando.linha > jogo->tamTabuleiro || comando.coluna < 0 || comando.coluna > jogo->tamTabuleiro){
				printf(BOLD(RED("\nINDICE DE LINHA OU COLUNA INVÁVLIDO!\n\n")));
				printf(CYAN("digite os indices novamente: "));
				scanf("%d", &n);
				limpaBuffer();
				separaCoordenadas(n, &comando.linha, &comando.coluna);
			}
			if(!strcmp(comando.acao, "manter")){
					while(lecoordenadas(jogo->tabuleiro.mantem, tamMR, (comando.linha - 1), (comando.coluna - 1))){
						printf(BOLD(RED("\nESTES ÍNDICES JÁ FORAM SELECIONADOS!\n\n")));
						printf(CYAN("digite os indices novamente: "));
						scanf("%d", &n);
						limpaBuffer();
						separaCoordenadas(n, &comando.linha, &comando.coluna);
					}
				} else{
					while(lecoordenadas(jogo->tabuleiro.remove, tamMR, (comando.linha - 1), (comando.coluna - 1))){
						printf(BOLD(RED("\nESTES ÍNDICES JÁ FORAM SELECIONADOS!\n\n")));
						printf(CYAN("digite os indices novamente: "));
						scanf("%d", &n);
						limpaBuffer();
						separaCoordenadas(n, &comando.linha, &comando.coluna);
					}
				}

		//Verificando se o comando = "salvar"
		} else if(!strcmp(comando.acao, "salvar")){
			scanf("%s", nomeArquivo);
		}

		//Validação da entrada do comando
		while(strcmp(comando.acao, "manter") && strcmp(comando.acao, "remover") && strcmp(comando.acao, "dica") && strcmp(comando.acao, "resolver") && strcmp(comando.acao, "salvar") && strcmp(comando.acao, "voltar")){
			limpaBuffer();
			printf(BOLD(RED("\nCOMANDO INVALIDO!\n\n")));
			printf(GREEN("%s") CYAN(", digite o comando: "), jogo->nome);
			scanf("%s", comando.acao);

			//Verificando se comando = "manter" ou "remover"
			if(!strcmp(comando.acao, "manter") || !strcmp(comando.acao, "remover")){
				scanf("%d", &n);
				limpaBuffer();
		
				separaCoordenadas(n, &comando.linha, &comando.coluna);

				//Validação da entrada dos indices
				while(comando.linha < 0 || comando.linha > jogo->tamTabuleiro || comando.coluna < 0 || comando.coluna > jogo->tamTabuleiro){
					printf(BOLD(RED("\nINDICE DE LINHA OU COLUNA INVÁVLIDO!\n\n")));
					printf(CYAN("digite os indices novamente: "));
					scanf("%d", &n);
					limpaBuffer();
			
					separaCoordenadas(n, &comando.linha, &comando.coluna);
				}
				
				if(!strcmp(comando.acao, "manter")){
					while(lecoordenadas(jogo->tabuleiro.mantem, tamMR, (comando.linha - 1), (comando.coluna - 1))){
						printf(BOLD(RED("\nESTES ÍNDICES JÁ FORAM SELECIONADOS!\n\n")));
						printf(CYAN("digite os indices novamente: "));
						scanf("%d", &n);
						limpaBuffer();

						separaCoordenadas(n, &comando.linha, &comando.coluna);
					}
				} else{
					while(lecoordenadas(jogo->tabuleiro.remove, tamMR, (comando.linha - 1), (comando.coluna - 1))){
						printf(BOLD(RED("\nESTES ÍNDICES JÁ FORAM SELECIONADOS!\n\n")));
						printf(CYAN("digite os indices novamente: "));
						scanf("%d", &n);
						limpaBuffer();
				
						separaCoordenadas(n, &comando.linha, &comando.coluna);
					}
				}

			} else if(!strcmp(comando.acao, "salvar")){
				scanf("%s", nomeArquivo);
		
			}
		}

		//Execuntando a função do comando digitado

		//comando "manter"
		if(!strcmp(comando.acao, "manter")){
			jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0] = comando.linha - 1;
			jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1] = comando.coluna - 1;

			//Eliminando a coordedada de remove se ela estiver salva
			if(lecoordenadas(jogo->tabuleiro.remove, tamMR, jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0], jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1])){
				removeLinhaMatriz(jogo->tabuleiro.remove, tamMR, 2, encontraLinhaMatriz(jogo->tabuleiro.remove, tamMR, (comando.linha - 1), (comando.coluna - 1)));
				jogo->tabuleiro.contr--;
			}

			jogo->tabuleiro.contm++;

		//comando "remover"
		} else if(!strcmp(comando.acao, "remover")){
			jogo->tabuleiro.remove[jogo->tabuleiro.contr][0] = comando.linha - 1;
			jogo->tabuleiro.remove[jogo->tabuleiro.contr][1] = comando.coluna - 1;

			//Eliminando a coordenada de mantem se ela estiver salva
			if(lecoordenadas(jogo->tabuleiro.mantem, tamMR, jogo->tabuleiro.remove[jogo->tabuleiro.contr][0], jogo->tabuleiro.remove[jogo->tabuleiro.contr][1])){
				removeLinhaMatriz(jogo->tabuleiro.mantem, tamMR, 2, encontraLinhaMatriz(jogo->tabuleiro.mantem, tamMR, (comando.linha - 1), (comando.coluna - 1)));
				jogo->tabuleiro.contm--;
			}

			jogo->tabuleiro.contr++;

		//Comando "dica"
		} else if(!strcmp(comando.acao, "dica")){
			int ok = 0;
			int cont = 0;

			//Verificando se todas as coordedas de resposta já foram mantidas
			for(int i = 0; i < jogo->tamResp; i++){
				if(lecoordenadas(jogo->tabuleiro.mantem, jogo->tabuleiro.contm, jogo->resposta[i][0], jogo->resposta[i][1])){
					cont++;
				}
			}

			if(cont < jogo->tamResp){
				while(!ok){
					//Selecionando uma posição aleatória.
					int la = rand() % jogo->tamTabuleiro; 
					int ca = rand() % jogo->tamTabuleiro;
					
					if(lecoordenadas(jogo->resposta, jogo->tamResp, la, ca) && !lecoordenadas(jogo->tabuleiro.mantem, tamMR, la, ca)){
						jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0] = la;
						jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1] = ca;

						//Eliminando a coordedada de remove se ela estiver salva
						if(lecoordenadas(jogo->tabuleiro.remove, tamMR, jogo->tabuleiro.mantem[jogo->tabuleiro.contm][0], jogo->tabuleiro.mantem[jogo->tabuleiro.contm][1])){
							removeLinhaMatriz(jogo->tabuleiro.remove, tamMR, 2, encontraLinhaMatriz(jogo->tabuleiro.remove, tamMR, la, ca));
							jogo->tabuleiro.contr--;
						}
						jogo->tabuleiro.contm++;
						ok = 1;
					}
				}
			} else{
				printf(BOLD(RED("\nNÂO HÁ MAIS DICAS!\n\n")));
			}

		//comando "resolver"
		} else if(!strcmp(comando.acao, "resolver")){
			terminaJogo(jogo, &tamMR);
			resolver = 1;

		//comando "salvar"
		} else if(!strcmp(comando.acao, "salvar")){
			jogo->tempo.totalSegundos = (time(NULL) - tempoInicial) + jogo->tempo.totalSegundos;
			
			if(!gravaJogo(nomeArquivo, jogo)){
				do{
					printf(BOLD(RED("\nERRO AO GRAVAR O JOGO!\n\n")));
					printf("Por favor, digite o nome do arquivo novamente: ");
					scanf("%s", nomeArquivo);
				}while(!gravaJogo(nomeArquivo, jogo));
			}

		//comando "voltar"
		} else if(!strcmp(comando.acao, "voltar")){
			jogo->tempo.totalSegundos = (time(NULL) - tempoInicial) + jogo->tempo.totalSegundos;
			if(menuInicial(jogo)){
				fimDeJogo = 1;
				break;
			}
		}

		//Verificando a soma atual dos termos baseado nas remoções do usuário.
		inicializaVetor(jogo->tabuleiro.somaLaux, jogo->tamTabuleiro);
		inicializaVetor(jogo->tabuleiro.somaCaux, jogo->tamTabuleiro);
		for(int i = 0; i < jogo->tamTabuleiro; i++){
			for(int j = 0; j < jogo->tamTabuleiro; j++){
				//Inicializando os vetores auxiliares de soma de linha e coluna
				jogo->tabuleiro.somaLaux[i] += jogo->tabuleiro.matriz[i][j];
				jogo->tabuleiro.somaCaux[j] += jogo->tabuleiro.matriz[i][j];

				for(int cont = 0; cont < jogo->tabuleiro.contr; cont++){
					if(i == jogo->tabuleiro.remove[cont][0] && j == jogo->tabuleiro.remove[cont][1]){
						jogo->tabuleiro.somaLaux[i] -= jogo->tabuleiro.matriz[i][j];
						jogo->tabuleiro.somaCaux[j] -= jogo->tabuleiro.matriz[i][j];
					}
				}
			}
		}
		
		//Verificando a vitória do jogador
		int correto = 0;
		for(int i = 0; i < jogo->tamTabuleiro; i++){
			if(jogo->tabuleiro.somaC[i] == jogo->tabuleiro.somaCaux[i])
				correto++;
			if(jogo->tabuleiro.somaL[i] == jogo->tabuleiro.somaLaux[i])
				correto++;
		}
		if(correto == (2 * jogo->tamTabuleiro)){
			jogo->tempo.totalSegundos = (time(NULL) - tempoInicial) + jogo->tempo.totalSegundos;
			terminaJogo(jogo, &tamMR);

			imprimeTabuleiro(jogo->tabuleiro, jogo->tamTabuleiro);

			printf(BOLD(GREEN("\n\t\tJOGO RESOLVIDO!\n")));
			
			//Se o jogador não tiver solicitado a solução automática do jogo
			if(!resolver){
				gravaIni(jogo);
			
				FILE *config = NULL;
				Ini dados = leIni(config, jogo);
				int entrou = 0;

				for(int i = 0; i < dados.qsize; i++){
					if(dados.size[i] == jogo->tamTabuleiro){
						for(int j = 0; j < dados.qplayers[i]; j++){
							if(!strcmp(dados.player[i][j], jogo->nome)){
								printf(BOLD(GREEN("\n\t\tPARABÉNS VOCÊ ESTÁ NA POSIÇÃO")));
								printf(BOLD(YELLOW(" #%d ")), j+1);
								printf(BOLD(GREEN("DO RANKING!\n")));
								entrou = 1;
								break;
							}
						}
					}
				}

				if(!entrou)
					printf(BOLD(YELLOW("\n\t\tQUE PENA! Você ainda não está no Ranking!\n")));
			}

			fimDeJogo = 1;
			break;
		}

		imprimeTabuleiro(jogo->tabuleiro, jogo->tamTabuleiro);

		//imprimindo para debug
		/*for(int i = 0; i < jogo->tabuleiro.contm; i++){
			for(int j = 0; j < 2; j++){
				printf("%d ", jogo->tabuleiro.mantem[i][j]);
			}
			printf("\n");
		}

		for(int i = 0; i < jogo->tabuleiro.contr; i++){
			for(int j = 0; j < 2; j++){
				printf("%d ", jogo->tabuleiro.remove[i][j]);
			}
			printf("\n");
		}*/

	}

	if(jogo->tempo.totalSegundos > 0){
		//Calculando e imprimindo o tempo de jogo
		calculaTempo(&jogo->tempo);
		printf(BOLD(BLUE("\nTempo de jogo: ")));
		printf("%02d:%02d:%02d\n\n", jogo->tempo.hora, jogo->tempo.min, jogo->tempo.seg);
		jogo->tempo.totalSegundos = 0;
	}
}

//Função que cira um novo jogo.
void novoJogo(Jogo *novoJogo){
	
	//Lê o nome do Jogador
	printf(CYAN("Digite o nome do jogador: "));
	fgets(novoJogo->nome, TAM_NOME, stdin);
	removeEnter(novoJogo->nome, TAM_NOME);
	printf("\n");
	
	//Lê o tamanho do Tabuleiro
	printf(CYAN("Digite o tamanho do tabuleiro(3 à 9): "));
	scanf("%d", &novoJogo->tamTabuleiro);
	limpaBuffer();
	while(novoJogo->tamTabuleiro < 3 || novoJogo->tamTabuleiro > 9){
		printf(BOLD(RED("\nTAMANHO DO TABULEIRO INVÁLIDO!\n\n")));
		printf(CYAN("Digite o tamanho do tabuleiro(3 à 9): "));
		scanf("%d", &novoJogo->tamTabuleiro);
		limpaBuffer();
	}
	printf("\n");
	
	//Lê o nível de dificuldade
	if(novoJogo->tamTabuleiro > 4){
		if(novoJogo->tamTabuleiro < 7){
			printf(CYAN("Digite o nível de dificuldade: \n\n"));
			printf(BOLD(YELLOW("\t\t\"F\" - ")) "Fácil \n" BOLD(YELLOW("\t\t\"M\" - ")) "Médio \n\n");
			printf(CYAN("Dificuldade: "));
			scanf(" %c", &novoJogo->dificuldade);
			while(novoJogo->dificuldade != 'F' && novoJogo->dificuldade != 'M'){
				printf(BOLD(RED("\nDIFICULDADE INVÁLIDA!\n\n")));
				printf(CYAN("Dificuldade: "));
				scanf(" %c", &novoJogo->dificuldade);
			}
			printf("\n");
		} else{
			printf(CYAN("Digite o nível de dificuldade: \n\n"));
			printf(BOLD(YELLOW("\t\t\"F\" - ")) "Fácil \n" BOLD(YELLOW("\t\t\"M\" - ")) "Médio \n" BOLD(YELLOW("\t\t\"D\" - ")) "Difícil\n\n");
			printf(CYAN("Dificuldade: "));
			scanf(" %c", &novoJogo->dificuldade);
			limpaBuffer();
			while(novoJogo->dificuldade != 'F' && novoJogo->dificuldade != 'M' && novoJogo->dificuldade != 'D'){
				printf(BOLD(RED("\nDIFICULDADE INVÁLIDA!\n\n")));
				printf(CYAN("Dificuldade: "));
				scanf(" %c", &novoJogo->dificuldade);
				limpaBuffer();
			}
			printf("\n");
		}
	}else{
		novoJogo->dificuldade = 'F';
	}
	
//Criação do tabuleiro
	srand(time(NULL));
	
	//Alocando os vetores de somas de linhas e colunas
	novoJogo->tabuleiro.somaL = malloc(novoJogo->tamTabuleiro * sizeof(int));
	novoJogo->tabuleiro.somaC = malloc(novoJogo->tamTabuleiro * sizeof(int));
	inicializaVetor(novoJogo->tabuleiro.somaL, novoJogo->tamTabuleiro);
	inicializaVetor(novoJogo->tabuleiro.somaC, novoJogo->tamTabuleiro);

	//Alocando e inicializando os vetores de soma atual
	novoJogo->tabuleiro.somaLaux = malloc(novoJogo->tamTabuleiro * sizeof(int));
	novoJogo->tabuleiro.somaCaux = malloc(novoJogo->tamTabuleiro * sizeof(int));
	inicializaVetor(novoJogo->tabuleiro.somaLaux, novoJogo->tamTabuleiro);
	inicializaVetor(novoJogo->tabuleiro.somaCaux, novoJogo->tamTabuleiro);
	
	//Alocando a matriz do tabuleiro
	novoJogo->tabuleiro.matriz = criaMatriz(novoJogo->tabuleiro.matriz, novoJogo->tamTabuleiro, novoJogo->tamTabuleiro);
	
	//Gerando da matriz do tabuleiro

	//Dificuladade: Fácil
	if(novoJogo->dificuldade == 'F'){
		for(int i = 0; i < novoJogo->tamTabuleiro; i++){
			for(int j = 0; j < novoJogo->tamTabuleiro; j++){
				novoJogo->tabuleiro.matriz[i][j] = (rand() % 9 + 1);
				
				//Adicionando as somas de linhas e colunas aos respectivos vetores
				if((rand() % 2)){
					novoJogo->tabuleiro.somaL[i] += novoJogo->tabuleiro.matriz[i][j];
					novoJogo->tabuleiro.somaC[j] += novoJogo->tabuleiro.matriz[i][j];
				}
			}
		}

	//Dificuldade: Médio
	} else if(novoJogo->dificuldade == 'M'){
		int ok;

		for(int i = 0; i < novoJogo->tamTabuleiro; i++){
			for(int j = 0; j < novoJogo->tamTabuleiro; j++){
				novoJogo->tabuleiro.matriz[i][j] = (rand() % 9 + 1);

				novoJogo->tabuleiro.somaLaux[i] += novoJogo->tabuleiro.matriz[i][j];
				novoJogo->tabuleiro.somaCaux[j] += novoJogo->tabuleiro.matriz[i][j];
			}
		}

		do{
			ok = 1;
			for(int i = 0; i < novoJogo->tamTabuleiro; i++){
				for(int j = 0; j < novoJogo->tamTabuleiro; j++){
					//Adicionando as somas de linhas e colunas aos respectivos vetores
					if(novoJogo->tamTabuleiro && (rand() % 2)){
						novoJogo->tabuleiro.somaL[i] += novoJogo->tabuleiro.matriz[i][j];
						novoJogo->tabuleiro.somaC[j] += novoJogo->tabuleiro.matriz[i][j];
					}
				}
			}

			for(int i = 0; i < novoJogo->tamTabuleiro; i++){
				if(!novoJogo->tabuleiro.somaL[i] || !novoJogo->tabuleiro.somaC[i]){
					ok = 0;
					break;
				}
				if(novoJogo->tabuleiro.somaL[i] == novoJogo->tabuleiro.somaLaux[i]){
					ok = 0;
					break;
				}
				if(novoJogo->tabuleiro.somaC[i] == novoJogo->tabuleiro.somaCaux[i]){
					ok = 0;
					break;
				}
			}

			if(!ok){
				inicializaVetor(novoJogo->tabuleiro.somaL, novoJogo->tamTabuleiro);
				inicializaVetor(novoJogo->tabuleiro.somaC, novoJogo->tamTabuleiro);
			}
		}while(!ok);
	
	//Dificuldade: Difícil
	} else{
		int ok;

		for(int i = 0; i < novoJogo->tamTabuleiro; i++){
			for(int j = 0; j < novoJogo->tamTabuleiro; j++){
				novoJogo->tabuleiro.matriz[i][j] = ((rand() % 18) + 1) - 9;
				novoJogo->tabuleiro.somaLaux[i] += novoJogo->tabuleiro.matriz[i][j];
				novoJogo->tabuleiro.somaCaux[j] += novoJogo->tabuleiro.matriz[i][j];
			}
		}

		do{
			ok = 1;
			for(int i = 0; i < novoJogo->tamTabuleiro; i++){
				for(int j = 0; j < novoJogo->tamTabuleiro; j++){
					//Adicionando as somas de linhas e colunas aos respectivos vetores
					if(novoJogo->tamTabuleiro && (rand() % 2)){
						novoJogo->tabuleiro.somaL[i] += novoJogo->tabuleiro.matriz[i][j];
						novoJogo->tabuleiro.somaC[j] += novoJogo->tabuleiro.matriz[i][j];
					}
				}
			}

			for(int i = 0; i < novoJogo->tamTabuleiro; i++){
				if(novoJogo->tabuleiro.somaL[i] == novoJogo->tabuleiro.somaLaux[i]){
					ok = 0;
					break;
				}
				if(novoJogo->tabuleiro.somaC[i] == novoJogo->tabuleiro.somaCaux[i]){
					ok = 0;
					break;
				}
			}

			if(!ok){
				inicializaVetor(novoJogo->tabuleiro.somaL, novoJogo->tamTabuleiro);
				inicializaVetor(novoJogo->tabuleiro.somaC, novoJogo->tamTabuleiro);
			}
		}while(!ok);
	}

	//Alocando e inicializando as matrizes mantem e remove com -1
	int tamMR = novoJogo->tamTabuleiro * novoJogo->tamTabuleiro;
	novoJogo->tabuleiro.mantem = criaMatriz(novoJogo->tabuleiro.mantem, tamMR, 2);
	novoJogo->tabuleiro.remove = criaMatriz(novoJogo->tabuleiro.mantem, tamMR, 2);
	inicializaMatriz(novoJogo->tabuleiro.mantem, tamMR, 2, -1);
	inicializaMatriz(novoJogo->tabuleiro.remove, tamMR, 2, -1);

	//Inicializando os vetores auxiliares de soma de linha e coluna
	for(int i = 0; i < novoJogo->tamTabuleiro; i++){
		for(int j = 0; j < novoJogo->tamTabuleiro; j++){
			novoJogo->tabuleiro.somaLaux[i] += novoJogo->tabuleiro.matriz[i][j];
			novoJogo->tabuleiro.somaCaux[j] += novoJogo->tabuleiro.matriz[i][j];
		}
	}

	//Inicializando com zero para indicar que um novo jogo foi criado
	novoJogo->tempo.totalSegundos = 0;

	executaJogo(novoJogo);
}

//Exibe o Ranking de jogadores
void exibirRanking(Jogo *jogo){
	FILE *config = NULL;
	Ini dados;
	dados = leIni(config, jogo);

	Tempo tempo;
	
	printf("<");
	for(int i = 0; i < 63; i++)
		printf("=");
	printf(">\n\n");

	if(dados.qsize > 0){
		printf(BOLD(GREEN("\tRANKING ATUAL DOS JOGADORES DE SUMPLETE\n\n")));

		printf("<");
		for(int i = 0; i < 63; i++)
			printf("=");
		printf(">\n\n");

		for(int i = 0; i < dados.qsize; i++){
			printf(BOLD(CYAN("Categoria: "))); 
			printf("%dx%d\n\n", dados.size[i], dados.size[i]);
			for(int j = 0; j < dados.qplayers[i]; j++){
				tempo.totalSegundos = dados.time[i][j];
				calculaTempo(&tempo);
				printf(BOLD(YELLOW("\t#%d")), j+1); 
				printf(" - ");
				printf(BOLD(GREEN("%-30s ")), dados.player[i][j]);
				printf(BOLD(BLUE("\t Tempo: ")));
				printf("%02d:%02d:%02d\n", tempo.hora, tempo.min, tempo.seg);
			}
			printf("\n");
		}

		printf("<");
		for(int i = 0; i < 63; i++)
			printf("=");
		printf(">\n\n");
	} else{
		printf(BOLD(YELLOW("Infelizmente ainda não há jogaodres no Raniking!\n\n")));
	}

	menuInicial(jogo);
}

//Função que impime o menu inicial do jogo, e faz a leitura da opção.
int menuInicial(Jogo *jogo){

	int op;
	char nomeArquivo[TAM_NOME];
	
	printf("\n");

	//Imprimindo o menu
	for(int i = 0; i < 65; i++)
		printf(BOLD(YELLOW(H_TAB_HOR)));
	printf("\n\n");

	printf(BOLD(YELLOW("\t\t0 - ")) "Sair do jogo\n");
	printf(BOLD(YELLOW("\t\t1 - ")) "Começar novo jogo\n");
	printf(BOLD(YELLOW("\t\t2 - ")) "Continuar um jogo salvo\n");
	printf(BOLD(YELLOW("\t\t3 - ")) "Continuar o jogo atual\n"); 
	printf(BOLD(YELLOW("\t\t4 - ")) "Exibir ranking\n\n");
	printf("Durante o jogo, digite \"" GREEN("voltar") "\" para retornar ao menu.\n\n");

	for(int i = 0; i < 65; i++)
		printf(BOLD(YELLOW(H_TAB_HOR)));
	printf("\n\n");
	
	//Lendo a opção
	printf(CYAN("Escolha uma opção: "));
	scanf("%d", &op);
	limpaBuffer();

	while(op != 0 && op != 1 && op != 2 && op != 3 && op != 4){
		printf(BOLD(RED("\nOPÇÃO INVÁLIDA!\n\n")));
		printf(CYAN("Escolha uma opção: "));
		scanf("%d", &op);
		limpaBuffer();
	}
	printf("\n");

	while(op == 3 && jogo->tempo.totalSegundos <= 0){
		printf(BOLD(RED("\nNEHNHUM JOGO ATUAL ENCONTRADO!\n\n")));
		printf(CYAN("Escolha uma opção: "));
		scanf("%d", &op);
		limpaBuffer();
	}
	
	switch(op){
		case 0:
			printf(GREEN("\nObrigado por jogar") BOLD(YELLOW(" SUMPLETE! \n\n")));
			return 1;
			break;
		case 1:
			novoJogo(jogo);
			return 1;
			break;
		case 2:
			char sn;
			printf(CYAN("\nDigite o nome do arquivo: "));
			scanf("%s", nomeArquivo);
	
			if(!leJogo(nomeArquivo, jogo)){
				do{
					printf(BOLD(RED("\nERRO! NÃO FOI POSSÍVEL FAZER A LEITURA DO ARQUIVO!\n")));
					printf(BOLD(YELLOW("CERTIFIQUE-SE DE QUE EXISTA UM ARQUIVO COM ESSE NOME!\n\n")));
					
					do{
						printf(CYAN("Dejesa tentar novamente? [S/N]: "));
						scanf(" %c", &sn);
						limpaBuffer();

						if(sn != 'S' && sn != 'N')
							printf(BOLD(RED("\nOPÇÃO INVÁLIDA\n\n")));

					} while(sn != 'S' && sn != 'N');

					if(sn == 'S'){
						printf(CYAN("\nPor favor, digite o nome do arquivo novamente: "));
						scanf("%s", nomeArquivo);
					} else{
						menuInicial(jogo);
						break;
					}
				}while(!leJogo(nomeArquivo, jogo));
			}

			if(sn == 'N')
				break;

			executaJogo(jogo);
			return 1;
			
			break;
		case 3:
			break;
		case 4:
			exibirRanking(jogo);
			break;
	}
	return 0;
}
