//Victor Xavier Costa - 23.1.4003

#include "tools.h"

//Removes the '\n' char form the given string
void removeBLChar(char* string){
    string[strlen(string) - 1] = '\0';
}

//Function for clear the buffer entrys until a '\n' is found
void bufferClear(){
    while(getchar() != '\n');
}

//Allocates memory for an int matrix.
int** createMatrix(int row, int col){
    int** matrix = (int**) malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++){
        matrix[i] = (int*) malloc(col * sizeof(int));
    }
    return matrix;
}

//Frees the allocated memory for a int matrix.
void deleteMatrix(int*** matrix, int row){
    for(int i = 0; i < row; i++){
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}
