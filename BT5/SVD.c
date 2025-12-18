/*
  Pure C SVD implementation (no external libs)
  S = A^T * A -> eigen-decompose S = V * diag(eig) * V^T
  singular values = sqrt(eig)
  U columns: u_i = (1/sigma_i) * A * v_i
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static void print_matrix(const char* name, double* A, int rows, int cols) {
    printf("\n%s (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) printf("%10.6f ", A[i*cols + j]);
        printf("\n");
    }
}

static double norm_fro(double* A, int rows, int cols) {
    double s = 0.0;
    for (int i = 0; i < rows*cols; ++i) s += A[i]*A[i];
    return sqrt(s);
}

static void mat_mult(double* A, int arows, int acols, double* B, int brows, int bcols, double* C) {
    for (int i = 0; i < arows; ++i) for (int j = 0; j < bcols; ++j) {
        double s = 0.0;
        for (int k = 0; k < acols; ++k) s += A[i*acols + k] * B[k*bcols + j];
        C[i*bcols + j] = s;
    }
}

static void transpose(double* A, int nrows, int ncols, double* AT) {
    for (int i = 0; i < nrows; ++i) for (int j = 0; j < ncols; ++j) AT[j*nrows + i] = A[i*ncols + j];
}

// Jacobi eigenvalue algorithm for symmetric n x n matrix A
// Returns eigenvalues in 'eig' (length n) and eigenvectors as columns in 'V' (n x n)
// Both eig and V must be allocated by caller
static void jacobi_eigen(double* A, int n, double* eig, double* V) {
    double* B = (double*)malloc(n*n*sizeof(double));
    memcpy(B, A, n*n*sizeof(double));
    for (int i = 0; i < n*n; ++i) V[i] = (i/n == i%n) ? 1.0 : 0.0;

    const int max_iter = 100;
    const double eps = 1e-12;
    for (int iter = 0; iter < max_iter; ++iter) {
        int p=0,q=1; double maxv = 0.0;
        for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
            double val = fabs(B[i*n + j]);
            if (val > maxv) { maxv = val; p=i; q=j; }
        }
        if (maxv < eps) break;
        double App = B[p*n + p];
        double Aqq = B[q*n + q];
        double Apq = B[p*n + q];
        double phi = 0.5 * atan2(2*Apq, Aqq - App);
        double c = cos(phi), s = sin(phi);
        for (int k = 0; k < n; ++k) {
            double Bkp = B[k*n + p];
            double Bkq = B[k*n + q];
            B[k*n + p] = c*Bkp - s*Bkq;
            B[k*n + q] = s*Bkp + c*Bkq;
        }
        for (int k = 0; k < n; ++k) {
            double Bpk = B[p*n + k];
            double Bqk = B[q*n + k];
            B[p*n + k] = c*Bpk - s*Bqk;
            B[q*n + k] = s*Bpk + c*Bqk;
        }
        B[p*n + p] = c*c*App - 2*s*c*Apq + s*s*Aqq;
        B[q*n + q] = s*s*App + 2*s*c*Apq + c*c*Aqq;
        B[p*n + q] = B[q*n + p] = 0.0;
        for (int k = 0; k < n; ++k) {
            double Vkp = V[k*n + p];
            double Vkq = V[k*n + q];
            V[k*n + p] = c*Vkp - s*Vkq;
            V[k*n + q] = s*Vkp + c*Vkq;
        }
    }
    for (int i = 0; i < n; ++i) eig[i] = B[i*n + i];
    free(B);
}

static void sort_eig_desc(int n, double* eig, double* V) {
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (eig[i] < eig[j]) {
                double t = eig[i]; eig[i] = eig[j]; eig[j] = t;
                for (int r = 0; r < n; ++r) { double tmp = V[r*n + i]; V[r*n + i] = V[r*n + j]; V[r*n + j] = tmp; }
            }
        }
    }
}

int main(void) {
    // Example: 3x3 symmetric "ugly" matrix
    double A3[3*3] = {3,1,1, 1,3,1, 1,1,3};
    print_matrix("A3", A3, 3, 3);
    double AT3[3*3]; transpose(A3,3,3,AT3);
    double S3[3*3]; mat_mult(3, AT3, 3, A3, 3, 3, S3);
    print_matrix("S3 = A^T * A", S3, 3, 3);
    double eig3[3]; double V3[3*3]; jacobi_eigen(S3, 3, eig3, V3);
    sort_eig_desc(3, eig3, V3);
    for (int i = 0; i < 3; ++i) if (eig3[i] < 0) eig3[i] = 0.0;
    double sv3[3]; for (int i = 0; i < 3; ++i) sv3[i] = (eig3[i] > 0) ? sqrt(eig3[i]) : 0.0;
    printf("singular values: %f %f %f\n", sv3[0], sv3[1], sv3[2]);
    print_matrix("V (cols)", V3, 3, 3);

    double Sigma3[3*3]; memset(Sigma3,0,sizeof(Sigma3)); for (int i=0;i<3;++i) Sigma3[i*3+i]=sv3[i];
    double AV3[3*3]; mat_mult(3, A3, 3, V3, 3, 3, AV3);
    double Sigma_inv3[3*3]; memset(Sigma_inv3,0,sizeof(Sigma_inv3)); for (int i=0;i<3;++i) if (sv3[i]>1e-12) Sigma_inv3[i*3+i]=1.0/sv3[i];
    double U3[3*3]; mat_mult(3, AV3, 3, Sigma_inv3, 3, 3, U3);
    print_matrix("U3", U3, 3, 3);

    double VT3[3*3]; transpose(V3,3,3,VT3);
    double temp3[3*3]; mat_mult(3, U3, 3, Sigma3, 3, 3, temp3);
    double A3_rec[3*3]; mat_mult(3, temp3, 3, VT3, 3, 3, A3_rec);
    print_matrix("A3_reconstructed", A3_rec, 3, 3);
    printf("reconstruction error (Frobenius norm of difference): %e\n", norm_fro(A3_rec,3,3) - norm_fro(A3,3,3));

    return 0;
}
