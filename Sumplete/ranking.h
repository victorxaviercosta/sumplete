#ifndef RANKING_H
#define RANKING_H

#include "formats.h"
#include "tools.h"
#include "interfaces.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZES 7
#define MAX_PLAYERS_PER_SIZE 5

typedef struct {
    int n_sizes;
    int sizes[MAX_SIZES];
    int n_players[MAX_SIZES];
    Player players[MAX_SIZES][MAX_PLAYERS_PER_SIZE];
} Ranking;

//Allocates and initializes memmory for a Ranking structure.
Ranking* createRanking();

//Frees memmory for a Ranking structure.
void freeRanking(Ranking** ranking);

//Reads a .ini file contanning the game ranking information.
void readRanking(Ranking* ranking);

//Writes the ranking information in the .ini file (updating it).
void writeRanking(char* file_name, Ranking* ranking);

//Verifies if the current player time is able to enter the rank.
//Retruns the rank position or 0 if it isn't albe to enter the rank.
int verifyRanking(Ranking* ranking, int size, Player player);

//Prints-out the current game rank.
void showRanking();

#endif //RANKING_H