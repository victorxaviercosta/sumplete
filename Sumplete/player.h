#ifndef PLAYER_H
#define PLAYER_H

#include "formats.h"

//Contains player infomation.
typedef struct{
    char name[MAX_NAME_SIZE];
    long int time;
} Player;

#endif //PLAYER_H.