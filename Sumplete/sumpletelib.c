//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"

//Allocates memory for a new game.
Game* createNewGame(){
    Game* newGame = (Game*) malloc(sizeof(Game));
    strcpy(newGame->player.name, "");
    newGame->difficult = ' ';
    newGame->size = 0;

    return newGame;
}

//Frees the allocated memory for a game.
void deleteGame(Game** game){
    free(*game);
    *game = NULL;
}

//Creates a new game.
Game* newGame(){
    Game* game = createNewGame();
    
    createNewGameInterface(game);  

    game->board = createNewBoard(game->size);
    newBoard(game->board, game->size, game->difficult);
    game->playerBoard = createNewBoard(game->size);
    newPlayerBoard(game->playerBoard, game->board, game->size);

    return game;
}

//Ends and frees all the allocated memory for a game.
void endGame(Game** game){
    deleteBoard(&(*game)->playerBoard, (*game)->size);
    deleteBoard(&(*game)->board, (*game)->size);
    deleteGame(game);
}

//Veryfies the win condition.
bool verifyVictory(Game* game){
    bool rowSum = compareArrays(game->board->r_sum, game->playerBoard->r_sum, game->size);
    bool colSum = compareArrays(game->board->c_sum, game->playerBoard->c_sum, game->size);
    if(rowSum && colSum)
        return true;
    return false;
}


void loadGame(){
    //loadGameInterface();
}

//Prints-out the game time.
void printGameTime(long game_time_secs){
    Time time = convertTime(game_time_secs);
    printf(BOLD(BLUE("\n\tTempo de jogo: ")));
    printTime(time);
    printf("\n");
}

//Finalize the game with an final print.
void finalizeGame(Game* game){
    finalizeBoard(game->playerBoard, game->size);
    newInterface();
    printGameHeader(game);
    printBoard(game->board, game->size, game->playerBoard);

    printGameTime(game->game_time);
}

//The core function where the game is executed.
void sumplete(Game* game){
    bool playing = true;
    game->game_time = time(NULL);
    
    //Game main loop.
    while(playing){
        sumpleteInterface(game);
        readCommand(game);

        if(verifyVictory(game))
            playing = false;

        //sleep(5);
    }

    game->game_time = time(NULL) - game->game_time;
    finalizeGame(game);
}
