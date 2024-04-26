#include <stdbool.h>
#include <stdio.h>
int N;
// Function to print solution
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

bool canPlace(int board[N][N], int row, int col)
{
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}


bool NQueen(int board[N][N], int col)
{
    // If all queens are placed then return true
    if (col >= N)
        return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++)
    {
        // Check if the queen can be placed on board[i][col]
        if (canPlace(board, i, col))
        {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // Recur to place rest of the queens
            if (NQueen(board, col + 1))
                return true;

            // If placing queen in board[i][col]
            // doesn't lead to a solution, then
            // remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }
    // If the queen cannot be placed in any row in this column col then return false
    return false;
}

// Main
int main()
{   
    printf("Enter N for NxN matrix : ");
    scanf("%d" , &N);
    int board[N][N];
    for(int i = 0 ; i<N ; i++){
        for(int j=0 ; j<N ; j++){
            board[i][j] = 0;
        }
    }

    // If no solution present
    if (NQueen(board, 0) == false)
    {
        printf("Solution does not exist");
        return false;
    }

    printSolution(board);
    return 0;
}
