//Victor Xavier Costa - 23.1.4003

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Removes the '\n' char form the given string
void removeBLChar(char* string);

//Function for clear the buffer entrys until a '\n' is found
void bufferClear();

//Allocates memory for an int matrix.
int** createMatrix(int row, int col);

//Frees the allocated memory for a int matrix.
void deleteMatrix(int*** matrix, int row);

#endif //TOOLS_H