#include <iostream>
#include <cmath>

using namespace std;

constexpr double EPSILON = 1e-5;
constexpr int MAX_ITERATIONS = 1000;

double function(double x) {
    return 2*log(2*x*x + 1) + 9*x + 3*exp(x*x) - 5;
}

double derivativeFunction(double x) {
    return (8*x)/(2*x*x + 1) + 9 + 6*x*exp(x*x);
}

double function1(double x) {
    // Check for division by zero
    if (abs(12 - 2*x) < 1e-12) {
        cout << "Warning: Division by zero at x = " << x << endl;
        return 1e20; // Return large value to indicate problem
    }
    return (exp(3*x) + 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

double derivativeFunction1(double x) {
    // Check for division by zero
    if (abs(12 - 2*x) < 1e-12) {
        cout << "Warning: Division by zero in derivative at x = " << x << endl;
        return 1e20; // Return large value to indicate problem
    }
    
    double numerator = exp(3*x) + 12*x*x + 5*x;
    double denominator = 12 - 2*x;
    double numerator_deriv = 3*exp(3*x) + 24*x + 5;
    double denominator_deriv = -2;
    
    // Using quotient rule: (u/v)' = (u'v - uv')/v^2
    double quotient_deriv = (numerator_deriv * denominator - numerator * denominator_deriv) / (denominator * denominator);
    
    return quotient_deriv - 25;
}

void newtonRaphson(double (*func)(double), double (*derivFunc)(double), double initial_guess) {
    double x = initial_guess;
    int iterations = 0;
    
    cout << "Starting Newton-Raphson method with initial guess: " << x << endl;
    cout << "Initial function value: " << func(x) << endl;
    cout << "Initial derivative value: " << derivFunc(x) << endl;

    while (iterations < MAX_ITERATIONS) {
        double fx = func(x);
        double dfx = derivFunc(x);
        
        // Check if derivative is too small (near zero)
        if (abs(dfx) < 1e-12) {
            cout << "Derivative is too small at iteration " << iterations << ". Method may not converge." << endl;
            break;
        }
        
        double h = fx / dfx;
        double x_new = x - h;
        iterations++;
        
        cout << "Iteration " << iterations << ": x = " << x_new 
             << ", func(x) = " << fx 
             << ", derivFunc(x) = " << dfx 
             << ", h = " << h << endl;
             
        // Check convergence
        if (abs(h) < EPSILON) {
            cout << "Convergence achieved after " << iterations << " iterations." << endl;
            cout << "The root of the function is approximately: " << x_new << endl;
            return;
        }
        
        // Check if function value is small enough
        if (abs(fx) < EPSILON) {
            cout << "Function value is close to zero after " << iterations << " iterations." << endl;
            cout << "The root of the function is approximately: " << x_new << endl;
            return;
        }
        
        x = x_new;
    }
    
    cout << "The method did not converge within " << MAX_ITERATIONS << " iterations." << endl;
    cout << "Final approximation: " << x << endl;
}

int main() {
    cout << "Newton-Raphson Method for solving equations" << endl;
    cout << "Function: (exp(3*x) + 12*x^2 + 5*x)/(12 - 2*x) - 25*x = 0" << endl;
    cout << "Enter initial guess: ";
    
    double initial_guess;
    cin >> initial_guess;
    
    cout << "Input received: " << initial_guess << endl;
    
    // Check if initial guess makes denominator zero
    if (abs(12 - 2*initial_guess) < 1e-12) {
        cout << "Error: Initial guess makes denominator zero (x = 6). Please choose a different value." << endl;
        return 1;
    }
    
    // Test function evaluation
    cout << "Testing function evaluation..." << endl;
    double test_val = function1(initial_guess);
    cout << "f(" << initial_guess << ") = " << test_val << endl;
    
    double test_deriv = derivativeFunction1(initial_guess);
    cout << "f'(" << initial_guess << ") = " << test_deriv << endl;
    
    cout << "\nStarting Newton-Raphson iterations..." << endl;
    newtonRaphson(function1, derivativeFunction1, initial_guess);
    return 0;
}
