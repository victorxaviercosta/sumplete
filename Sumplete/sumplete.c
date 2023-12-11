//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	newInterface();
	printf("%*s%s", 50, " ", GREEN("\n\t\t\t  Bem vindo ao Jogo") BOLD(YELLOW(" SUMPLETE!\n\n")));
	
	mainMenu();
	
	printf("%*s%s", 50, " ", GREEN("\n\t\t\t  Obrigado por jogar") BOLD(YELLOW(" SUMPLETE!\n\n")));
	return 0;
}