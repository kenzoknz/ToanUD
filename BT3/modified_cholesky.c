#include <stdio.h>
#include <math.h>

#define N 3  
void print_matrix(double A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%10.4f ", A[i][j]);
        printf("\n");
    }
}

//  LDL^T 
int ldlt_decomposition(double A[N][N], double L[N][N], double D[N]) {
    for (int i = 0; i < N; i++) {
        //  D[i]
        double sum = 0.0;
        for (int k = 0; k < i; k++)
            sum += L[i][k] * L[i][k] * D[k];
        D[i] = A[i][i] - sum;
        if (fabs(D[i]) < 1e-12) return 0; // Không khả nghịch

        //  L[j][i] 
        for (int j = i + 1; j < N; j++) {
            sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * L[i][k] * D[k];
            L[j][i] = (A[j][i] - sum) / D[i];
        }
    }
    //  L[i][i] = 1, L[i][j] = 0 với j > i
    for (int i = 0; i < N; i++) {
        L[i][i] = 1.0;
        for (int j = i + 1; j < N; j++)
            L[i][j] = 0.0; 
    }
    return 1;
}

int main() {
    double A[N][N] = {
        { 4, 2, 4 },
        { 2, 10, 5 },
        { 4, 5, 9 }
    };
    double L[N][N] = {0};
    double D[N] = {0};

    printf("A:\n");
    print_matrix(A);

    if (!ldlt_decomposition(A, L, D)) {
        printf("Ma tran khong kha nghich hoac khong phan tich duoc.\n");
        return 1;
    }

    printf("\nL:\n");
    print_matrix(L);

    printf("\n D (diagonal):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                printf("%10.4f ", D[i]);
            else
                printf("%10.4f ", 0.0);
        }
        printf("\n");
    }

    printf("\n L^T (transpose):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%10.4f ", L[j][i]);
        printf("\n");
    }

    return 0;
}