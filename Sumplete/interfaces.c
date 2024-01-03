//Victor Xavier Costa - 23.1.4003

#include "interfaces.h"

//Function for setting up a new Interface of the game
void newInterface(){
    gotoxy(0,0);
    system("clear");
    printf("\n\n\n");
}

//Prints-out the sumplete logo.
void printLogo(){
    printf("\n");
    printf(BOLD(YELLOW("\t\t   _____                       _      _       \n")));
	printf(BOLD(YELLOW("\t\t  / ____|                     | |    | |      \n")));
	printf(BOLD(YELLOW("\t\t | (___  _   _ _ __ ___  _ __ | | ___| |_ ___ \n")));
	printf(BOLD(YELLOW("\t\t  \\___ \\| | | | '_ ` _ \\| '_ \\| |/ _ \\ __/ _ \\\n")));
	printf(BOLD(YELLOW("\t\t  ____) | |_| | | | | | | |_) | |  __/ ||  __/\n")));
	printf(BOLD(YELLOW("\t\t |_____/ \\__,_|_| |_| |_| .__/|_|\\___|\\__\\___|\n")));
	printf(BOLD(YELLOW("\t\t                        | |                   \n")));
	printf(BOLD(YELLOW("\t\t                        |_|                   \n")));
    printf("\n");
}

//Prints-out the given string letter by letter.
void printLetterByLetter(char* string){
    int lenght = strlen(string);
    for(int i = 0; i < lenght; i++){
        printf("%c", string[i]);
        fflush(stdout);
        freeze(0.05);
    }
}

//Plays the initial animation.
void initialAnimation(){
    printLetterByLetter(GREEN("\n\t\t\t  Bem vindo ao jogo") BOLD(YELLOW(" SUMPLETE!\n\n")));

	fflush(stdout);
	freeze(1);
}

//Plays the final animation.
void finalAnimation(){
    printLetterByLetter(GREEN("\n\t\t\t  Obrigado por jogar") BOLD(YELLOW(" SUMPLETE!\n\n")));

	fflush(stdout);
	freeze(1);
}

//Function that prints-out the main menu interface.
void mainMenu(){
    newInterface();

    printLogo();

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
}

//Prints-out a game header.
void printGameHeader(Game* game){
    printLogo();

    printf("\t" BOLD(YELLOW(H_TAB_TL)));
    for(int i = 0; i < 63; i++)
        printf(BOLD(YELLOW(H_TAB_HOR)));
    printf(BOLD(YELLOW(H_TAB_TR)) "\n");

    printf("\t" BOLD(YELLOW(H_TAB_VER)) "\t\t\t\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER)) "\n");
    printf("\t" BOLD(YELLOW(H_TAB_VER)) BOLD(CYAN("  Nome: ")) "%-20s", game->player.name);
    if(game->size)
        printf(BOLD(CYAN(" Tamanho: ")) "%-3d",  game->size);
    else
        printf(BOLD(CYAN(" Tamanho: ")) "   ");
    printf(BOLD(CYAN(" Dificuldade: ")) "%c\t" BOLD(YELLOW(H_TAB_VER)) "\n", game->difficult);
    printf("\t" BOLD(YELLOW(H_TAB_VER)) "\t\t\t\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER)) "\n");

    printf("\t" BOLD(YELLOW(H_TAB_BL)));
    for(int i = 0; i < 63; i++)
        printf(BOLD(YELLOW(H_TAB_HOR)));
    printf(BOLD(YELLOW(H_TAB_BR) "\n\n"));
}

//Prints-out the difficult selection Interface.
void printDifficultInterface(char difficult_levels){
    printf(CYAN("\n\tEscolha uma dificuldade: "));
    printf(BOLD(YELLOW("  \"F\" - ")) "Fácil \n");
	printf("\t\t\t\t" BOLD(YELLOW("   \"M\" - ")) "Médio \n");
    if(difficult_levels == 'D')
        printf("\t\t\t\t" BOLD(YELLOW("   \"D\" - ")) "Difícil\n");
    printf("\n");
}

//Create new game interface.
void createNewGameInterface(Game* game){
    newInterface();
    printGameHeader(game);

    readName(game->player.name);
    gotoxy(4, 0);
    printGameHeader(game);
    gotoxy(13, 0);

    readBoardSize(&game->size);
    gotoxy(4, 0);
    printGameHeader(game);
    gotoxy(26, 0);

    chooseDifficult(&game->difficult, &game->size);
    gotoxy(4, 0);
    printGameHeader(game);
    gotoxy(23, 0);
}

//Prints-out the sumplete game interface.
void sumpleteInterface(Game* game){
    newInterface();
    gotoxy(4, 0);
    printGameHeader(game);

    printBoard(game->board, game->size, game->playerBoard);
}