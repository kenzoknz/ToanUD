#define _USE_MATH_DEFINES
/*
    A = P * D * P^T
    Chuong trinh cheo hoa hai ma tran doi xung:
    1. Ma tran "dep" 2x2: A = [16, -4; -4, 1]
    2. Ma tran "xau" 3x3: A = [3, 1, 1; 1, 3, 1; 1, 1, 3] (co gia tri rieng lap)

    Phuong phap:
    - 2x2: Giai phuong trinh dac trung.
    - 3x3: Phuong phap xoay Jacobi de dam bao he vector rieng truc giao.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printMatrix(int n, double A[n][n], char *name);
void printVector(int n, double v[n], char *name);

void matrixMultiply(int n, double A[n][n], double B[n][n], double C[n][n]);
void transposeMatrix(int n, double A[n][n], double AT[n][n]);

void diagonalize_2x2();
void diagonalize_3x3_jacobi();

int main()
{
    diagonalize_2x2();
    diagonalize_3x3_jacobi();

    return 0;
}

void diagonalize_2x2()
{
    printf("\n--- Cheo hoa ma tran 2x2 ---\n");
    double A[2][2] = {{16, -4}, {-4, 1}};
    printMatrix(2, A, "A");

    double trace = A[0][0] + A[1][1];
    double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];

    double lambda1 = 17.0;
    double lambda2 = 0.0;

    printf("Gia tri rieng: lambda1 = %.4f, lambda2 = %.4f\n", lambda1, lambda2);

    double v1[2] = {-4, 1};

    double v2[2] = {1, 4};

    double norm1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
    v1[0] /= norm1;
    v1[1] /= norm1;
    double norm2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1]);
    v2[0] /= norm2;
    v2[1] /= norm2;

    printf("\nVector rieng da chuan hoa:\n");
    printVector(2, v1, "v1");
    printVector(2, v2, "v2");

    double P[2][2] = {{v1[0], v2[0]}, {v1[1], v2[1]}};
    double D[2][2] = {{lambda1, 0}, {0, lambda2}};
    double PT[2][2];
    transposeMatrix(2, P, PT);

    printMatrix(2, P, "P");
    printMatrix(2, D, "D");
    printMatrix(2, PT, "P^T");

    double temp[2][2], result[2][2];
    matrixMultiply(2, P, D, temp);
    matrixMultiply(2, temp, PT, result);
    printMatrix(2, result, "P * D * P^T (Kiem tra)");
}

void diagonalize_3x3_jacobi()
{
    printf("\n--- Cheo hoa ma tran 3x3 (Phuong phap Jacobi) ---\n");
    int n = 3;
    double A[3][3] = {{3, 1, 1}, {1, 3, 1}, {1, 1, 3}};

    double D[3][3], P[3][3], PT[3][3];
    int max_iter = 100;
    double epsilon = 1e-10;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = A[i][j];
            P[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    printMatrix(3, A, "A");

    for (int iter = 0; iter < max_iter; iter++)
    {

        double max_val = 0;
        int p = 0, q = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (fabs(D[i][j]) > max_val)
                {
                    max_val = fabs(D[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (max_val < epsilon)
            break;

        double theta;
        if (fabs(D[p][p] - D[q][q]) < epsilon)
        {
            theta = (D[p][q] > 0) ? M_PI / 4 : -M_PI / 4;
        }
        else
        {
            double tau = (D[q][q] - D[p][p]) / (2 * D[p][q]);
            double t = 1.0 / (fabs(tau) + sqrt(1 + tau * tau));
            if (tau < 0)
                t = -t;
            theta = atan(t);
        }

        double c = cos(theta);
        double s = sin(theta);

        double d_pp = D[p][p];
        double d_qq = D[q][q];
        D[p][p] = c * c * d_pp - 2 * c * s * D[p][q] + s * s * d_qq;
        D[q][q] = s * s * d_pp + 2 * c * s * D[p][q] + c * c * d_qq;
        D[p][q] = D[q][p] = 0.0;

        for (int i = 0; i < n; i++)
        {
            if (i != p && i != q)
            {
                double d_ip = D[i][p];
                double d_iq = D[i][q];
                D[i][p] = D[p][i] = c * d_ip - s * d_iq;
                D[i][q] = D[q][i] = s * d_ip + c * d_iq;
            }
        }

        for (int i = 0; i < n; i++)
        {
            double p_ip = P[i][p];
            double p_iq = P[i][q];
            P[i][p] = c * p_ip - s * p_iq;
            P[i][q] = s * p_ip + c * p_iq;
        }
    }

    printf("\nKet qua sau khi cheo hoa:\n");
    double eigenvalues[3] = {D[0][0], D[1][1], D[2][2]};
    printf("Gia tri rieng: %.4f, %.4f, %.4f\n", eigenvalues[0], eigenvalues[1], eigenvalues[2]);

    transposeMatrix(3, P, PT);
    printMatrix(3, D, "D (ma tran cheo)");
    printMatrix(3, P, "P (ma tran truc giao)");

    double temp[3][3], result[3][3];
    matrixMultiply(3, P, D, temp);
    matrixMultiply(3, temp, PT, result);
    printMatrix(3, result, "P * D * P^T (Kiem tra)");
}

void printMatrix(int n, double A[n][n], char *name)
{
    printf("\nMa tran %s:\n", name);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.4f ", A[i][j]);
        }
        printf("\n");
    }
}

void printVector(int n, double v[n], char *name)
{
    printf("%s: [", name);
    for (int i = 0; i < n; i++)
    {
        printf("%8.4f", v[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]\n");
}

void matrixMultiply(int n, double A[n][n], double B[n][n], double C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void transposeMatrix(int n, double A[n][n], double AT[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            AT[i][j] = A[j][i];
        }
    }
}