#ifndef GAME_H
#define GAME_H

#include "formats.h"
#include "board.h"
#include "player.h"

//Contains game information.
typedef struct{
    Player player;
    int size;
    char difficult;

    Board* board;
    Board* playerBoard;

    long int game_time;
    long int starting_time;

    bool playing;
} Game;

#endif //GAME_H