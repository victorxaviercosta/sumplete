//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"
#include <stdio.h>

int main(){

	newInterface();

	//initialAnimation();

	int procedure = 0;
	do{
		mainMenu();
		procedure = mainMenuInput();
	} while(procedure != 0);
	
	finalAnimation();
	clear();
	return 0;
}