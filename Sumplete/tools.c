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



/*========================================
            MATRIX MANIPULATION
==========================================*/

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
        (*matrix)[i] = NULL;
    }
    free(*matrix);
    *matrix = NULL;
}

//Initialize an int matrix with the given value.
void initializeMatrix(int** matrix, int row, int col, int value){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = value;
        }
    }
}

//Compare two given matrices with the same dimantions
//Returns false if they are different and true if they are the same 
bool compareMatrices(int** matrix1, int** matrix2, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(matrix1[i][j] != matrix2[i][j])
                return false;
        }
    }
    return true;
}

//Prints-out an int matrix.
void printMatrix(int** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



/*========================================
            ARRAY MANIPULATION
==========================================*/

//Allocates memory for an int array.
int* createArray(int size){
    int* array = (int*) malloc(size * sizeof(int));
    return array;
}

//Frees the allocated memory for a int array.
void deleteArray(int** array){
    free(*array);
    *array = NULL;
}

//Initializes an array with zero.
void initialzeArray(int* array, int size){
    for(int i = 0; i  < size; i++){
        array[i] = 0;
    }
}

//Copy from source array to reciver.
void copyArray(int* reciver, int* source, int size){
    for(int i = 0; i < size; i++){
        reciver[i] = source[i];
    }
}

//Compare two given arrays with the same dimantions
//Returns false if they are different and true if they are the same  
bool compareArrays(int* array1, int* array2, int size){
    for(int i = 0; i < size; i++){
        if(array1[i] != array2[i])
            return false;
    }
    return true;
}



/*========================================
            TIME MANIPULATION
==========================================*/

//Converts a time in seconds into a hour/mins/sec time.
Time convertTime(long s_time){
    Time time;
    time.h = s_time / 3600;
    time.min = (s_time % 3600) / 60;
    time.sec = (s_time % 3600) % 60;
    return time;
}

//Prints-out a hour/mins/sec time.
void printTime(Time time){
    printf("%02d:%02d:%02d", time.h, time.min, time.sec);
}