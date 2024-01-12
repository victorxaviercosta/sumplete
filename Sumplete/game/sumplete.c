#include "sumpletelib.h"
#include <stdio.h>

int main(){
	
	newInterface();

	initialAnimation();
	printf(CYAN("\n\t\t\t  Precione ENTER para começar."));
	bufferClear();

	int procedure = 0;
	do{
		mainMenu();
		procedure = mainMenuInput();
	} while(procedure != 0);
	
	finalAnimation();
	clear();
	return 0;
}