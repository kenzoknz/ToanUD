#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <complex>

#define PI 3.141592654
#define MAX_SIZE 10
using namespace std;

typedef double matrix[MAX_SIZE][MAX_SIZE];
double B1[MAX_SIZE][MAX_SIZE] = {0.0};

void inputMatrix(int n, matrix A);
void outputMatrix(int n, const matrix A);
void multiMatrix(const matrix A, const matrix B, matrix C, int cola, int rowa, int rowb);
void Danhilepski(matrix A, matrix M, matrix M1, matrix B, int n);
void solution2(double a, double b, double c, double x[]);
void solution3(double a, double b, double c, double d, double x[]);
void solveCharacteristicEquation(const matrix A, double lambda[], int n);
double determinant(const matrix A, int n);
bool invertMatrix(const matrix A, matrix inverse, int n);
void sortEigenvalues(double lambda[], int n);
void verifyEigendecomposition(const matrix A, const matrix S, const matrix D, const matrix Sinv, const double lambda[], int n);
void performEigenDecomposition(int n);
/*
Điều kiện ma trận A để phân rã eigen:
- Ma trận phải khả nghịch
- Phải có đầy đủ vector riêng và trị riêng
- Ma trận có đủ eigenvalues thực
*/

int main()
{
    int n;
    cout << "Enter matrix size (2-" << MAX_SIZE << "): ";
    cin >> n;
    
    if (n < 2 || n > MAX_SIZE)
    {
        cout << "Invalid size! Program terminated." << endl;
        return 1;
    }
    
    performEigenDecomposition(n);

    return 0;
}

void performEigenDecomposition(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            B1[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    matrix A, M, M1, B, tempA;
    double lambda[MAX_SIZE] = {0};

    inputMatrix(n, A);

    // Copy original A to tempA for verification later
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            tempA[i][j] = A[i][j];
        }
    }

    cout << "\nOriginal Matrix A:" << endl;
    outputMatrix(n, A);

    Danhilepski(A, M, M1, B, n);
    solveCharacteristicEquation(A, lambda, n);
    sortEigenvalues(lambda, n);

    cout << "\nEigenvalues:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << setprecision(6) << fixed << "lambda[" << i << "] = " << lambda[i] << endl;
    }

    // Compute eigenvectors
    matrix y, x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            y[j][i] = pow(lambda[i], n - j - 1);
        }
    }
    multiMatrix(B1, y, x, n, n, n);

    cout << "\nS (Eigenvector matrix):" << endl;
    outputMatrix(n, x);

    // Create diagonal matrix D
    matrix D;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            D[i][j] = (i == j) ? lambda[i] : 0.0;
        }
    }

    cout << "\nD (Diagonal eigenvalue matrix):" << endl;
    outputMatrix(n, D);

    // Invert S and verify
    matrix inverse;
    if (invertMatrix(x, inverse, n))
    {
        cout << "\nS^-1 (Inverse of eigenvector matrix):" << endl;
        outputMatrix(n, inverse);

        // Verify the decomposition
        verifyEigendecomposition(tempA, x, D, inverse, lambda, n);
    }
    else
    {
        cout << "\nWarning: Could not compute S^-1. Matrix may not be diagonalizable." << endl;
    }
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

void solution2(double a, double b, double c, double x[])
{
    if (std::fabs(a) < 1e-9)
    {
        cout << "Error: 'a' coefficient is near zero in quadratic solver." << endl;
        x[0] = x[1] = 0.0 / 0.0;
        return;
    }

    double delta = b * b - 4.0 * a * c;

    if (delta >= 0)
    {
        x[0] = (-b + sqrt(delta)) / (2.0 * a);
        x[1] = (-b - sqrt(delta)) / (2.0 * a);
    }
    else
    {
        // Complex roots - take real part
        x[0] = -b / (2.0 * a);
        x[1] = -b / (2.0 * a);
        cout << "Warning: Complex eigenvalues detected (only real parts shown)." << endl;
    }
}

void solution3(double a, double b, double c, double d, double x[])
{
    // Solve cubic equation: ax^3 + bx^2 + cx + d = 0
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

void solveCharacteristicEquation(const matrix A, double lambda[], int n)
{
    // Extract coefficients from upper row of Danhilepski form
    // Characteristic equation: det(A - λI) = 0
    // After Danhilepski: λ^n + c_{n-1}λ^{n-1} + ... + c_1λ + c_0 = 0
    // Coefficients are in -A[0][j]
    
    if (n == 2)
    {
        // λ^2 - A[0][0]·λ - A[0][1] = 0
        solution2(1.0, -A[0][0], -A[0][1], lambda);
    }
    else if (n == 3)
    {
        // λ^3 - A[0][0]·λ^2 - A[0][1]·λ - A[0][2] = 0
        solution3(1.0, -A[0][0], -A[0][1], -A[0][2], lambda);
    }
    else if (n == 4)
    {
        // λ^4 - A[0][0]·λ^3 - A[0][1]·λ^2 - A[0][2]·λ - A[0][3] = 0
        cout << "Using numerical method for 4x4 matrix..." << endl;
        
        // Initial guesses spread across range
        double guess[4] = {-10.0, -1.0, 1.0, 10.0};
        
        for (int i = 0; i < 4; i++)
        {
            double x = guess[i];
            for (int iter = 0; iter < 1000; iter++)
            {
                // f(x) = x^4 - A[0][0]x^3 - A[0][1]x^2 - A[0][2]x - A[0][3]
                double f = pow(x, 4) - A[0][0] * pow(x, 3) - A[0][1] * pow(x, 2) - A[0][2] * x - A[0][3];
                // f'(x) = 4x^3 - 3A[0][0]x^2 - 2A[0][1]x - A[0][2]
                double df = 4.0 * pow(x, 3) - 3.0 * A[0][0] * pow(x, 2) - 2.0 * A[0][1] * x - A[0][2];
                
                if (fabs(df) < 1e-12) break;
                
                double x_new = x - f / df;
                if (fabs(x_new - x) < 1e-9)
                {
                    x = x_new;
                    break;
                }
                x = x_new;
            }
            lambda[i] = x;
        }
    }
    else
    {
        cout << "Warning: Solving characteristic equation for n=" << n 
             << " not fully implemented. Using trace approximation." << endl;
        for (int i = 0; i < n; i++)
        {
            lambda[i] = A[0][i]; // Rough approximation
        }
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
