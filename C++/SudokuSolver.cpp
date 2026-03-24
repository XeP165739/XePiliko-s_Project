#include <iostream>
#include <string>

int board[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

bool isValid(int row, int col, int num){
    for(int i = 0; i < 9; i++){ // chekcing the row and col
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    int c = col % 3, r = row % 3;

    for (int i = 0; i < 3 ; i++){ //checking the box
        for (int j = 0; j < 3; j++){
            if (board[row - r + i][col - c + j] == num) {
                return false;
            }
        }
    } 

    return true;
}

bool solve(){
    for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++){
        if(board[i][j] == 0){
            for(int k = 1; k <= 9; k++){
                if(isValid(i,j,k)){
                    board[i][j] = k;
                
                    if(solve()) return true;

                    board[i][j] = 0;
                }
            }
            return false;
        }
    }

    return true;
}

int main(){    
    if(solve()){
        std::cout << "Solved" << std::endl;
    } else {
        std::cout << "Not Solved" << std::endl;
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}