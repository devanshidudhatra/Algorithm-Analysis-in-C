#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX

int n;

void fillDistanceMatrix(int A[n][n], int D[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                D[i][j] = 0;
            }
            else if (A[i][j] == 0)
            {
                D[i][j] = INF;
            }
            else
            {
                D[i][j] = A[i][j];
            }
        }
    }
}

void Floyd_Warshall(int A[n][n], int D[n][n])
{
    fillDistanceMatrix(A, D);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (D[i][k] < INF && D[k][j] < INF)
                {
                    if ((D[i][k] + D[k][j]) < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }
    }
}

int main()
{
    printf("Enter size of nxn matrix : ");
    scanf("%d", &n);
    int A[n][n], D[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element A[%d][%d] : ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    Floyd_Warshall(A, D);

    // To print Adjacency Matrix
    printf("Result : \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (D[i][j] == INF)
            {
                printf("%7s", "INF");
            }
            else
            {
                printf("%7d", D[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}