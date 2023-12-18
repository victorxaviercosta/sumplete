//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"
#include <stdio.h>

int main(){
	newInterface();
	printf(GREEN("\n\t\t\t  Bem vindo ao Jogo") BOLD(YELLOW(" SUMPLETE!\n\n")));

	int procedure = 0;
	do{
		mainMenu();
		procedure = mainMenuInput();
	} while(procedure != 0);
	
	printf(GREEN("\n\t\t\t  Obrigado por jogar") BOLD(YELLOW(" SUMPLETE!\n\n")));
	return 0;
}