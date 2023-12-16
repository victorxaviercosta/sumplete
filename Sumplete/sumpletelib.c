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

//Loads a game-file.
bool loadGame(Game* game){
    bool error = false;
    char yn;
    char file_name[MAX_NAME_SIZE];
    FILE* file;
    do{
        newInterface();
        readFileName(file_name, &error);
        if(error){
            printf(CYAN("\tDeseja tentar novamente? [s/n]: "));
            scanf("%c", &yn);
            bufferClear();
            if(yn == 'n')
                return false;
        }
    }while(error);

    //Allocating memory for a new game.
    game = createNewGame();

    file = fopen(file_name, "r");
    if(file == NULL){
        error = true;
        printError(UNABLE_TO_OPEN_FILE_ERROR);
    }

    //Reading the game board size.
    fscanf(file, "%d", &game->size);

    //Allocating memory for the game board and played Board.
    game->board = createNewBoard(game->size);
    game->playerBoard = createNewBoard(game->size);
    
    //Reading the board matrix.
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            fscanf(file, "%d", &game->board->matrix[i][j]);
        }
    }

    //Reading the board rows sum.
    for(int i = 0; i < game->size; i++){
        fscanf(file, "%d", game->board->r_sum[i]);
    }

    //Reading the board columns sum.
    for(int j = 0; j < game->size; j++){
        fscanf(file, "%d", game->board->c_sum[j]);
    }

    int n_keep, n_remove, a, b;

    //Reading the number of marks to keep.
    fscanf(file, "%d", &n_keep);

    //Reading the makrs to keep.
    for(int i = 0; i < n_keep; i++){
        fscanf(file, "%d%d", &a, &b);
        game->playerBoard->marked[a-1][b-1] = 1;
    }

    //Reading the number of marks to remove.
    fscanf(file, "%d", &n_remove);

    //Reading the makrs to remove.
    for(int i = 0; i < n_remove; i++){
        fscanf(file, "%d%d", &a, &b);
        game->playerBoard->marked[a-1][b-1] = 0;
    }

    //Reading the player name
    fgets(game->player.name, "%s", file);
    removeBLChar(game->player.name);

    //Reading the game time.
    fscanf(file, "%ld", game->game_time); //STOPD HERE. Have to consider this is not the correct way to store the played time and the calculus is different.
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
    }

    game->game_time = time(NULL) - game->game_time;
    finalizeGame(game);
}
