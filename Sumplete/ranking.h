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
    char names[MAX_SIZES][MAX_PLAYERS_PER_SIZE][MAX_NAME_SIZE];
    long int times[MAX_SIZES][MAX_PLAYERS_PER_SIZE];
} Ranking;

//Allocates and initializes memmory for a Ranking structure.
Ranking* createRanking();

//Frees memmory for a Ranking structure.
void freeRanking(Ranking** ranking);

//Reads a .ini file contanning the game ranking information.
void readRanking(Ranking* ranking);




#endif //RANKING_H