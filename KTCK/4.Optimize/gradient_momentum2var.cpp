#include <iostream>
#include <cmath>
#include <iomanip>
#define MAX_ITER 10000 
#define EPS 1e-5
using namespace std;

double objectiveFunction(double x, double y) {
    return x*x + y*y + 2*sin(x)*cos(y);
}

double gradientX(double x, double y) {
    return 2*x + 2*cos(x)*cos(y);
}

double gradientY(double x, double y) {
    return 2*y - 2*sin(x)*sin(y);
}

void optimizeMomentum(double gamma, double alpha, double x_init, double y_init) {
    double x = x_init;
    double y = y_init;
    double vx = 0.0;  // Velocity for x
    double vy = 0.0;  // Velocity for y
    int iterations = 0;
    
    cout << fixed << setprecision(6);
    cout << "Function: f(x,y) = x^2 + y^2 + 2*sin(x)*cos(y)" << endl;
    cout << "Initial point: (" << x << ", " << y << ")" << endl;
    cout << "Learning rate (gamma): " << gamma << endl;
    cout << "Momentum (alpha): " << alpha << endl;
    cout << "Convergence threshold: " << EPS << endl << endl;
    
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
        
        if (iterations % 100 == 0 || iterations <= 5) {
            cout << "Iter " << iterations << ": "
                 << "x = " << x << ", y = " << y 
                 << ", f(x,y) = " << objectiveFunction(x, y) << endl;
        }
        
        double diff = sqrt((x - x_prev)*(x - x_prev) + (y - y_prev)*(y - y_prev));
        if (diff < EPS) {
            cout << "\nConvergence reached after " << iterations << " iterations." << endl;
            cout << "Minimum value: " << objectiveFunction(x, y) << endl;
            cout << "At point: x = " << x << ", y = " << y << endl;
            return;
        }
    }
    
    cout << "\nMaximum iterations reached without convergence." << endl;
    cout << "Final point: x = " << x << ", y = " << y << endl;
    cout << "Function value: " << objectiveFunction(x, y) << endl;
}

int main() {
    double gamma = 0.01;    // Learning rate
    double alpha = 0.9;     // Momentum coefficient
    double x_init = 2.0;    // Initial x
    double y_init = 2.0;    // Initial y
    
    optimizeMomentum(gamma, alpha, x_init, y_init);
    return 0;
}