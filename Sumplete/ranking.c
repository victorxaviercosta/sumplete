#include "ranking.h"

//Allocates and initializes memmory for a Ranking structure.
Ranking* createRanking(){
    Ranking* ranking = (Ranking*) malloc(sizeof(Ranking));
    ranking->n_sizes = 0;
    initialzeArray(ranking->sizes, MAX_SIZES);
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
    int size;

    FILE* file = fopen("sumplete.ini", "a");
    fclose(file);

    file = fopen("sumplete.ini", "r");

    fseek(file, 0, SEEK_END);
    int tam = ftell(file);
    fseek(file, 0, SEEK_SET);

    while(tam > 0 && !feof(file)){
        fscanf(file, "%s", string);
        fscanf(file, "%s", aux);

        //Reading the board size.
        if(!strcmp(string, "size")){
            fscanf(file, "%d", &size);
            ranking->sizes[size - 3] = size;
            ranking->n_sizes++;
            
            fscanf(file, "%s", string);
            fscanf(file, "%s", aux);            

        }

        //Reading the player name.
        fgetc(file);    
        fgets(ranking->players[size-3][ranking->n_players[size-3]].name, MAX_NAME_SIZE, file);
        removeBLChar(ranking->players[size-3][ranking->n_players[size-3]].name);

        fscanf(file, "%s", string);
        fscanf(file, "%s", aux);

        //Reding the player time.
        fscanf(file, "%ld", &ranking->players[size-3][ranking->n_players[size-3]].time);
        ranking->n_players[size-3]++;
    }

    fclose(file);
}

//Writes the ranking information in the .ini file (updating it).
void writeRanking(char* file_name, Ranking* ranking){
    FILE* file = fopen(file_name, "w");

    int cont = 0, cont2 = 0;
    for(int i = 0; i < MAX_SIZES; i++){
        if(ranking->sizes[i]){
            cont++;
            fprintf(file, "size = %d\n", ranking->sizes[i]);
            
            cont2 = 0;
            for(int j = 0; j < ranking->n_players[i]; j++){
                cont2++;
                fprintf(file, "player%d = %s\n", j+1, ranking->players[i][j].name);
                fprintf(file, "time%d = %ld", j+1, ranking->players[i][j].time);
                if(cont < ranking->n_sizes || cont2 < ranking->n_players[i])
                    fprintf(file, "\n");
            }

            if(cont < (ranking->n_sizes))
                fprintf(file, "\n");
        }
    }

    fclose(file);
}

//Verifies if the current player time is able to enter the rank.
//Retruns the rank position or 0 if it isn't albe to enter the rank.
int verifyRanking(Ranking* ranking, int size, Player player){
    int position = 0;
    int pSize = size - 3;

    //Special case: the current size still dosen't exist.
    if(!ranking->sizes[pSize]){
        ranking->sizes[pSize] = size;
        ranking->players[pSize][0] = player;
        ranking->n_players[pSize]++;
        ranking->n_sizes++;
        position = 1;
        return position;
    }

    //Checking for the possibility of entering the rank.
    for(int i = 0; i < ranking->n_players[pSize]; i++){
        if(player.time < ranking->players[pSize][i].time){
            for(int j = ranking->n_players[pSize]; j >= i; j--){
                ranking->players[pSize][j] = ranking->players[pSize][j-1];
            }
            ranking->players[pSize][i] = player;
            if(ranking->n_players[pSize] < MAX_PLAYERS_PER_SIZE)
                ranking->n_players[pSize]++;
            position = i+1;
            return position;
        }
    }

    //If player doesn't beat the current times but there's still space for a new player.
    if(ranking->n_players[pSize] < MAX_PLAYERS_PER_SIZE){
        ranking->players[pSize][ranking->n_players[pSize]] = player;
        ranking->n_players[pSize]++;
        position = ranking->n_players[pSize];
    }
    return position;
}

//Prints-out the current game rank.
void showRanking(){
    Time time;
    Ranking* ranking = createRanking();
    readRanking(ranking);

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

		for(int i = 0; i < MAX_SIZES; i++){
            if(ranking->sizes[i]){
                printf("\t" H_TAB_VER BOLD(CYAN(" Categoria: "))); 
                printf("%dx%d" "\t\t\t\t\t\t" H_TAB_VER "\n",  ranking->sizes[i], ranking->sizes[i]);
                printf("\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");
                for(int j = 0; j < ranking->n_players[i]; j++){
                    time = convertTime(ranking->players[i][j].time);
                    printf("\t" H_TAB_VER BOLD(YELLOW("     #%d")), j+1); 
                    printf(" - ");
                    printf(BOLD(GREEN("%-30s ")), ranking->players[i][j].name);
                    printf(BOLD(BLUE("  Tempo: ")));
                    printf("%02d:%02d:%02d \t" H_TAB_VER "\n", time.h, time.min, time.sec);
                }
                printf("\t" H_TAB_VER "\t\t\t\t\t\t\t\t" H_TAB_VER "\n");
            }
		}

		printf("\t" H_TAB_BL);
		for(int i = 0; i < 63; i++)
			printf(H_TAB_HOR);
		printf(H_TAB_BR "\n\n");

	} else{
		printf(BOLD(YELLOW("\n\tInfelizmente ainda não há jogaodres no Raniking!\n\n")));
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