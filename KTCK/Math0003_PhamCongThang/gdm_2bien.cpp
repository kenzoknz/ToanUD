#include <iostream>
#include <cmath>
#include <iomanip>
#define MAX_ITER 1000 
#define EPS 1e-6
using namespace std;


double objectiveFunction(double x, double y) {
    double term1 = x*x + y - 11.0;
    double term2 = x + y*y - 7.0;
    return term1*term1 + term2*term2;
}

double gradientX(double x, double y) {
    double term1 = x*x + y - 11.0;
    double term2 = x + y*y - 7.0;
    return 4.0*x*term1 + 2.0*term2;
}
double gradientY(double x, double y) {
    double term1 = x*x + y - 11.0;
    double term2 = x + y*y - 7.0;
    return 2.0*term1 + 4.0*y*term2;
}

void optimizeMomentum(double gamma, double alpha, double x_init, double y_init) {
    double x = x_init;
    double y = y_init;
    double vx = 0.0;  // Velocity for x
    double vy = 0.0;  // Velocity for y
    int iterations = 0;
    
    cout << fixed << setprecision(8);
    cout << "Initial point: (x=" << x << ", y=" << y << ")" << endl;
    cout << "Learning rate (gamma): " << gamma << endl;
    cout << "Momentum (alpha): " << alpha << endl;
    cout << "Max iterations: " << MAX_ITER << endl;
    cout << "Convergence threshold (epsilon): " << EPS << endl << endl;
    
    while (iterations < MAX_ITER) {
        iterations++;
        double x_prev = x;
        double y_prev = y;
        
        double grad_x = gradientX(x, y);
        double grad_y = gradientY(x, y);
        
        vx = alpha * vx - gamma * grad_x;
        vy = alpha * vy - gamma * grad_y;
        
        x = x + vx;
        y = y + vy;
        
        if (iterations % 100 == 0 || iterations <= 10) {
            cout << "Iter " << setw(5) << iterations << ": "
                 << "x = " << setw(12) << x 
                 << ", y = " << setw(12) << y 
                 << ", f(x,y) = " << setw(15) << objectiveFunction(x, y) << endl;
        }
        
        // Kiểm tra hội tụ
        double diff = sqrt((x - x_prev)*(x - x_prev) + (y - y_prev)*(y - y_prev));
        if (diff < EPS) {
            cout << "\nConvergence reached after " << iterations << " iterations." << endl;
            cout << "Minimum value: " << objectiveFunction(x, y) << endl;
            cout << "At point: (x = " << x << ", y = " << y << ")" << endl;

            return;
        }
    }
    
    cout << "\nMaximum iterations reached without convergence." << endl;
    cout << "Final point: (x = " << x << ", y = " << y << ")" << endl;
    cout << "Function value: " << objectiveFunction(x, y) << endl;

}

int main() {
    
    double gamma = 0.001;      // Learning rate
    double alpha = 0.1;        // Momentum coefficient
    double x_init = 0.0;       // Initial x
    double y_init = 0.0;       // Initial y
    cout << "- Phuong phap: Gradient Descent with Momentum" << endl;
    cout << "- Tham so hoc (learning rate) γ = " << gamma << endl;
    cout << "- He so dong luong (momentum coefficient) α = " << alpha << endl << endl;
    
    optimizeMomentum(gamma, alpha, x_init, y_init);
  
    return 0;
}