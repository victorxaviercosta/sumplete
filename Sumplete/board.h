#ifndef BOARD_H
#define BOARD_H

#include "tools.h"
#include "formats.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Contains board information.
typedef struct{
    int** matrix;
    int* r_sum;
    int* c_sum;

    int** marked;
} Board;

//Allocates memory for a new sumplete board.
Board* createNewBoard(int size);

//Frees the allocated memory for a board.
void deleteBoard(Board** board, int size);

//Creates a new sumplete board.
void newBoard(Board* board, int size, char difficult);

//Creates a new sumplete player board.
void newPlayerBoard(Board* playerBoard, Board* gameBoard, int size);

//A function to be called at the end for the game to mark all the unmarked cells of the player marked board.
void finalizeBoard(Board* playerBoard, int size);

//Counts the number of "keeps" and removes from the current game.
void countKeepsAndRemoves(Board* playerBoard, int size, int* n_keep, int* n_remove);

//Prints-out the game board.
void printBoard(Board* board, int size, Board* playerBoard);

#endif //BOARD_H