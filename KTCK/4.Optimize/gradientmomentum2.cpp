#include <iostream>
#include <cmath>
#define gamma 0.001
#define N 1000
#define alpha 0.1
#define e 0.00001

using namespace std;

// Hàm số: f(x) = (2e^(2x) + 4x^2 + 4x)/(25 - x) - 15x
double function(double x) {
    return (2*exp(2*x) + 4*x*x + 4*x) / (25 - x) - 15*x;
}

double grad(double x) {
    double u = 2*exp(2*x) + 4*x*x + 4*x;        // u(x)
    double uprime = 4*exp(2*x) + 8*x + 4;       // u'(x)
    double v = 25 - x;                          // v(x)
    
    return (uprime * v + u) / (v * v) - 15;
}

double GradientDescentWithMomentum(double x) {
    double v = 0;           // momentum term
    double x_new = 0;
    
    for(int i = 1; i < N; i++) {
        // Công thức momentum: v_t = α * v_{t-1} + γ * ∇f(x_t)
        // Cập nhật x: x_{t+1} = x_t - v_t
        v = alpha * v + gamma * grad(x);
        x_new = x - v;
        
        cout << "Iter " << i << ": v = " << v << "; x = " << x_new 
             << "; f(x) = " << function(x_new) << "; grad = " << grad(x) << endl;
        
        // Điều kiện dừng khi thay đổi x quá nhỏ
        if(abs(x_new - x) < e) {
            cout << "\nConverged after " << i << " iterations." << endl;
            return x_new;
        }
        x = x_new;
    }
    
    cout << "\nReached maximum iterations." << endl;
    return x;
}

int main() {
    double x = 0; // điểm khởi đầu
    
    cout << "=== Gradient Descent with Momentum ===" << endl;
    cout << "Learning rate (γ) = " << gamma << endl;
    cout << "Momentum (α) = " << alpha << endl;
    cout << "Starting point x0 = " << x << endl;
    cout << "f(x0) = " << function(x) << endl;
    cout << "f'(x0) = " << grad(x) << endl << endl;
    
    double minimum = GradientDescentWithMomentum(x);
    
    cout << "\n=== Results ===" << endl;
    cout << "X_min = " << minimum << endl;
    cout << "Y_min = f(X_min) = " << function(minimum) << endl;
    
    return 0;
}