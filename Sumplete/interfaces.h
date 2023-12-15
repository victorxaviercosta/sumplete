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

//Function that prints-out the main menu interface.
void mainMenu();

//Prints-out a game header.
void printGameHeader(Game* game);

//Prints-out the difficult selection Interface.
void printDifficultInterface(char difficult_levels);

//Create new game interface.
void createNewGameInterface(Game* game);

//Load a saved game Interface.
void loadGameInterface();

//Prints-out the sumplete game interface.
void sumpleteInterface(Game* game);

#endif //INTERFACES_H