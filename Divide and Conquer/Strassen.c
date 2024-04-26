#include <stdio.h>

// Function to add two matrices
void add(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtract(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen algorithm
void strassen(int n, int A[n][n], int B[n][n], int C[n][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int n1 = n / 2;

    // We divide the original matrix into halves
    int A11[n1][n1], A12[n1][n1], A21[n1][n1], A22[n1][n1];
    int B11[n1][n1], B12[n1][n1], B21[n1][n1], B22[n1][n1];
    // Answer matrix into halves
    int C11[n1][n1], C12[n1][n1], C21[n1][n1], C22[n1][n1];
    // 7 multiplication mayrix that we will obtain
    int M1[n1][n1], M2[n1][n1], M3[n1][n1], M4[n1][n1], M5[n1][n1], M6[n1][n1], M7[n1][n1];
    // This temp matrices are needed as a intermediate
    int temp1[n1][n1], temp2[n1][n1];

    // Divide matrices A and B into submatrices
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n1];
            A21[i][j] = A[i + n1][j];
            A22[i][j] = A[i + n1][j + n1];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n1];
            B21[i][j] = B[i + n1][j];
            B22[i][j] = B[i + n1][j + n1];
        }
    }

    // Compute M1 = (A11 + A22) * (B11 + B22)
    add(n1, A11, A22, temp1);
    add(n1, B11, B22, temp2);
    strassen(n1, temp1, temp2, M1);

    // Compute M2 = (A21 + A22) * B11
    add(n1, A21, A22, temp1);
    strassen(n1, temp1, B11, M2);

    // Compute M3 = A11 * (B12 - B22)
    subtract(n1, B12, B22, temp1);
    strassen(n1, A11, temp1, M3);

    // Compute M4 = A22 * (B21 - B11)
    subtract(n1, B21, B11, temp1);
    strassen(n1, A22, temp1, M4);

    // Compute M5 = (A11 + A12) * B22
    add(n1, A11, A12, temp1);
    strassen(n1, temp1, B22, M5);

    // Compute M6 = (A21 - A11) * (B11 + B12)
    subtract(n1, A21, A11, temp1);
    add(n1, B11, B12, temp2);
    strassen(n1, temp1, temp2, M6);

    // Compute M7 = (A12 - A22) * (B21 + B22)
    subtract(n1, A12, A22, temp1);
    add(n1, B21, B22, temp2);
    strassen(n1, temp1, temp2, M7);

    // Compute C11 = M1 + M4 - M5 + M7
    add(n1, M1, M4, temp1);
    subtract(n1, temp1, M5, temp2);
    add(n1, temp2, M7, C11);

    // Compute C12 = M3 + M5
    add(n1, M3, M5, C12);

    // Compute C21 = M2 + M4
    add(n1, M2, M4, C21);

    // Compute C22 = M1 - M2 + M3 + M6
    subtract(n1, M1, M2, temp1);
    add(n1, temp1, M3, temp2);
    add(n1, temp2, M6, C22);

    // Combine submatrices to form matrix C
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + n1] = C12[i][j];
            C[i + n1][j] = C21[i][j];
            C[i + n1][j + n1] = C22[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int n, int matrix[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("Enter the size of square matrices (nxn): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];

    printf("Enter elements for matrix A:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements for matrix B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    strassen(n, A, B, C);

    printf("Matrix C (Result of A x B):\n");
    printMatrix(n, C);

    return 0;
}
