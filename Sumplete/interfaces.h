#ifndef INTERFACES_H
#define INTERFACES_H

#include "formats.h"
#include "tools.h"
#include "game.h"
#include "commands.h"
#include "sumpletelib.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Function for setting up a new Interface of the game
void newInterface();

//Prints-out the sumplete logo.
void printLogo();

//Prints-out the given string letter by letter.
void printLetterByLetter(char* string);

//Plays the initial animation.
void initialAnimation();

//Plays the final animation.
void finalAnimation();

//Function that prints-out the main menu interface.
void mainMenu();

//Prints-out a game header.
void printGameHeader(Game* game);

//Prints-out the difficult selection Interface.
void printDifficultInterface(char difficult_levels);

//Create new game interface.
void createNewGameInterface(Game* game);

//Prints-out the sumplete game interface.
void sumpleteInterface(Game* game);

#endif //INTERFACES_H