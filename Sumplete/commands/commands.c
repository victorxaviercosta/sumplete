#include "commands.h"

/*========================================
            MENU COMMANDS
==========================================*/

//Reads and interprets the main menu input.
//Also defines the flux of the aplication depending on the user descisions.
int mainMenuInput(){
    bool error = false; int id = 0;
    int op = -1;
    char file_name[MAX_NAME_SIZE];
    Game* game;

    do{ 
        gotoxy(28, 0); clearLine;
        printf(CYAN("\tEscolha uma opção: "));
        scanf("%d", &op);
        bufferClear();

        error = false; id = 0;
        gotoxy(27, 0); clearLine;
        gotoxy(29, 0);

        switch(op){
            case 0:
                remove("default_unfinished_game.txt");
                break;

            case 1:
                game = newGame();
                sumplete(game);
                endGame(&game);
                return 1;

            case 2:
                if(readFileName(file_name)){
                    game = createNewGame();
                    if(loadGame(&game, file_name)){
                        sumplete(game);
                        
                    } else{
                        printError(UNABLE_TO_OPEN_FILE_ERROR);
                        freeze(2);
                    }
                    endGame(&game);
                }
                return 1;

            case 3:
                if(loadGame(&game, "default_unfinished_game.txt")){
                    sumplete(game);
                    endGame(&game);
                } else{
                    error = true;
                    id = 1;
                }
                break;

            case 4:
                newInterface();
                printLogo();
                showRanking();
                return 1;
            
            case 5:
                commandsInterface();
                return 1;

            default:
                error = true;
        }
        if(error){
            gotoxy(26, 0);
            if(id == 1)
                printError(NO_CURRENT_GAME_AVALIABLE);
            else
                printError(INVALID_OPTION_ERROR);
        }
        
    } while(error);
    return 0;
}


//Reads a file name.
 bool readFileName(char* file_name){
    bool error = false;
    char yn;
    do{
        error = false;
        newInterface();
        printLogo();
        printf(BOLD(YELLOW("\t\t CARREGAR JOGO SALVO\n\n")));
        
        printf(CYAN("\n\tDigite o nome do arquivo: "));
        scanf("%s", file_name);
        bufferClear();
        validateFileName(file_name, &error);
        if(error){
            printError(INVALID_FILE_EXTENTION_ERROR);
        }

        if(error){
            printf(CYAN("\tDeseja tentar novamente? [s/n]: "));
            scanf("%c", &yn);
            bufferClear();
            if(yn == 'n')
                return false;
        }
    }while(error);
    return true;
}

//Validate a file name (veryfies if it's extention is .txt).
void validateFileName(char* file_name, bool* error){
    int tam; 
    tam = strlen(file_name);

    char file_extention[5];
    file_extention[0] = file_name[tam - 4];
    file_extention[1] = file_name[tam - 3];
    file_extention[2] = file_name[tam - 2];
    file_extention[3] = file_name[tam - 1];
    file_extention[4] = '\0';

    if(strcmp(file_extention, ".txt"))
        *error = true;
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
            gotoxy(22, 0);
            printError(INVALID_SIZE_ERROR);

        } else{
            printf("\n");
        }
        gotoxy(24, 0); clearLine;
        gotoxy(23, 0);
        printf(CYAN("\n\tDigite o tamanho do tabuleiro(3 a 9): "));
        scanf("%d", size);
        bufferClear();
        printf("\n");

        gotoxy(23, 0); clearLine;
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
                gotoxy(29, 0);
                printError(INVALID_DIFFICULT_ERROR);
            } else{
                printf("\n");
            }
            gotoxy(31, 0); clearLine;
            gotoxy(30, 0);
            printf(CYAN("\n\tDificuldade: "));
            scanf("%c", difficult);
            bufferClear();

            gotoxy(30, 0); clearLine;
            gotoxy(32, 0);
            error = false;
            if(*difficult != 'F' && *difficult != 'M'){
                error = true;
            }
        }while(error);

    } else if((*boardSize) < 10){
        printDifficultInterface('D');
        do{
            if(error){
                gotoxy(30, 0);
                printError(INVALID_DIFFICULT_ERROR);
            } else{
                printf("\n");
            }
            gotoxy(32, 0); clearLine;
            gotoxy(31, 0);
            printf(CYAN("\n\tDificuldade: "));
            scanf("%c", difficult);
            bufferClear();

            gotoxy(31, 0); clearLine;
            gotoxy(33, 0);
            error = false;
            if(*difficult != 'F' && *difficult != 'M' && *difficult != 'D')
                error = true;
        }while(error);
    }
}



/*========================================
            IN-GAME COMMANDS
==========================================*/

void command_commands(){
    bufferClear();
    commandsInterface();
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

void command_hint(Game* game, bool* error){
    int nMarks = 0;
    int nMatches = 0;
    int r, c;
    bool ok = false;
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            if(game->board->marked[i][j]){
                nMarks++;
                if(game->playerBoard->marked[i][j] == 1)
                    nMatches++;
            }
        }
    }

    if(nMarks == nMatches){
        *error = true;
        return;
    }else{
        while(!ok){
            r = rand() % game->size;
            c = rand() % game->size;
            if(game->board->marked[r][c] && game->playerBoard->marked[r][c] != 1){
                if(game->playerBoard->marked[r][c] == 0){
                    game->playerBoard->r_sum[r] += game->board->matrix[r][c];
                    game->playerBoard->c_sum[c] += game->board->matrix[r][c];
                }
                game->playerBoard->marked[r][c] = 1;
                ok = true;
            }
        }
    }
}

void command_solve(Game* game){
    initialzeArray(game->playerBoard->r_sum, game->size);
    initialzeArray(game->playerBoard->c_sum, game->size);
    for(int i = 0; i < game->size; i++){
        for(int j = 0; j < game->size; j++){
            game->playerBoard->marked[i][j] = game->board->marked[i][j];
            if(game->playerBoard->marked[i][j]){
                game->playerBoard->r_sum[i] += game->board->matrix[i][j];
                game->playerBoard->c_sum[j] += game->board->matrix[i][j];
            }
        }
    }
    game->playerBoard->matrix[0][0] = 1; //Sinalizes the game was automatically solved.
}

void command_save(Game* game, bool* error, int* id){
    char file_name[MAX_NAME_SIZE];
    scanf("%s", file_name);
    bufferClear();
    validateFileName(file_name, error);
    if(*error){
        *id = 1;
        return;
    }

    if(!saveGame(game, file_name)){
        *error = true;
        *id = 2;
        return;
    }
    game->playerBoard->matrix[0][0] = 2; //Sinalizes the game was saved.
}

void command_back(Game* game){
    saveGame(game, "default_unfinished_game.txt");
    game->playing = false;
}

//Reads and interprets the in-game player command.
void readCommand(Game* game){
    bool error = false;
    int position = 11 + (2 * game->size) + 15;
    int positionP1 = position + 1;
    int positionM1 = position - 1;
    char* command = (char*) malloc(MAX_COMMAND_SIZE * sizeof(char));
    int id;
    do{
        fflush(stdout);
        error = false;
        
        gotoxy(positionP1, 0); clearLine;
        gotoxy(position, 0);
        printf(CYAN("\n\t%s, digite o comando: "), game->player.name);
        scanf("%s", command);

        if(!strcmp(command, "comandos")){
            command_commands();

        }else if(!strcmp(command, "manter")){
            command_keep(game, &error);
            if(error){
                gotoxy(positionM1, 0);
                printError(INVALID_INDEXES_ERROR);
            }

        }else if(!strcmp(command, "remover")){
            command_remove(game, &error);
            if(error){
                gotoxy(positionM1, 0);
                printError(INVALID_INDEXES_ERROR);
            }

        }else if(!strcmp(command, "dica")){
            command_hint(game, &error);
            if(error){
                gotoxy(positionM1, 0);
                printError(NO_MORE_HINTS);
            }

        }else if(!strcmp(command, "resolver")){
            command_solve(game);
            bufferClear();

        }else if(!strcmp(command, "salvar")){
            id = 0;
            command_save(game, &error, &id);
            if(error){
                gotoxy(positionM1, 0);
                if(id == 1)
                    printError(INVALID_FILE_EXTENTION_ERROR);
                else if (id == 2)
                    printError(UNABLE_TO_SAVE_FILE_ERROR);
                freeze(2);
            } else{
                gotoxy(positionM1, 0);
                printSuccess(FILE_SUCCESSFULLY_SAVED);
                freeze(2);
            }

        }else if(!strcmp(command, "voltar")){
            command_back(game);

        }else{
            bufferClear();
            error = true;
            gotoxy(positionM1, 0);
            printError(INVALID_COMMAND_ERROR);
        }
    } while(error);

    free(command);
}