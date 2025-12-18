#include <bits/stdc++.h>

#define PI 3.141592654
#define MAX_SIZE 10
using namespace std;

typedef double matrix[MAX_SIZE][MAX_SIZE];
double B1[MAX_SIZE][MAX_SIZE] = {0.0};

void inputMatrix(int n, matrix A);
void outputMatrix(int n, const matrix A);
void multiMatrix(const matrix A, const matrix B, matrix C, int cola, int rowa, int rowb);
void Danhilepski(matrix A, matrix M, matrix M1, matrix B, int n);
void solution(double a, double b, double c, double d, double x[]);
double determinant(const matrix A, int n);
bool invertMatrix(const matrix A, matrix inverse, int n);
void sortEigenvalues(double lambda[], int n);
void verifyEigendecomposition(const matrix A, const matrix S, const matrix D, const matrix Sinv, const double lambda[], int n);


int main()
{

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            B1[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    matrix A, M, M1, B, tempA;
    double lambda[3] = {0, 0, 0};
    int n;

    cout << "Enter n: ";
    cin >> n;

    inputMatrix(n, A);

    // Copy original A to tempA for verification later
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            tempA[i][j] = A[i][j];
        }
    }

    Danhilepski(A, M, M1, B, n);

    if (n == 3 && std::fabs(A[1][0]) > 1e-9 && std::fabs(A[2][0]) > 1e-9)
    {
        cout << "Warning: Danhilepski might not have succeeded in full transformation." << endl;
    }

    solution(1.0, -A[0][0], -A[0][1], -A[0][2], lambda);
    sortEigenvalues(lambda, n);

    cout << "\nDanhilepski's solution: Eigen values:" << endl;

    for (int i = 0; i < n; ++i)
    {
        cout << setprecision(4) << fixed << "lambda[" << i << "] = " << lambda[i] << endl;
    }

    if (n == 3)
    {
        double y[3][MAX_SIZE], x[3][MAX_SIZE];

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                y[j][i] = pow(lambda[i], 3 - j - 1);
            }
        }
        multiMatrix(B1, y, x, 3, 3, 3);

        cout << "\nS (Eigenvector matrix): " << endl;
        outputMatrix(3, x);

        matrix D;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                D[i][j] = (i == j) ? lambda[i] : 0.0;
            }
        }

        cout << "\nDiagonalized matrix D: " << endl;
        outputMatrix(3, D);

        matrix inverse;
        if (invertMatrix(x, inverse, 3))
        {
            cout << "\nS^-1 (Inverse Eigenvector matrix): " << endl;
            outputMatrix(3, inverse);

            // Verify the decomposition
            verifyEigendecomposition(tempA, x, D, inverse, lambda, 3);
        }
    }

    return 0;
}
void inputMatrix(int n, matrix A)
{
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }
}

void outputMatrix(int n, const matrix A)
{
    cout << fixed << setprecision(5);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(12) << A[i][j] ;
        }
        cout << endl;
    }
}

void multiMatrix(const matrix A, const matrix B, matrix C, int cola, int rowa, int rowb)
{
    for (int i = 0; i < cola; i++)
    {
        for (int j = 0; j < rowb; j++)
        {
            C[i][j] = 0.0;
            for (int k = 0; k < rowa; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Danhilepski(matrix A, matrix M, matrix M1, matrix B, int n)
{

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            B1[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = n - 2; k >= 0; k--)
    {

        if (std::fabs(A[k + 1][k]) < 1e-9)
        {

            cout << "Warning: Near-zero pivot in Danhilepski at k=" << k << endl;

            return;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                M[i][j] = (i == j) ? 1.0 : 0.0;
                M1[i][j] = (i == j) ? 1.0 : 0.0;

                if (i == k)
                {
                    M1[i][j] = A[k + 1][j];

                    if (j == k)
                    {
                        M[i][j] = 1.0 / A[k + 1][k];
                    }
                    else
                    {
                        M[i][j] = -A[k + 1][j] / A[k + 1][k];
                    }
                }
            }
        }

        multiMatrix(A, M, B, n, n, n);
        multiMatrix(M1, B, A, n, n, n);

        multiMatrix(B1, M, B, n, n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                B1[i][j] = B[i][j];
            }
        }
        
    }
}

double determinant(const matrix A, int n)
{
    double det = 0.0;
    if (n == 1)
        return A[0][0];
    if (n == 2)
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];

    matrix temp;
    for (int f = 0; f < n; f++)
    {
        int temp_i = 0;
        for (int i = 1; i < n; i++)
        {
            int temp_j = 0;
            for (int j = 0; j < n; j++)
            {
                if (j == f)
                    continue;
                temp[temp_i][temp_j] = A[i][j];
                temp_j++;
            }
            temp_i++;
        }
        det += (f % 2 == 0 ? 1.0 : -1.0) * A[0][f] * determinant(temp, n - 1);
    }
    return det;
}

bool invertMatrix(const matrix A, matrix inverse, int n)
{
    double det = determinant(A, n);
    if (std::fabs(det) < 1e-9)
    {
        cout << "Matrix is singular (det approx 0) and cannot be inverted." << endl;
        return false;
    }

    matrix adjoint;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix temp;
            int temp_i = 0;

            for (int x = 0; x < n; x++)
            {
                if (x == i)
                    continue;
                int temp_j = 0;
                for (int y = 0; y < n; y++)
                {
                    if (y == j)
                        continue;
                    temp[temp_i][temp_j] = A[x][y];
                    temp_j++;
                }
                temp_i++;
            }

            double cofactor = pow(-1.0, i + j) * determinant(temp, n - 1);

            adjoint[j][i] = cofactor;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inverse[i][j] = adjoint[i][j] / det;
        }
    }
    return true;
}

void solution(double a, double b, double c, double d, double x[])
{

    if (std::fabs(a) < 1e-9)
    {

        cout << "Error: 'a' coefficient is near zero in cubic solver." << endl;
        x[0] = x[1] = x[2] = 0.0 / 0.0;
        return;
    }

    double p = (3.0 * a * c - b * b) / (3.0 * a * a);
    double q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);

    double delta = (q * q / 4.0) + (p * p * p / 27.0);

    if (delta <= 1e-9)
    {

        double phi_arg = -q / (2.0 * sqrt(-p * p * p / 27.0));

        phi_arg = std::min(1.0, std::max(-1.0, phi_arg));

        double phi = acos(phi_arg);
        double R = 2.0 * sqrt(-p / 3.0);
        double b_over_3a = b / (3.0 * a);

        x[0] = R * cos(phi / 3.0) - b_over_3a;
        x[1] = R * cos((phi + 2.0 * PI) / 3.0) - b_over_3a;
        x[2] = R * cos((phi - 2.0 * PI) / 3.0) - b_over_3a;
    }

    else
    {
        double R = sqrt(delta);
        double S = pow(-q / 2.0 + R, 1.0 / 3.0);
        double T = pow(-q / 2.0 - R, 1.0 / 3.0);

        x[0] = S + T - b / (3.0 * a);
        x[1] = 0.0;
        x[2] = 0.0;
    }

}

void sortEigenvalues(double lambda[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (lambda[j] < lambda[j + 1])
            {
                double temp = lambda[j];
                lambda[j] = lambda[j + 1];
                lambda[j + 1] = temp;
            }
        }
    }
}

void verifyEigendecomposition(const matrix A, const matrix S, const matrix D, const matrix Sinv, const double lambda[], int n)
{
    matrix Temp, Reconstructed_A, Error;

    multiMatrix(S, D, Temp, n, n, n);
    multiMatrix(Temp, Sinv, Reconstructed_A, n, n, n);
    double max_error = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Error[i][j] = Reconstructed_A[i][j] - A[i][j];
            if (fabs(Error[i][j]) > max_error)
            {
                max_error = fabs(Error[i][j]);
            }
        }
    }

    cout << "\nVerification of Eigendecomposition (S * D * S^-1 - A):" << endl;
    cout << "Error matrix:" << endl;
    outputMatrix(n, Error);
    cout << "Maximum absolute error in reconstruction: " << max_error << endl;

    if (max_error < 1e-5)
    {
        cout << "Eigendecomposition verified successfully within tolerance." << endl;
    }
    else
    {
        cout << "Warning: Eigendecomposition verification failed. Error exceeds tolerance." << endl;
    }
}
