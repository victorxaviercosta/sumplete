#include "ranking.h"
#include "formats.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

void readRanking(int* sizes, char** names, int* times){
    int i = 0;
    char string[MAX_NAME_SIZE], aux[5];

    FILE* file = fopen("sumplete.ini", "w");
    while(!feof(file)){
        fscanf(file, "%s", string);
        fscanf(file, aux);

        if(!strcmp(string, "size")){
            fscanf("%d", sizes[i]);
        }
    }
}

void showRanking(){
    int sizes[7];
    char names[35][MAX_NAME_SIZE];
    long int times[35];
    readRanking(&sizes, &names, &times);
}