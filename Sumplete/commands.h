#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"
#include "tools.h"
#include "interfaces.h"
#include "board.h"
#include "ranking.h"

//Reads and interprets the main menu input.
//Also defines the flux of the aplication depending on the user descisions.
int mainMenuInput();

//Reads a file name.
bool readFileName(char* file_name);

//Reads the player name.
void readName(char* name);

//Reads the board size.
void readBoardSize(int* size);

//Difficult selection Interface.
void chooseDifficult(char* difficult, int* boardSize);

//Validate a file name (veryfies if it's extention is .txt).
void validateFileName(char* file_name, bool* error);

//Reads and interprets the player command.
void readCommand(Game* game);

#endif //COMMANDS_H