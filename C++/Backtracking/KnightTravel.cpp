#include <iostream>

const int size = 5;
const int total = size * size;
int board[size][size] = {total};

int horseX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int horseY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int row, int col){
    if(0 > row || row >= size || 0 > col || col >= size) return false;
    if(board[row][col] != 0) return false;

    return true;
}

bool solution(int row, int col, int step){
    if(step <= 0) return true;

    for(int i = 0; i < 8; i++){
        int r = row + horseY[i], c = col + horseX[i];

        if(isSafe(r,c)){
            board[r][c] = step;

            if(solution(r, c, step - 1)) return true;

            board[r][c] = 0;
        }
    }
    
    return false;
}

void view(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    if(solution(0,0,total - 1)){
        view();
    } else {
        std::cout << "Not Solved" << std::endl;
    }
    return 0;
}