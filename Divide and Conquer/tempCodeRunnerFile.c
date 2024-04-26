#include <stdio.h>

void multiply(int n, int A[][n], int B[][n], int C[][n]) {
  // Base case: If matrices are 1x1, perform single multiplication
  if (n == 1) {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  // Divide matrices into sub-matrices
  int half = n / 2;

  int a11[half][half], a12[half][half], a21[half][half], a22[half][half];
  int b11[half][half], b12[half][half], b21[half][half], b22[half][half];
  int c11[half][half], c12[half][half], c21[half][half], c22[half][half];

  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
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

  // Recursive calls for sub-matrices (4 multiplications per call)
  multiply(half, a11, b11, c11);
  multiply(half, a12, b21, c12);
  multiply(half, a21, b11, c21);
  multiply(half, a22, b22, c22);

  // Combine results back into the original matrix
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      C[i][j] = c11[i][j] + c12[i][j];
      C[i][j + half] = c11[i][j] + c12[i][j];
      C[i + half][j] = c21[i][j] + c22[i][j];
      C[i + half][j + half] = c21[i][j] + c22[i][j];
    }
  }
}

void printMatrix(int n, int matrix[][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int n;
  printf("Enter the size of square matrices (nxn): ");
  scanf("%d", &n);

  int A[n][n], B[n][n], C[n][n];

  printf("Enter elements for matrix A:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &A[i][j]);
    }
  }

  printf("Enter elements for matrix B:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &B[i][j]);
    }
  }

  multiply(n, A, B, C);

  printf("Matrix C (Result of A x B):\n");
  printMatrix(n, C);

  return 0;
}
