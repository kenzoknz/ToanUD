#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 10
//Điều kiện của ma trận A là: ma trận vuông, đối xứng qua chéo chính
void input_matrix(double **A, int n) {
    printf("Nhap ma tran %dx%d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
}
void print_ldlt(double **L, double *D, int n) {
    
    printf("\nMa tran L:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10.5f ", L[i][j]);
        printf("\n");
    }
     printf("\nMa tran D (diagonal):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                printf("%10.5f ", D[i]);
            else
                printf("%10.5f ", 0.0);
        }
        printf("\n");
    }

    printf("\nMa tran L^T (transpose):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10.5f ", L[j][i]);
        printf("\n");
    }
}
void print_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10.5f ", A[i][j]);
        printf("\n");
    }
}

double** allocate_matrix(int n) {
    double **matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.0;
        }
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

//  LDL^T 
int ldlt_decomposition(double **A, double **L, double *D, int n) {
    for (int i = 0; i < n; i++) {
        //  D[i]
        double sum = 0.0;
        for (int k = 0; k < i; k++)
            sum += L[i][k] * L[i][k] * D[k];
        D[i] = A[i][i] - sum;
        if (fabs(D[i]) < 1e-5) return 0; // Không khả nghịch

        //  L[j][i] 
        for (int j = i + 1; j < n; j++) {
            sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * L[i][k] * D[k];
            L[j][i] = (A[j][i] - sum) / D[i];
        }
    }
    //  L[i][i] = 1, L[i][j] = 0 với j > i
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
        for (int j = i + 1; j < n; j++)
            L[i][j] = 0.0; 
    }
    return 1;
}

int verify_ldlt(double **A, double **L, double *D, int n, double *max_error) {
    double **temp = allocate_matrix(n);
    double **result = allocate_matrix(n);
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            temp[i][j] = L[i][j] * D[j];
        }
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            result[i][j] = 0.0;
            for (k = 0; k < n; k++) {
                result[i][j] += temp[i][k] * L[j][k];  // L[j][k] = L^T[k][j]
            }
        }
    }
    
    *max_error = 0.0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            double error = fabs(A[i][j] - result[i][j]);
            if (error > *max_error) {
                *max_error = error;
            }
        }
    }
    
    printf("\nMa tran ket qua L*D*L^T:\n");
    print_matrix(result, n);
    
    printf("\nSai so lon nhat: %.8f\n", *max_error);
    
    int is_valid = (*max_error < 1e-5);
    
    if (is_valid) {
        printf("=> Kiem tra THANH CONG! A = L*D*L^T\n");
    } else {
        printf("=> Kiem tra THAT BAI! Sai so qua lon.\n");
    }
    free_matrix(temp, n);
    free_matrix(result, n);
    return is_valid;
}

int main() {
    int n;
    
    printf("Nhap cap ma tran (1-%d): ", MAX_N);
    scanf("%d", &n);
    
    if (n < 1 || n > MAX_N) {
        printf("Cap ma tran khong hop le!\n");
        return 1;
    }
    
    double **A = allocate_matrix(n);
    double **L = allocate_matrix(n);
    double *D = (double*)calloc(n, sizeof(double));

    input_matrix(A, n);

    printf("\nMa tran A da nhap:\n");
    print_matrix(A, n);

    if (!ldlt_decomposition(A, L, D, n)) {
        printf("Ma tran khong kha nghich hoac khong phan tich duoc.\n");
        free_matrix(A, n);
        free_matrix(L, n);
        free(D);
        return 1;
    }

    print_ldlt(L, D, n);

    printf("KIEM TRA PHAN TICH LDLT\n");
    double max_error;
    verify_ldlt(A, L, D, n, &max_error);
    
    // Giải phóng bộ nhớ
    free_matrix(A, n);
    free_matrix(L, n);
    free(D);

    return 0;
}