#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"
#include "tools.h"
#include "interfaces.h"
#include "board.h"

//Reads and interprets the main menu input.
//Also defines the flux of the aplication depending on the user descisions.
void mainMenuInput();

//Reads the player name.
void readName(char* name);

//Reads the board size.
void readBoardSize(int* size);

//Difficult selection Interface.
void chooseDifficult(char* difficult, int* boardSize);

//Reads and interprets the player command.
void readCommand(Game* game);

//Reads a file name.
void readFileName(char* file_name, bool* error);

#endif //COMMANDS_H