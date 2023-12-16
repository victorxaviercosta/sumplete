#include "commands.h"

//Reads and interprets the main menu input.
//Also defines the flux of the aplication depending on the user descisions.
void mainMenuInput(){
    bool error = false;
    int op;
    Game* game;

    do{
        if(error){
            gotoxy(16, 0);
            printError(INVALID_OPTION_ERROR);
        } else{
            printf("\n");
        }
        
        gotoxy(18, 0); clearLine;
        printf(CYAN("\tEscolha uma opção: "));
        gotoxy(18, 28);
        scanf("%d", &op);
        bufferClear();

        error = false;
        switch(op){
            case 0:
                break;

            case 1:
                game = newGame();
                sumplete(game);
                endGame(&game);
                break;

            case 2:
                if(loadGame(game)){
                    sumplete(game);
                    endGame(&game);
                }
                break;

            case 3:

                break;

            case 4:
                //showRanking();
                break;

            default:
                error = true;
        }
        
    } while(error);
}

//Reads the player name.
void readName(char* name){
    printf(CYAN("\n\tDigite o nome do jogador: "));
    fgets(name, MAX_NAME_SIZE, stdin);
    removeBLChar(name);
    printf("\n");
}

//Reads the board size.
void readBoardSize(int* size){
    bool error = false;

    do{
        if(error){
            gotoxy(12, 0);
            printError(INVALID_SIZE_ERROR);

        } else{
            printf("\n");
        }
        gotoxy(14, 0); clearLine;
        gotoxy(13, 0);
        printf(CYAN("\n\tDigite o tamanho do tabuleiro(3 a 9): "));
        scanf("%d", size);
        bufferClear();
        printf("\n");

        gotoxy(13, 0); clearLine;
        error = false;
        if(*size < 3 || *size > 9){
            error = true;
        }
    } while(error);
}

//Difficult selection Interface.
void chooseDifficult(char* difficult, int* boardSize){
    bool error = false;
    if((*boardSize) < 5){
        printf(CYAN("\n\tDificuldade: ") "F\n");
        *difficult = 'F';

    } else if((*boardSize) < 7){
        printDifficultInterface('M');
        do{
            if(error){
                gotoxy(19, 0);
                printError(INVALID_DIFFICULT_ERROR);
            } else{
                printf("\n");
            }
            gotoxy(21, 0); clearLine;
            gotoxy(20, 0);
            printf(CYAN("\n\tDificuldade: "));
            scanf("%c", difficult);
            bufferClear();

            gotoxy(20, 0); clearLine;
            gotoxy(22, 0);
            error = false;
            if(*difficult != 'F' && *difficult != 'M'){
                error = true;
            }
        }while(error);

    } else if((*boardSize) < 10){
        printDifficultInterface('D');
        do{
            if(error){
                gotoxy(20, 0);
                printError(INVALID_DIFFICULT_ERROR);
            } else{
                printf("\n");
            }
            gotoxy(22, 0); clearLine;
            gotoxy(21, 0);
            printf(CYAN("\n\tDificuldade: "));
            scanf("%c", difficult);
            bufferClear();

            gotoxy(21, 0); clearLine;
            gotoxy(23, 0);
            error = false;
            if(*difficult != 'F' && *difficult != 'M' && *difficult != 'D')
                error = true;
        }while(error);
    }
}



/*========================================
            IN-GAME COMMANDS
==========================================*/

void validateFileName(char* file_name, bool* error){
    int tam = strlen(file_name);
    char file_extention[4];
    file_extention[0] = file_name[tam - 4];
    file_extention[1] = file_name[tam - 3];
    file_extention[2] = file_name[tam - 2];
    file_extention[3] = file_name[tam - 1];

    if(strcmp(file_extention, ".txt"))
        *error = true;
}



void command_keep(Game* game, bool* error){
    int indexes;
    scanf("%d", &indexes);
    bufferClear();
    int i = (indexes/10) - 1, j = (indexes%10) - 1;

    if(i < 0 || i >= game->size || j < 0 || j >= game->size){
        *error = true;

    }else if(game->playerBoard->marked[i][j] != 1){
        if(game->playerBoard->marked[i][j] == 0){
            game->playerBoard->r_sum[i] += game->board->matrix[i][j];
            game->playerBoard->c_sum[j] += game->board->matrix[i][j];
        }

        game->playerBoard->marked[i][j] = 1;
    }
}

void command_remove(Game* game, bool* error){
    int indexes;
    scanf("%d", &indexes);
    bufferClear();
    int i = (indexes/10) - 1, j = (indexes%10) - 1;

    if(i < 0 || i >= game->size || j < 0 || j >= game->size){
        *error = true;

    }else if(game->playerBoard->marked[i][j] != 0){
        game->playerBoard->r_sum[i] -= game->board->matrix[i][j];
        game->playerBoard->c_sum[j] -= game->board->matrix[i][j];

        game->playerBoard->marked[i][j] = 0;
    }
}

void command_hint(Game* game){

}

void command_solve(Game* game){

}

void command_save(Game* game, bool* error){
    char file_name[MAX_NAME_SIZE];
    scanf("%s", file_name);
    bufferClear();
    validateFileName(file_name, error);
    if(*error){
        return;
    }

    //Writing a game file.
    FILE *file = fopen(file_name, "w");
    if(file == NULL){
        *error = true;
        return;
    }
    printf("Oi\n");
    fflush(stdout);
    freeze(2);

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
    fprintf(file, "%ld", game->game_time);

    fclose(file);
}

void command_back(Game* game){

}

//Reads and interprets the in-game player command.
void readCommand(Game* game){
    bool error = false;
    int position = 11 + (2 * game->size) + 5;
    char* command = (char*) malloc(MAX_COMMAND_SIZE * sizeof(char));
    do{
        error = false;
        gotoxy(position-1, 0); clearLine;
        gotoxy(position, 0); clearLine;
        printf(CYAN("\n\t%s, digite o comando: "), game->player.name);
        scanf("%s", command);

        if(!strcmp(command, "manter")){
            command_keep(game, &error);
            if(error){
                gotoxy(position-1, 0);
                printError(INVALID_INDEXES_ERROR);
            }

        }else if(!strcmp(command, "remover")){
            command_remove(game, &error);
            if(error){
                gotoxy(position-1, 0);
                printError(INVALID_INDEXES_ERROR);
            }

        }else if(!strcmp(command, "dica")){
            command_hint(game);

        }else if(!strcmp(command, "resolver")){
            command_solve(game);

        }else if(!strcmp(command, "salvar")){
            command_save(game, &error);
            if(error){
                gotoxy(position-1, 0);
                printError(INVALID_FILE_EXTENTION_ERROR);
                freeze(2);
            } else{
                gotoxy(position-1, 0);
                printSuccess(FILE_SUCCESSFULLY_SAVED);
                freeze(2);
            }

        }else if(!strcmp(command, "voltar")){
            command_back(game);

        }else{
            error = true;
            gotoxy(position-1, 0);
            printError(INVALID_COMMAND_ERROR);
        }
    } while(error);

    free(command);
}

//Reads a file name.
void readFileName(char* file_name, bool* error){
    *error = false;
    printf(CYAN("\n\tDigite o nome do arquivo: "));
    scanf("%s", file_name);
    bufferClear();
    validateFileName(file_name, error);
    if(*error){
        printError(INVALID_FILE_EXTENTION_ERROR);
    }
}