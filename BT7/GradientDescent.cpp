#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

 float function1( float x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

 float derivativeFunction1( float x) {
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}

float SGD(float x_init, float learning_rate, int epochs, float (*gradFunc)(float), float (*objFunc)(float)) {
    float x = x_init;

    for (int i = 1; i <= epochs; ++i) {
        float x_prev = x;
        x = x - learning_rate * gradFunc(x);
        cout << "Iteration " << i << ": x = " << x << ", function value = " << objFunc(x) << endl;
        if (fabs(x - x_prev) < 1e-5) {
            cout << "Convergence reached after " << i << " iterations." << endl;
            break;
        }
        if (i >= epochs) {
            cout << "Maximum number of iterations reached." << endl;
            break;
        }
    }
    return objFunc(x);
}

int main() {
    float x_initial = -1.0; 
    float learning_rate = 0.001; 
    int epochs = 1000;  
    cout << "Result of SGD: " << SGD(x_initial, learning_rate, epochs, derivativeFunction1, function1) << endl;
    return 0;
}
