
//Prints-out the difficult selection Interface.
void printDifficultInterface(char difficult_levels){
    printf("\t" BOLD(YELLOW(H_TAB_TL)));
    for(int i = 0; i < 39; i++)
        printf(BOLD(YELLOW(H_TAB_HOR)));
    printf(BOLD(YELLOW(H_TAB_TR)));

    printf("\n\t" BOLD(YELLOW(H_TAB_VER)) "\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER)) "\n");
    printf("\t" BOLD(YELLOW(H_TAB_VER)) CYAN("  Escolha uma dificuldade: \t\t" BOLD(YELLOW(H_TAB_VER))"\n"));
    printf("\t" BOLD(YELLOW(H_TAB_VER)) "\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER))"\n");
    printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t\"F\" - ")) "Fácil  \t\t" BOLD(YELLOW(H_TAB_VER "\n")));
	printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t\"M\" - ")) "Médio  \t\t" BOLD(YELLOW(H_TAB_VER "\n")));
    if(difficult_levels == 'D')
        printf("\t" BOLD(YELLOW(H_TAB_VER "\t\t\"D\" - ")) "Difícil  \t\t" BOLD(YELLOW(H_TAB_VER "\n")));
    printf("\t" BOLD(YELLOW(H_TAB_VER)) "\t\t\t\t\t" BOLD(YELLOW(H_TAB_VER))"\n");

    printf("\t" BOLD(YELLOW(H_TAB_BL)));
    for(int i = 0; i < 39; i++)
        printf(BOLD(YELLOW(H_TAB_HOR)));    
    printf(BOLD(YELLOW(H_TAB_BR)) "\n\n");
}