//Victor Xavier Costa - 23.1.4003

#include "sumpletelib.h"

//Prints-out the specified error message.
void printError(char* error_name){
    printf(BOLD(RED("\n\t\t\t\t %s\n\n")), error_name);
}

//Function for setting up a new Interface of the game
void newInterface(){
    system("clear");
    printf("\n\n\n");
}

//Allocates memory for a new game.
Game* createNewGame(){
    Game* newGame = (Game*) malloc(sizeof(Game));
    return newGame;
}

//Frees the allocated memory for a game.
void deleteGame(Game** game){
    free(*game);
    *game = NULL;
}

//Function that prints-out the main menu interface.
void mainMenu(){
    
    printf("\n\t" BOLD(YELLOW(H_TAB_TL)));
    for(int i = 0; i < 63; i++){
        printf(BOLD(YELLOW(H_TAB_HOR)));
    }
    printf(BOLD(YELLOW(H_TAB_TR))"\n");
    printf("\t" BOLD(YELLOW(H_TAB_VER))"\t\t\t\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER))"\n");

    printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t0 - ")) "Sair do jogo             \t\t\t" BOLD(YELLOW(H_TAB_VER "\n")));
	printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t1 - ")) "Começar novo jogo        \t\t\t" BOLD(YELLOW(H_TAB_VER "\n")));
	printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t2 - ")) "Continuar um jogo salvo  \t\t\t" BOLD(YELLOW(H_TAB_VER "\n")));
	printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t3 - ")) "Continuar o jogo atual   \t\t\t" BOLD(YELLOW(H_TAB_VER "\n"))); 
	printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t4 - ")) "Exibir ranking           \t\t\t" BOLD(YELLOW(H_TAB_VER "\n")));
    printf("\t" BOLD(YELLOW(H_TAB_VER))"\t\t\t\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER))"\n");
	printf("\t" BOLD(YELLOW(H_TAB_VER)) "     Durante o jogo, digite \"" GREEN("voltar") "\" para retornar ao menu.\t" BOLD(YELLOW(H_TAB_VER)) "\n");

    printf("\t" BOLD(YELLOW(H_TAB_VER))"\t\t\t\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER))"\n");
    printf("\t" BOLD(YELLOW(H_TAB_BL)));
    for(int i = 0; i < 63; i++){
        printf(BOLD(YELLOW(H_TAB_HOR)));
    }
    printf(BOLD(YELLOW(H_TAB_BR))"\n\n");

    readComand('M');
}


//Reads the input command based on the interface from where it's called.
void readComand(char interface){
    bool error;
    int op;
    char commad[MAX_COMMAND_SIZE];
    switch(interface){
        case 'M':
            do{
                error = false;
                printf(CYAN("\tEscolha uma opção: "));
                scanf("%d", &op);
                bufferClear();

                switch(op){
                    case 0:
                        return;

                    case 1:
                        newGame();
                        break;

                    case 2:
                        //loadGame();
                        break;

                    case 3:

                        break;

                    case 4:
                        //showRanking();
                        break;

                    default:
                        error = true;
                        printError(INVALID_OPTION_ERROR);
                }
            }while(error);
            break;

        default:
            return;
    }

    if(!strcmp(commad, "voltar")){
        mainMenu();
    }
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
    bool error;
    do{
        error = false;
        printf(CYAN("\n\tDigite o tamanho do tabuleiro(3 a 9): "));
        scanf("%d", size);
        bufferClear();
        printf("\n");
        if(*size < 3 || *size > 9){
            error = true;
            printError(INVALID_SIZE_ERROR);
        }
    } while(error);
}

//Create new game interface.
void newGame(){
    Game* game = createNewGame();
    
    newInterface();
    readName(game->player.name);
    readBoardSize(&game->size);
    
}

//The core function where the game is executed.
void sumplete(){

}
