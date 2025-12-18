#include <iostream>
#include <cmath>
#include <iomanip>
#define MAX_ITER 1000
#define EPSILON 1e-6

using namespace std;

float objectiveFunction( float x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

 float derivative( float x) {
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}
// Gradient Descent với Momentum
void gradientDescentMomentum(double gamma, double alpha, double x_init) {
    cout << "Learning rate (gamma): " << gamma << endl;
    cout << "Momentum (alpha): " << alpha << endl;
    cout << "Initial point: x = " << x_init << endl << endl;
    
    double x = x_init;
    double v = 0.0;  
    int iterations = 0;
    
    cout << fixed << setprecision(6);
    cout << "Iter\t\tx\t\tf(x)\t\tv\t\tf'(x)" << endl;
    cout << string(75, '-') << endl;
    
    while (iterations < MAX_ITER) {
        double grad = derivative(x);
        v = alpha * v + (1 - alpha) * grad;
        double x_new = x - gamma * v;
        
        if (true) {
            cout << iterations << "\t\t" << x << "\t" << objectiveFunction(x) 
                 << "\t" << v << "\t" << grad << endl;
        }
        
        if (fabs(x_new - x) < EPSILON) {
            cout << string(75, '-') << endl;
            cout << "Convergence reached after " << iterations + 1 << " iterations." << endl;
            cout << "Minimum value: " << objectiveFunction(x_new) << endl;
            cout << "At point: x = " << x_new << endl;
            return;
        }
        
        x = x_new;
        iterations++;
    }
    
    cout << string(75, '-') << endl;
    cout << "Maximum iterations reached: " << MAX_ITER << endl;
    cout << "Minimum value: " << objectiveFunction(x) << endl;
    cout << "At point: x = " << x << endl;
}

int main() {
    // Tham số
    double gamma = 0.001;   // Learning rate
    double alpha = 0.01;     // Momentum
    double x_init = -1.0;   // Điểm khởi đầu
    
    gradientDescentMomentum(gamma, alpha, x_init);

    return 0;
}
