#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **make_matrix(int rows, int cols) {
  int **matrix = calloc(rows, sizeof(int *));

  for (int i = 0; i < rows; i++) {
    matrix[i] = calloc(cols, sizeof(int));
  }

  return matrix;
}

int **matrix_multiply(int **a, int a_rows, int a_cols, int **b, int b_rows,
                      int b_cols) {
  if (a_rows != b_cols) {
    return NULL;
  }

  int **c = make_matrix(a_rows, b_cols);
  for (int i = 0; i < a_rows; i++) {
    for (int j = 0; j < b_cols; j++) {
      c[i][j] = 0;
      for (int k = 0; k < a_cols; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return c;
}

typedef struct {
  int **m;
  int **s;
} result_t;

void matrix_chain_order(int *p, int n, int **m, int **s) {
  int row = n + 1;

  for (int i = 1; i <= n; i++) {
    *((int *)m + row * i + i) = 0;
    *((int *)s + row * i + i) = 0;
  }

  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int j = i + l - 1;
      *((int *)m + row * i + j) = -1;

      for (int k = i; k <= j - 1; k++) {
        int tmp1 = *((int *)m + row * i + k);
        int tmp2 = *((int *)m + row * (k + 1) + j);

        int q = tmp1 + tmp2 + p[i - 1] * p[k] * p[j];

        int old = *((int *)m + row * i + j);

        if (q < old || old == -1) {
          *((int *)m + row * i + j) = q;
          *((int *)s + row * i + j) = k;
        }
      }
    }
  }
}

int main(void) {
  int p[] = {30, 35, 15, 5, 10, 20, 25};
  int n = 6;
  int m[n + 1][n + 1];
  int s[n + 1][n + 1];

  matrix_chain_order(p, n, (int **)m, (int **)s);

  printf("Table m:\n");

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }

  printf("\nTable s:\n");

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      printf("%d ", s[i][j]);
    }
    printf("\n");
  }
}
