#include "solver.h"

// Function that convert decimal to binary 
void decToBinary(int n, int* binary, int size){ 
    int k;
    for (int i = 0; i < size; i++) { 
        k = n >> i; 
        binary[size - i - 1] = (k & 1); 
    } 
}

/*
3 4 5 |  0
2 3 4 |  2
2 9 3 | 11
----------
4 9 0 |

0 0 0 -> 2^size
1 0 0 -> 2^(size-1)
1 1 0 -> 2^(size-2)
| | |
| | -> 2^(size-3)
| -> 2^(size-2)
-> 2^(size-1)

2^(size - 1) -> 1
2^4 = 16
16/2 = 8

*/

bool checkColumnSum(Board* board, int size, int combinations, int start, int column);
bool checkRowSum(Board* board, int size, int combinations, int start, int row);

//Tests the columns combinations in associon with checkRowSum().
bool checkColumnSum(Board* board, int size, int combinations, int start, int column){
    int binary[size];
    int columnSum = 0;
    
    //printf(BOLD(YELLOW("COLUMN: ")) "%d\n", column);
    for(int a = 0; a < combinations; a++){

        columnSum = 0;
        decToBinary(a, binary, size);

        for(int i = start; i < size; i++){
            board->marked[i][column] = binary[i];
        }

        for(int i = 0; i < size; i++){
            if(board->marked[i][column])
                columnSum += board->matrix[i][column];
        }

        if(columnSum == board->c_sum[column]){
            //printMatrix(board->marked, size, size);

            //Recursion stop condition.
            if(column == size-1)
                return true;

            if(checkRowSum(board, size, combinations, start, column+1))
                return true;                
        }
    }
    return false;
}

//Tests the columns combinations in associon with checkColumnsSum().
bool checkRowSum(Board* board, int size, int combinations, int start, int row){
    //Recursion stop Condition
    if(combinations <= 1)
        return false;
    
    int binary[size];
    int rowSum = 0;
    int next_combinations;
    int next_start = start + 1;
    
    //printf(BOLD(YELLOW("ROW: ")) "%d\n", row);
    for(int a = 0; a < combinations; a++){

        rowSum = 0;
        decToBinary(a, binary, size);

        for(int j = start; j < size; j++){
            board->marked[row][j] = binary[j];
        }

        for(int j = 0; j < size; j++){
            if(board->marked[row][j])
                rowSum += board->matrix[row][j];
        }

        if(rowSum == board->r_sum[row]){
            //printMatrix(board->marked, size, size);

            next_combinations = pow(2, (size - start - 1));
            //printf(BOLD(BLUE("combinations = ")) "%d\n", next_combinations);

            if(checkColumnSum(board, size, next_combinations, next_start, row))
                return true;
        }
    }   
    return false;
}

//Finds a solution for the game.
void solve(Board* board, int size){
    int combinations = pow(2, size);
    checkRowSum(board, size, combinations, 0, 0);
}

//main instance for testing.
/*
int main(){
    printf(BOLD(BLUE("\t==================================\n")));
    printf(BOLD(BLUE("\t SUMPLETE SOLVER VISUAL TESTER\n")));
    printf(BOLD(BLUE("\t==================================\n")));

    int size; char difficult;
    printf(BOLD(RED("\nNOTE:")) "you can select a board size greater than 9 but keep in mind that the amount of tests needed grows exponentially and the execution time tends to be considerably long for boards greater than 9\n");
    do{
        printf(BOLD(MAGENTA("\n\tBoard size: "))); scanf("%d", &size);
    }while(size <= 0);
    bufferClear();
    do{
        printf(BOLD(MAGENTA("\n\tBoard difficult ('F', 'M' or 'D'): "))); scanf("%c", &difficult);
    }while(difficult != 'F' && difficult != 'M' && difficult != 'D');

    Board* board = createNewBoard(size);
    newBoard(board, size, difficult);
    Board* playerBoard = createNewBoard(size);
    newPlayerBoard(playerBoard, board, size);

    printf(BOLD(BLUE("\nBoard: \n")));
    printBoard(board, size, playerBoard);

    int** prescribed = createMatrix(size, size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            prescribed[i][j] = board->marked[i][j];
        }
    }

    printf(BOLD(BLUE("\nprescribed solution: \n")));
    printMatrix(prescribed, size, size);
    printf("\n");
    
    initializeMatrix(board->marked, size, size, 0);

    printf(GREEN("STARTING TO SOLVE\n"));
    printf("======================================================\n\n");
    solve(board, size);
    printf("======================================================\n");
    printf(GREEN("FINISHED\n"));

    printf(BOLD(BLUE("\nprescribed solution: \n")));
    printMatrix(prescribed, size, size);

    printf(BOLD(BLUE("found solution: \n")));
    printMatrix(board->marked, size, size);

    if(compareMatrices(prescribed, board->marked, size, size)){
        printf(BOLD(GREEN("SAME SOLUTION\n")));
    } else{
        printf(BOLD(RED("DIFFERENT SOLUTION\n")));
    }


    initialzeArray(playerBoard->r_sum, size);
    initialzeArray(playerBoard->c_sum, size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            playerBoard->marked[i][j] = board->marked[i][j];
            if(playerBoard->marked[i][j]){
                playerBoard->r_sum[i] += board->matrix[i][j];
                playerBoard->c_sum[j] += board->matrix[i][j];
            }
        }
    }

    printf(BOLD(BLUE("\nFound solution applied to the board: \n")));
    printBoard(board, size, playerBoard);

    bool rowSum = compareArrays(board->r_sum, playerBoard->r_sum, size);
    bool colSum = compareArrays(board->c_sum, playerBoard->c_sum, size);
    if(rowSum && colSum)
        printf(BOLD(GREEN("CORRECT\n\n")));
    else
        printf(BOLD(RED("WRONG\n\n")));

    deleteMatrix(&prescribed, size);
    deleteBoard(&playerBoard, size);
    deleteBoard(&board, size);
}
*/