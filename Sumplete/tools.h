    //Victor Xavier Costa - 23.1.4003

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))
#define reportCursorPosition printf("\033[6n")
#define saveCursorPosition printf("\0337")
#define gotoCursorPosition printf("\0338")
#define clearLine printf("\033[2K")

typedef struct{
    int h;
    int min;
    int sec;
} Time;

/*void getxy(int* x, int* y){
    reportCursorPosition;
    scanf("%d%d", x, y);
}*/

//Removes the '\n' char form the given string
void removeBLChar(char* string);

//Function for clear the buffer entrys until a '\n' is found
void bufferClear();

//Allocates memory for an int matrix.
int** createMatrix(int row, int col);

//Frees the allocated memory for a int matrix.
void deleteMatrix(int*** matrix, int row);

//Initialize an int matrix with the given value.
void initializeMatrix(int** matrix, int row, int col, int value);

//Compare two given matrices with the same dimantions
//Returns false if they are different and true if they are the same 
bool compareMatrices(int** matrix1, int** matrix2, int row, int col);

//Prints-out an int matrix.
void printMatrix(int** matrix, int row, int col);

//Allocates memory for an int array.
int* createArray(int size);

//Frees the allocated memory for a int array.
void deleteArray(int** array);

//Initializes an array with zero.
void initialzeArray(int* array, int size);

//Copy from source array to reciver.
void copyArray(int* reciver, int* source, int size);

//Compare two given arrays with the same dimantions
//Returns false if they are different and true if they are the same  
bool compareArrays(int* array1, int* array2, int size);

//Converts a time in seconds into a hour/mins/sec time.
Time convertTime(long s_time);

//Prints-out a hour/mins/sec time.
void printTime(Time time);

#endif //TOOLS_H