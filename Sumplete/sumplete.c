//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"
#include <stdio.h>

int main(){
	newInterface();
	printf(GREEN("\n\t\t\t  Bem vindo ao Jogo") BOLD(YELLOW(" SUMPLETE!\n\n")));
	
	mainMenu();
	mainMenuInput();
	
	printf(GREEN("\n\t\t\t  Obrigado por jogar") BOLD(YELLOW(" SUMPLETE!\n\n")));
	return 0;
}