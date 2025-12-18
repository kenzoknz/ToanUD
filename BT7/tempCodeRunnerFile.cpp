#include <iostream>
#include <cmath>
#define max 1000 
#define eps 1e-5
using namespace std;
double function1(double x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

double derivativeFunction1(double x) {
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}

void optimize(double gamma, double alpha, double x_init, double (*objFunc)(double), double (*gradFunc)(double)) {
    double x = x_init;
    double v = 0.0; 
    int iterations = 0;
    while (iterations < max) {
        iterations++;
        double x_prev = x;
        v = alpha * v + (1 - alpha) * gradFunc(x);
        x = x - gamma * v;
        cout << "Objective function value at iteration " << iterations << ": x = " << x << ", function value = " << objFunc(x) << endl;
        if (fabs(x - x_prev) < 1e-5) {
            cout << "Optimization of the objective function completed." << endl;
            cout << "Optimal value of x: " << objFunc(x) << endl;
            break;
        }
    }
    if (iterations == max) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
}

int main() {
    double gamma = 0.001; 
    double alpha = 0.01;  
    double x_init = -2.0; 
    optimize(gamma, alpha, x_init, function1, derivativeFunction1);
    return 0;
}
