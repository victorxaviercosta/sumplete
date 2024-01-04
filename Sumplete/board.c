//Victor Xavier Costa - 23.1.4003

#include "board.h"

//Allocates memory for a new sumplete board.
Board* createNewBoard(int size){
    Board* newBoard= (Board*) malloc(sizeof(Board));
    newBoard->matrix = createMatrix(size, size);
    newBoard->r_sum = createArray(size);
    newBoard->c_sum = createArray(size);
    newBoard->marked = createMatrix(size, size);
    return newBoard;
}

//Frees the allocated memory for a board.
void deleteBoard(Board** board, int size){
    deleteArray(&(*board)->c_sum);
    deleteArray(&(*board)->r_sum);
    deleteMatrix(&(*board)->matrix, size);
    deleteMatrix(&(*board)->marked, size);
    free(*board);
    *board = NULL;
}

//Creates a new sumplete board.
void newBoard(Board* board, int size, char difficult){
    srand(time(NULL));
    initialzeArray(board->c_sum, size);
    initialzeArray(board->r_sum, size);


    //Filling the board matrix with random values.
    if(difficult == 'F' || difficult == 'M'){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board->matrix[i][j] = (rand() % 9 + 1);
            }
        }

    }else if(difficult == 'D'){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board->matrix[i][j] = (rand() % 18 + 1) - 9;
            }
        }
    
    }else{
        printError(INVALID_DIFFICULT_ERROR);
        printError(BOARD_CREATION_FAIL);
        return;
    }


    //Selecting the elements to be part of the solution.
    int max_marks = (size * size) - 1, marks = 0;
    switch(difficult){
        //Easy difficult.
        case 'F':
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    board->marked[i][j] = rand() % 2;
                    if(board->marked[i][j]){
                        board->r_sum[i] += board->matrix[i][j];
                        board->c_sum[j] += board->matrix[i][j];
                    }
                }
            }
            break;

        //Medium difficult
        case 'M':
            do{
                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        if(marks < max_marks){
                            board->marked[i][j] = rand() % 2;
                            if(board->marked[i][j]){
                                board->r_sum[i] += board->matrix[i][j];
                                board->c_sum[j] += board->matrix[i][j];
                                marks++;
                            }
                        } else{
                            board->marked[i][j] = 0;
                        }
                    }
                }
            } while(!marks);
            break;

        //Hard difficult.
        case 'D':
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    if(marks < max_marks){
                        board->marked[i][j] = rand() % 2;
                        if(board->marked[i][j]){
                            board->r_sum[i] += board->matrix[i][j];
                            board->c_sum[j] += board->matrix[i][j];
                            marks++;
                        }
                    } else{
                        board->marked[i][j] = 0;
                    }
                }
            }
            break;
    }
}

//Creates a new sumplete player board.
void newPlayerBoard(Board* playerBoard, Board* gameBoard, int size){
    initializeMatrix(playerBoard->marked, size, size, -1);
    initialzeArray(playerBoard->c_sum, size);
    initialzeArray(playerBoard->r_sum, size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            playerBoard->r_sum[i] += gameBoard->matrix[i][j];
            playerBoard->c_sum[j] += gameBoard->matrix[i][j];
        }
    }

}

//A function to be called at the end for the game to mark all the unmarked cells of the player marked board.
void finalizeBoard(Board* playerBoard, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(playerBoard->marked[i][j] == -1)
                playerBoard->marked[i][j] = 1;
        }
    }
}

//Counts the number of "keeps" and removes from the current game.
void countKeepsAndRemoves(Board* playerBoard, int size, int* n_keep, int* n_remove){
    *n_keep = 0; *n_remove = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(playerBoard->marked[i][j] == 1)
                (*n_keep)++;
            if(playerBoard->marked[i][j] == 0)
                (*n_remove)++;
        }
    }
}

//Prints-out the game board.
void printBoard(Board* board, int size, Board* playerBoard){
	//Printing the columns indexes.
	printf("\t     " H_TAB_TL);
	for(int i = 0; i < size - 1; i++){
		printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TJ);
	}
	printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TR "\n");

	printf("\t     " H_TAB_VER);
	for(int i = 0; i < size; i++){
		printf(BOLD(YELLOW(" %3d ")), i+1);
		if(i < (size - 1))
			printf(H_TAB_VER);
	}
	printf(H_TAB_VER"\n");

	printf("\t" H_TAB_TL H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MJ);
	for(int i = 0; i < size; i++){
		if(i < (size - 1))
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BJ);
		else
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR);
	}
	printf(H_TAB_MJ H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TR);
	printf("\n");
	
    //Printing the rows indexes, the matrix and the rows sum.
	for(int i = 0; i < size; i++){
		//Rows indexes.
		printf("\t" H_TAB_VER BOLD(YELLOW("%3d ")) H_TAB_VER, i+1);

		//Board matrix.
		for(int j = 0; j < size; j++){
            if(playerBoard->marked[i][j] == 1)
			    printf(BOLD(GREEN(" %3d ")), board->matrix[i][j]);
            else if(playerBoard->marked[i][j] == 0)
                printf(BOLD(RED(" %3d ")), board->matrix[i][j]);
            else
                printf(" %3d ", board->matrix[i][j]);

			if(j < (size - 1))
				printf(TAB_VER);
		}

		//Rows sum.
		printf(H_TAB_VER);
        if(playerBoard->r_sum[i] == board->r_sum[i])
            printf(BOLD(CYAN("%3d ")), board->r_sum[i]);
        else
            printf(CYAN("%3d "), board->r_sum[i]);
		printf(H_TAB_VER "\n");

		if(i < (size - 1))
			printf("\t" H_TAB_ML H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MR);

		for(int j = 0; j < size; j++){
			if(i < (size - 1)){
				printf(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR);
				if(j < (size - 1))
					printf(TAB_MJ);
			}
		}
		
		if(i < (size - 1)){
			printf(H_TAB_ML H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MR);
			printf("\n");
		}
	}

	printf("\t" H_TAB_BL H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_MJ);
	for(int i = 0; i < size; i++){
		if(i < (size - 1))
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_TJ);
		else
			printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR);
	}
	printf(H_TAB_MJ H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BR);
	
	//Printing the columns sum.
	printf("\n\t     " H_TAB_VER);
	for(int i = 0; i < size; i++){
        if(playerBoard->c_sum[i] == board->c_sum[i])
            printf(BOLD(CYAN(" %3d ")), board->c_sum[i]);
        else
		    printf(CYAN(" %3d "), board->c_sum[i]);
		if(i < (size - 1))
			printf(H_TAB_VER);
	}
	printf(H_TAB_VER "\n");

	printf("\t     " H_TAB_BL);
	for(int i = 0; i < size - 1; i++){
		printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BJ);
	}
	printf(H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_HOR H_TAB_BR);
	printf("\n\n");
}