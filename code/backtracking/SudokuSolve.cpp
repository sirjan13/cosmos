#include<iostream>
using namespace std;

/*
 * Part of Cosmos by OpenGenus Foundation
*/

int n = 9;

bool isPossible(int mat[][9], int curr_row, int curr_col, int num){
    ///Row or col should not have number
    for(int x=0; x < n; x++){
        if(mat[x][curr_row] == num || mat[curr_col][x] == num){
            return false;
        }
    }

    /// Subgrid should not have number
    int first_row_subgrid = (curr_row/3)*3;
    int first_col_subgrid = (curr_col/3)*3;

    for(int x=first_row_subgrid; x < first_row_subgrid + 3; x++){
        for(int y=first_col_subgrid; y < first_col_subgrid + 3; y++){
            if(mat[x][y] == num){
                return false;
            }
        }
    }

    return true;
}

void printMat(int mat[][9]){
    for(int row=0; row < n; row++){
        for(int col=0; col < n; col++){
            cout << mat[row][col] << " ";

            if((col+1)%3 == 0){
                cout << '\t';
            }
        }

        if((row+1)%3 == 0){
            cout << endl;
        }

        cout << endl;
    }
}

bool solveSudoku(int mat[][9], int curr_row, int curr_col){
    ///Base Case
    if(curr_row == 9){
        printMat(mat);
        return true;
    }

    ///Crossed the last Cell in the row
    if(curr_col == 9){
        return solveSudoku(mat, curr_row+1, 0);
    }

    ///Skip if filled cell
    if(mat[curr_row][curr_col] != 0){
        return solveSudoku(mat, curr_row, curr_col+1);
    }

    ///White Cell
    ///Try to place every possible number
    for(int num=1; num <= 9; num++){
        if(isPossible(mat, curr_row, curr_col, num)){
            ///Place the number - assuming solution is possible with this
            mat[curr_row][curr_col] = num;
            bool isSolved = solveSudoku(mat, curr_row, curr_col+1);
            if(isSolved){
                return true;
            }
            ///loop will place the next number
        }
    }

    ///Backtracking
    mat[curr_row][curr_col] = 0;
    return false;
}

int main(){
    int mat[9][9] =
            {{5,3,0,0,7,0,0,0,0},
             {6,0,0,1,9,5,0,0,0},
             {0,9,8,0,0,0,0,6,0},
             {8,0,0,0,6,0,0,0,3},
             {4,0,0,8,0,3,0,0,1},
             {7,0,0,0,2,0,0,0,6},
             {0,6,0,0,0,0,2,8,0},
             {0,0,0,4,1,9,0,0,5},
             {0,0,0,0,8,0,0,7,9}};

    printMat(mat);
    cout << "Solution" << endl;
    solveSudoku(mat, 0, 0);

    return 0;
}
