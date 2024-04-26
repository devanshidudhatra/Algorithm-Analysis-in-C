#include <stdio.h>

void multiply(int n, int A[][n], int B[][n], int C[][n]) 
{
  // Base case: If matrices are 1x1, perform single multiplication
  if (n == 1) 
  {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  // Divide matrices into sub-matrices
  int half = n / 2;

  int a11[half][half], a12[half][half], a21[half][half], a22[half][half];
  int b11[half][half], b12[half][half], b21[half][half], b22[half][half];
  int c1111[half][half], c1221[half][half], c1112[half][half], c1222[half][half], c2111[half][half], c2221[half][half], c2112[half][half], c2222[half][half];

  for (int i = 0; i < half; i++) 
  {
    for (int j = 0; j < half; j++) 
    {
      a11[i][j] = A[i][j];
      a12[i][j] = A[i][j + half];
      a21[i][j] = A[i + half][j];
      a22[i][j] = A[i + half][j + half];

      b11[i][j] = B[i][j];
      b12[i][j] = B[i][j + half];
      b21[i][j] = B[i + half][j];
      b22[i][j] = B[i + half][j + half];
    }
  }

  // Recursive calls for sub-matrices 
  multiply(half, a11, b11, c1111);
  multiply(half, a12, b21, c1221);
  multiply(half, a11, b12, c1112);
  multiply(half, a12, b22, c1222);
  multiply(half, a21, b11, c2111);
  multiply(half, a22, b21, c2221);
  multiply(half, a21, b12, c2112);
  multiply(half, a22, b22, c2222);

  // Combine results back into the original matrix
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      C[i][j] = c1111[i][j] + c1221[i][j];
      C[i][j + half] = c1112[i][j] + c1222[i][j];
      C[i + half][j] = c2111[i][j] + c2221[i][j];
      C[i + half][j + half] = c2112[i][j] + c2222[i][j];
    }
  }
}

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

  multiply(n, A, B, C);

  printf("Matrix C (Result of A x B):\n");
  printMatrix(n, C);

  return 0;
}