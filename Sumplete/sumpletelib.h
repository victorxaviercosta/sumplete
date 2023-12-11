//Victor Xavier Costa - 23.1.4003

#ifndef SUMPLETELIB_H
#define SUMPLETELIB_H

#include "formats.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>


//Error macros definition.
#define INVALID_OPTION_ERROR "OPÇÃO INVÁLIDA!"
#define INVALID_COMMAND_ERROR "COMANDO INVÁLIDO!"
#define INVALID_SIZE_ERROR "TAMANHO DE TABULEIRO INVÁLIDO!"


//Needed macros for the game.
#define MAX_NAME_SIZE 51
#define MAX_COMMAND_SIZE 11 



//Contains player infomation.
typedef struct{
    char name[MAX_NAME_SIZE];
} Player;

//Contains board information.
typedef struct{
    int** matrix;
    int* r_sum;
    int* c_sum;
} Board;

//Contains game information.
typedef struct{
    Player player;
    int size;
    char difficult;
    int game_time;
} Game;

//Prints-out the specified error message.
void printError(char* error_name);

//Function for setting up a new Interface of the game
void newInterface();

//Allocates memory for a new game.
Game* createNewGame();

//Frees the allocated memory for a game.
void deleteGame(Game** game);

//Function that prints-out the main menu interface.
void mainMenu();

//Reads the input command based on the interface from where it's called.
void readComand(char interface);

//Reads the player name.
void readName(char* name);

//Creates a new game.
void newGame();

#endif
