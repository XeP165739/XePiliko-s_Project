#include <iostream>

int board[8][8] = {0};

bool isValid(int row, int col){
    for(int i = 0; i < 8; i++){ // rook move
        if(board[i][col] != 0 || board[row][i] != 0) return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--){
        if(board[i][j] != 0) return false;
    }

    for (int i = row, j = col; i >= 0 && j < 8; i--, j++){
        if(board[i][j] != 0) return false;
    }

    return true;
}

bool solve(int row){
    if(row >= 8) return true;

    for(int i = 0; i < 8; i++){
        if(isValid(row, i)){
            board[row][i] = 1;

            if(solve(row + 1)) return true;

            board[row][i] = 0;
        }
    }

    return false;
}

void view(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << ((board[i][j] == 1) ? "Q" : "_") << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    if(solve(0)){
        view();
    } else {
        std::cout << "Not Solved" << std::endl;
    }
    return 0;
}