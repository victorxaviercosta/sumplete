//Victor Xavier Costa - 23.1.4003

#ifndef SUMPLETELIB_H
#define SUMPLETELIB_H

#include "formats.h"
#include "tools.h"
#include "game.h"
#include "interfaces.h"
#include "board.h"
#include "solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Allocates memory for a new game.
Game* createNewGame();

//Frees the allocated memory for a game.
void deleteGame(Game** game);

//Creates a new game.
Game* newGame();

//Ends and frees all the allocated memory for a game.
void endGame(Game** game);

//Saves a game file.
bool saveGame(Game* game, char* file_name);

//Loads a game-file.
bool loadGame(Game** game, char* file_name);

//Identifies the current game difficult.
void identifyGameDifficult(Game* game);

//Prints-out the game time.
void printGameTime(long game_time_secs);

//The core function where the game is executed.
void sumplete(Game* game);

#endif //SUMPLETELIB_H
