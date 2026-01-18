#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <cmath>
#define eps 1e-5
using namespace std;
using namespace Eigen;

void input(double A[][10], int row, int col);
void swap(double &a, double &b);
void display(double A[][10], int row, int col);
void transpose(double A[][10], double At[][10], int rows, int cols);
void NhanMaTran(MatrixXd &S, double A[][10], double B[][10], int row1, int col1, int col2);
void GetEigenValuesAndVector(MatrixXd S, MatrixXd &lambda, MatrixXd &vector);
void tinhMatranS(MatrixXd lambda, double sigma[][10], int rows, int cols);
void tinhMatranU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols);
void tinhMatranV(MatrixXd vector, double V[][10]);
void gramSchmidt(double U[][10], int rows, int cols);
void computeApproximateMatrix(double A3[][10], double U[][10], double sigma[][10], double VT[][10], int rows, int cols, int k);
double frobeniusNorm(double A[][10], double B[][10], int rows, int cols);

int main()
{
    int rows, cols;
    double A[10][10], At[10][10];
    cout << "Nhap ma tran " << endl;
    cout << "Hang: ";
    cin >> rows;
    cout << "Cot: ";
    cin >> cols;
    cout << "Nhap phan tu ma tran: " << endl;
    input(A, rows, cols);
    cout << "Ma tran goc" << endl;
    display(A, rows, cols);
    MatrixXd S(cols, cols), lambda(cols, 1), vector(cols, cols);
    transpose(A, At, rows, cols);
    NhanMaTran(S, At, A, cols, rows, cols);
    GetEigenValuesAndVector(S, lambda, vector);
    cout << "Phan ra theo U*sigma*V^T" << endl;
    double sigma[10][10], U[10][10], V[10][10];
    tinhMatranU(lambda, vector, U, A, rows, cols);
    cout << "Ma tran U:" << endl;
    display(U, rows, rows);
    tinhMatranS(lambda, sigma, rows, cols);
    cout << "Ma tran sigma:" << endl;
    display(sigma, rows, cols);
    tinhMatranV(vector, V);
    cout << "Ma tran V^T:" << endl;
    double VT[10][10];
    transpose(V, VT, cols, cols);
    display(VT, cols, cols);
    // Thử lại U * sigma * V^T - A
    MatrixXd Umat(rows, rows), Sig(rows, cols), VTrans(cols, cols);
    
   cout << "Kiem tra U * Sigma * V^T - A:" << endl;
   for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            Umat(i, j) = U[i][j];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            Sig(i, j) = sigma[i][j];

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < cols; j++)
            VTrans(i, j) = VT[i][j];

    MatrixXd Acheck(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            Acheck(i, j) = A[i][j];

    MatrixXd diff = Umat * Sig * VTrans - Acheck;

    cout << diff << endl;

    cout << "TINH MA TRAN XAP XI A3" << endl;
    
    int k = 3; 
    int max_k = min(rows, cols);
    if (k > max_k) {
        cout << "Canh bao: Chi co " << max_k << " gia tri ky di, su dung k = " << max_k << endl;
        k = max_k;
    }
    
    double A3[10][10];
    computeApproximateMatrix(A3, U, sigma, VT, rows, cols, k);
    
    cout << "\nMa tran xap xi A" << k << " (su dung " << k << " gia tri ky di lon nhat):" << endl;
    display(A3, rows, cols);
    
    cout << "\n========================================" << endl;
    cout << "TINH SAI SO FROBENIUS" << endl;
    cout << "========================================" << endl;
    
    double error = frobeniusNorm(A, A3, rows, cols);
    
    cout << "\nSai so Frobenius ||A - A" << k << "||: " << fixed << setprecision(10) << error << endl;
    
    // Tính và hiển thị ma trận sai số (A - A3)
    cout << "\nMa tran sai so (A - A" << k << "):" << endl;
    double diff_matrix[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            diff_matrix[i][j] = A[i][j] - A3[i][j];
        }
    }
    display(diff_matrix, rows, cols);
    
    return 0;
}

void input(double A[][10], int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
           // cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A[i][j];
        }
}

void display(double A[][10], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout << setw(9) << fixed << setprecision(5) << A[i][j];
        cout << endl;
    }
}

void swap(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

void transpose(double A[][10], double At[][10], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            At[j][i] = A[i][j];
        }
}

void NhanMaTran(MatrixXd &S, double A[][10], double B[][10], int row1, int col1, int col2)
{
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            S(i, j) = 0;
            for (int k = 0; k < col1; k++)
            {
                S(i, j) = S(i, j) + A[i][k] * B[k][j];
            }
        }
    }
}

void GetEigenValuesAndVector(MatrixXd S, MatrixXd &lambda, MatrixXd &vector)
{
    SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(S);
    vector = eigensolver.eigenvectors();
    lambda = eigensolver.eigenvalues();
    int k = lambda.rows();
    int l = vector.rows();
    for (int i = 0; i < k; i++)
    {
        if (lambda(i, 0) < eps)
            lambda(i, 0) = 0;
    }
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
        {
            if (lambda(j, 0) > lambda(i, 0))
            {
                swap(lambda(j, 0), lambda(i, 0));
                for (int h = 0; h < l; h++)
                    swap(vector(h, i), vector(h, j));
            }
        }
}

void tinhMatranU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols)
{
    MatrixXd ui(rows, 1);
    double Vi[cols][10];
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Vi[j][0] = vector(j, i);
        }
        NhanMaTran(ui, A, Vi, rows, cols, 1);
        for (int k = 0; k < rows; k++)
        {
            if (lambda(i, 0) != 0)
            {
                U[k][i] = (1 / sqrt(lambda(i, 0))) * ui(k, 0);
            }
            else
            {
                U[k][i] = 0;
            }
        }
    }
    if (rows > cols)
    {
        if (rows > cols)
        {
            MatrixXd U_matrix(rows, cols);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    U_matrix(i, j) = U[i][j];
                }
            }
            MatrixXd orthogonal_basis = U_matrix.householderQr().householderQ();
            for (int j = cols; j < rows; j++)
            {
                for (int i = 0; i < rows; i++)
                {
                    U[i][j] = orthogonal_basis(i, j);
                }
            }
        }
    }
    else
    {
        gramSchmidt(U, rows, cols);
    }
}

void gramSchmidt(double U[][10], int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double dot_product = 0;
            for (int k = 0; k < rows; k++)
            {
                dot_product += U[k][i] * U[k][j];
            }
            for (int k = 0; k < rows; k++)
            {
                U[k][i] -= dot_product * U[k][j];
            }
        }
        double norm = 0;
        for (int k = 0; k < rows; k++)
        {
            norm += U[k][i] * U[k][i];
        }
        norm = sqrt(norm);
        if (norm > 1e-10)
        {
            for (int k = 0; k < rows; k++)
            {
                U[k][i] /= norm;
            }
        }
        else
        {
            MatrixXd random_vector = MatrixXd::Random(rows, 1);
            for (int j = 0; j < i; j++)
            {
                double dot_product = 0;
                for (int k = 0; k < rows; k++)
                {
                    dot_product += random_vector(k, 0) * U[k][j];
                }
                for (int k = 0; k < rows; k++)
                {
                    random_vector(k, 0) -= dot_product * U[k][j];
                }
            }
            double random_norm = random_vector.norm();
            for (int k = 0; k < rows; k++)
            {
                U[k][i] = random_vector(k, 0) / random_norm;
            }
        }
    }
}

void tinhMatranV(MatrixXd vector, double V[][10])
{
    int row = vector.rows(), col = vector.cols();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            V[i][j] = vector(i, j);
        }
    }
}
void tinhMatranS(MatrixXd lambda, double sigma[][10], int rows, int cols)
{
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            sigma[i][j] = (i != j) ? 0 : sqrt(lambda(k, 0));
            if (i == j)
                k++;
        }
}

void computeApproximateMatrix(double A3[][10], double U[][10], double sigma[][10], double VT[][10], int rows, int cols, int k)
{
    // Khởi tạo ma trận kết quả về 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A3[i][j] = 0.0;
        }
    }
    
    for (int rank = 0; rank < k; rank++) {
        double sigma_val = sigma[rank][rank]; 
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                A3[i][j] += sigma_val * U[i][rank] * VT[rank][j];
            }
        }
    }
}

double frobeniusNorm(double A[][10], double B[][10], int rows, int cols)
{
    double sum = 0.0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double diff = A[i][j] - B[i][j];
            sum += diff * diff;
        }
    }
    
    return sqrt(sum);
}
