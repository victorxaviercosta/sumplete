#include "solver.h"

// Function that convert decimal to binary 
void decToBinary(int n, int* binary, int size){ 
    int k;
    for (int i = 0; i < size; i++) { 
        k = n >> i; 
        binary[size - i - 1] = (k & 1); 
    } 
}

void checkRowSum(){

}

void solve(Board* board, int size){
    int binary[size];
    int combinations = pow(2, size);
    int rowSum = 0, columnSum = 0;

    for(int a = 0; a < combinations; a++){
        decToBinary(a, binary, size);

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board->marked[i][j] = binary[j];
                if(binary[j])
                    rowSum += board->matrix[i][j];
            }

            if(rowSum == board->r_sum){
                //stoped here.
            }
        }

        /*
        printf("binary: ");
        for(int k = 0; k < size; k++){
            printf("%d ", binary[k]);
        }
        printf("\n");
        */
    }
}

int main(){
    int size = 5;
    Board* board = createNewBoard(size);
    newBoard(board, size, 'F');
    
    solve(board, size);
    deleteBoard(&board, size);
}