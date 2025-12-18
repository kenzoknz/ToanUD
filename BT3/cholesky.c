#include <stdio.h>
#include <math.h>

#define N 3   //size of the matrix

void cholesky(int matrix[N][N]) {
    printf("Original Matrix (A):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%6d ", matrix[i][j]);
        printf("\n");
    }
    double lower[N][N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;

            if (j == i) {
                for (int k = 0; k < j; k++)
                    sum += lower[j][k] * lower[j][k];
                lower[j][j] = sqrt(matrix[j][j] - sum);
            } else {
                for (int k = 0; k < j; k++)
                    sum += lower[i][k] * lower[j][k];
                lower[i][j] = (matrix[i][j] - sum) / lower[j][j];
            }
        }
    }

    printf("\nLower Triangular Matrix (L):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%8.4f ", lower[i][j]);
        printf("\n");
    }

    printf("\nTranspose (L^T):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%8.4f ", lower[j][i]);
        printf("\n");
    }
}

int main(void) {
    int matrix[N][N] = {
        { 4,  12, -16 },
        { 12, 37, -43 },
        {-16, -43, 98 }
    };

    cholesky(matrix);
    return 0;
}
