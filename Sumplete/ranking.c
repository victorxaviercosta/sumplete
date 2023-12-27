#include "ranking.h"

//Allocates and initializes memmory for a Ranking structure.
Ranking* createRanking(){
    Ranking* ranking = (Ranking*) malloc(sizeof(Ranking));
    ranking->n_sizes = 0;
    initialzeArray(ranking->n_players, MAX_SIZES);
    return ranking;
}

//Frees memmory for a Ranking structure.
void freeRanking(Ranking** ranking){
    free(*ranking);
    *ranking = NULL;
}

//Reads a .ini file contanning the game ranking information.
void readRanking(Ranking* ranking){
    char string[MAX_NAME_SIZE], aux[5];
    int position;

    FILE* file = fopen("sumplete.ini", "r");
    while(!feof(file)){
        fscanf(file, "%s", string);
        fscanf(file, "%s", aux);

        if(!strcmp(string, "size")){
            fscanf(file, "%d", &ranking->sizes[ranking->n_sizes]);
            ranking->n_sizes++;
            
            fscanf(file, "%s", string);
            fscanf(file, "%s", aux);            

        }

        position = ranking->n_sizes - 1;
        //Reading the player name.
        fgetc(file);    
        fgets(ranking->names[position] [ranking->n_players[position]], MAX_NAME_SIZE, file);
        removeBLChar(ranking->names[position] [ranking->n_players[position]]);

        fscanf(file, "%s", string);
        fscanf(file, "%s", aux);

        //Reding the player time.
        fscanf(file, "%ld", &ranking->times[position][ranking->n_players[position]]);
        ranking->n_players[position]++;
    }

    fclose(file);
}

//Writes the ranking information in the .ini file (updating it).
void writeRanking(char* file_name, Ranking* ranking){
    FILE* file = fopen(file_name, "w");

    for(int i = 0; i < ranking->n_sizes; i++){
        fprintf(file, "size = %d\n", ranking->sizes[i]);
        
        for(int j = 0; j < ranking->n_players[i]; j++){
            fprintf(file, "player%d = %s\n", j+1, ranking->names[i][j]);
            fprintf(file, "time%d = %ld", j+1, ranking->times[i][j]);
            if(i < ranking->n_sizes - 1)
                fprintf(file, "\n");    
        }

        if(i < ranking->n_sizes - 1)
            fprintf(file, "\n");
    }
}

//Verifies if the current player time is able to enter the rank.
bool verifyRanking(Ranking* ranking, int size, long int time){
    for(int i = 0)
}

void showRanking(){
    Time time;
    Ranking* ranking = createRanking();
    readRanking(ranking);

    //newInterface();

	if(ranking->n_sizes > 0){
        printf("\t" H_TAB_TL);
        for(int i = 0; i < 63; i++)
            printf(H_TAB_HOR);
        printf(H_TAB_TR "\n\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");

		printf("\t" H_TAB_VER BOLD(GREEN("\t    RANKING ATUAL DOS JOGADORES DE SUMPLETE\t\t") H_TAB_VER "\n"));
        printf("\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");

		printf("\t" H_TAB_ML);
		for(int i = 0; i < 63; i++)
			printf(H_TAB_HOR);
		printf(H_TAB_MR "\n\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");

		for(int i = 0; i < ranking->n_sizes; i++){
			printf("\t" H_TAB_VER BOLD(CYAN(" Categoria: "))); 
			printf("%dx%d" "\t\t\t\t\t\t" H_TAB_VER "\n",  ranking->sizes[i], ranking->sizes[i]);
            printf("\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");
			for(int j = 0; j < ranking->n_players[i]; j++){
				time = convertTime(ranking->times[i][j]);
				printf("\t" H_TAB_VER BOLD(YELLOW("     #%d")), j+1); 
				printf(" - ");
				printf(BOLD(GREEN("%-30s ")), ranking->names[i][j]);
				printf(BOLD(BLUE("  Tempo: ")));
				printf("%02d:%02d:%02d \t" H_TAB_VER "\n", time.h, time.min, time.sec);
			}
			printf("\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");
		}

		printf("\t" H_TAB_BL);
		for(int i = 0; i < 63; i++)
			printf(H_TAB_HOR);
		printf(H_TAB_BR "\n\n");

	} else{
		printf("\t" BOLD(YELLOW("Infelizmente ainda não há jogaodres no Raniking!\n\n")));
	}

    char enter;
    printf(CYAN("\tPrescione ENTER para voltar ao menu."));
    scanf("%c", &enter);

    freeRanking(&ranking);
}

/*
size = 3
player1 = John Silva
time1 = 12
player2 = Paul Souza
time2 = 34
player3 = Computador
time3 = 55
player4 = Ringo Oliveira
time4 = 56

size = 4
player1 = Astro Jetson
time1 = 3
player2 = Rosie Jetson
time2 = 4

size = 5
player1 = Victor
time1 = 188

size = 6
player1 = Victor
time1 = 165
*/