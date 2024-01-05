#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include "../board/board.h"

// Function that convert decimal to binary 
void decToBinary(int n, int* binary, int size);

//Finds a solution for the game.
void solve(Board* board, int size);

#endif //SOLVER_H