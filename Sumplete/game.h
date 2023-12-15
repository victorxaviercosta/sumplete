#ifndef GAME_H
#define GAME_H

#include "formats.h"
#include "board.h"

//Contains player infomation.
typedef struct{
    char name[MAX_NAME_SIZE];
} Player;

//Contains game information.
typedef struct{
    Player player;
    int size;
    char difficult;

    Board* board;
    Board* playerBoard;

    long game_time;
} Game;

#endif //GAME_H