#include <iostream>
#include <cmath>
#include <iomanip>
#define MAX_ITER 5000 
#define EPS 1e-5
using namespace std;


double objectiveFunction(double y, double z) {
    if (z >= y) {
        double val = z - z*y + log10(1.0 + exp(-z*z));
        return fabs(val);
    } else {
        double val = -z*y + log10(exp(z*z) + 1.0);
        return fabs(val);
    }
}

double gradientY(double y, double z) {
    double inner;
    if (z >= y) {
        inner = z - z*y + log10(1.0 + exp(-z*z));
    } else {
        inner = -z*y + log10(exp(z*z) + 1.0);
    }
    double sign = (inner >= 0) ? 1.0 : -1.0;
    return sign * (-z);
}

double gradientZ(double y, double z) {
    const double ln10 = log(10.0);
    double inner, dg_dz;
    
    if (z >= y) {
        inner = z - z*y + log10(1.0 + exp(-z*z));
        double exp_term = exp(-z*z);
        dg_dz = 1.0 - y - (2.0*z / ln10) * exp_term / (1.0 + exp_term);
    } else {
        inner = -z*y + log10(exp(z*z) + 1.0);
        double exp_term = exp(z*z);
        dg_dz = -y + (2.0*z / ln10) * exp_term / (exp_term + 1.0);
    }
    
    double sign = (inner >= 0) ? 1.0 : -1.0;
    return sign * dg_dz;
}

void optimizeMomentum(double gamma, double alpha, double y_init, double z_init) {
    double y = y_init;
    double z = z_init;
    double vy = 0.0;  // Velocity for y
    double vz = 0.0;  // Velocity for z
    int iterations = 0;
    
    
    cout << "Function: f(y,z)" << endl;
    cout << "  if z >= y: |z - zy + log10(1 + e^(-z^2))|" << endl;
    cout << "  if z < y:  |-zy + log10(e^(z^2) + 1)|" << endl << endl;
    cout << "Initial point: (y=" << y << ", z=" << z << ")" << endl;
    cout << "Learning rate (gamma): " << gamma << endl;
    cout << "Momentum (alpha): " << alpha << endl;
    cout << "Convergence threshold: " << EPS << endl << endl;
    
    while (iterations < MAX_ITER) {
        iterations++;
        double y_prev = y;
        double z_prev = z;
        
        double grad_y = gradientY(y, z);
        double grad_z = gradientZ(y, z);
        
        vy = alpha * vy - gamma * grad_y;
        vz = alpha * vz - gamma * grad_z;
        
        y = y + vy;
        z = z + vz;
        
        if (iterations % 100 == 0 || iterations <= 10) {
            cout << "Iter " << setw(5) << iterations << ": "
                 << "y = " << setw(12) << y << ", z = " << setw(12) << z 
                 << ", f(y,z) = " << setw(12) << objectiveFunction(y, z) << endl;
        }
        
        // Kiểm tra hội tụ
        double diff = sqrt((y - y_prev)*(y - y_prev) + (z - z_prev)*(z - z_prev));
        if (diff < EPS) {
            cout << "\n✓ Convergence reached after " << iterations << " iterations." << endl;
            cout << "Minimum value: " << objectiveFunction(y, z) << endl;
            cout << "At point: y = " << y << ", z = " << z << endl;
            return;
        }
    }
    
    cout << "\n Maximum iterations reached without convergence." << endl;
    cout << "Final point: y = " << y << ", z = " << z << endl;
    cout << "Function value: " << objectiveFunction(y, z) << endl;
}

int main() {
    
    double gamma = 0.0001;    // Learning rate
    double alpha = 0.4;     // Momentum coefficient
    double y_init = 0.06;    // Initial y
    double z_init = 0.06;    // Initial z
    optimizeMomentum(gamma, alpha, y_init, z_init);

    
    return 0;
}