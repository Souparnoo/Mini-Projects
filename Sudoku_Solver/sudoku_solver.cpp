#include <iostream>
using namespace std;

const int N = 9;

// Function to print the board
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if it's safe to place num at board[row][col]
bool Safe(int board[N][N], int row, int col, int num) {
    // Row check
    for (int x = 0; x < N; x++)
        if (board[row][x] == num)
            return false;

    // Column check
    for (int x = 0; x < N; x++)
        if (board[x][col] == num)
            return false;

    // 3x3 box check
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Main recursive backtracking function
bool solve(int board[N][N], int row = 0, int col = 0) {
    if (row == N - 1 && col == N)
        return true;

    if (col == N) {
        row++;
        col = 0;
    }

    if (board[row][col] != 0)
        return solve(board, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (Safe(board, row, col, num)) {
            board[row][col] = num;

            if (solve(board, row, col + 1))
                return true;
        }

        board[row][col] = 0; // Backtrack
    }

    return false;
}

// Driver code
int main() {
    int board[N][N] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    if (solve(board)) {
        cout << "Solved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}
