//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"

//Allocates memory for a new game.
Game* createNewGame(){
    Game* newGame = (Game*) malloc(sizeof(Game));
    strcpy(newGame->player.name, "");
    newGame->difficult = ' ';
    newGame->size = 0;
    newGame->game_time = 0;
    newGame->starting_time = 0;

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

//Saves a game file.
bool saveGame(Game* game, char* file_name){
    //Writing a game file.
    FILE *file = fopen(file_name, "w");
    if(file == NULL){
        return false;
    }

    //Writing the game size.
    fprintf(file, "%d\n", game->size);

    //Writing the game matrix.
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            fprintf(file, "%d ", game->board->matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    //Writing the rows sum.
    for(int i = 0; i < game->size; i++){
        fprintf(file, "%d ", game->board->r_sum[i]);
    }
    fprintf(file, "\n");

    //Writing the columns sum.
    for(int j = 0; j < game->size; j++){
        fprintf(file, "%d ", game->board->c_sum[j]);
    }
    fprintf(file, "\n");

    //Counting the number of "keeps" and "removes".
    int n_keep, n_remove;
    countKeepsAndRemoves(game->playerBoard, game->size, &n_keep, &n_remove);

    //Writing the number of marks to keep.
    fprintf(file, "%d\n", n_keep);

    //Writing the marks to keep coordenates.
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            if(game->playerBoard->marked[i][j] == 1){
                fprintf(file, "%d %d\n", i+1, j+1);
            }
        }
    }

    //Writing the number of marks to remove.
    fprintf(file, "%d\n", n_remove);

    //Writing the marks to remove coordenates.
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            if(game->playerBoard->marked[i][j] == 0){
                fprintf(file, "%d %d\n", i+1, j+1);
            }
        }
    }

    //Writing the player name.
    fprintf(file, "%s\n", game->player.name);

    //Writing the played time.
    game->game_time = time(NULL) - game->game_time + game->starting_time;
    fprintf(file, "%ld", game->game_time);

    fclose(file);
    return true;
}

//Loads a game-file.
bool loadGame(Game** game, char* file_name){
    
    //Allocating memory for a new game.
    (*game) = createNewGame();

    FILE* file = fopen(file_name, "r");
    if(file == NULL){
        return false;
    }

    //Reading the game board size.
    fscanf(file, "%d", &(*game)->size);

    //Allocating memory for the game board and played Board.
    (*game)->board = createNewBoard((*game)->size);
    (*game)->playerBoard = createNewBoard((*game)->size);
    
    //Reading the board matrix.
    for(int i = 0; i < (*game)->size; i++){
        for(int j = 0; j < (*game)->size; j++){
            fscanf(file, "%d", &(*game)->board->matrix[i][j]);
        }
    }

    //Reading the board rows sum.
    for(int i = 0; i < (*game)->size; i++){
        fscanf(file, "%d", &(*game)->board->r_sum[i]);
    }

    //Reading the board columns sum.
    for(int j = 0; j < (*game)->size; j++){
        fscanf(file, "%d", &(*game)->board->c_sum[j]);
    }

    //Initializing playerborad.
    newPlayerBoard((*game)->playerBoard, (*game)->board, (*game)->size);

    int n_keep, n_remove, a, b;

    //Reading the number of marks to keep.
    fscanf(file, "%d", &n_keep);

    //Reading the makrs to keep.
    for(int i = 0; i < n_keep; i++){
        fscanf(file, "%d%d", &a, &b);
        (*game)->playerBoard->marked[a-1][b-1] = 1;
    }

    //Reading the number of marks to remove.
    fscanf(file, "%d", &n_remove);

    //Reading the makrs to remove.
    for(int i = 0; i < n_remove; i++){
        fscanf(file, "%d%d ", &a, &b);
        (*game)->playerBoard->marked[a-1][b-1] = 0;
        (*game)->playerBoard->r_sum[a-1] -= (*game)->board->matrix[a-1][b-1];
        (*game)->playerBoard->c_sum[b-1] -= (*game)->board->matrix[a-1][b-1];
    }

    //Reading the player name
    fgets((*game)->player.name, MAX_NAME_SIZE, file);
    removeBLChar((*game)->player.name);

    //Reading the game time.
    fscanf(file, "%ld", &(*game)->starting_time);

    //Checking the game difficult (because it is not allowed to store it).
    //provisory setting difficult to easy
    (*game)->difficult = 'F';

    fclose(file);
    return true;
}


void solveGame(){
    
}


//Prints-out the game time.
void printGameTime(long int game_time_secs){
    Time time = convertTime(game_time_secs);
    printf(BOLD(BLUE("\n\tTempo de jogo: ")));
    printTime(time);
    printf("\n");
}

//Finalize the game with an final print victory.
void finalizeGame(Game* game){
    finalizeBoard(game->playerBoard, game->size);
    newInterface();
    printGameHeader(game);
    printBoard(game->board, game->size, game->playerBoard);
    freeze(1);
    printGameTime(game->game_time);
    printf(BOLD(GREEN("\n\t\t\tVITÓRIA!!!\n")));
    fflush(stdout);
    freeze(1);
}

//The core function where the game is executed.
void sumplete(Game* game){
    bool victory = false;
    game->playing = true;
    game->game_time = time(NULL);

    //Game main loop.
    while(game->playing){
        sumpleteInterface(game);
        readCommand(game);

        if(verifyVictory(game)){
            victory = true;
            game->playing = false;
        }
    }

    game->game_time = time(NULL) - game->game_time + game->starting_time;
    
    char enter;
    int rank_position;
    if(victory){
        finalizeGame(game);
        
        Ranking* ranking = createRanking();
        readRanking(ranking);
        game->player.time = game->game_time;
        rank_position = verifyRanking(ranking, game->size, game->player);
        writeRanking("sumplete.ini", ranking);
        if(rank_position){
            printf(BOLD(GREEN("\n\tVOCÊ ESTÁ NA POSIÇÃO ")) BOLD(YELLOW("#%d")) BOLD(GREEN(" DO RANKING!\n")), rank_position);
        }

        printf(CYAN("\n\tPrescione ENTER para voltar ao menu."));
        scanf("%c", &enter);
    }
}
