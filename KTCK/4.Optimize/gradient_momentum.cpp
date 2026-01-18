#include <iostream>
#include <cmath>
#define MAX_ITER 3000
#define eps 1e-5
using namespace std;

double function1(double x) {
    //if (fabs(35.0 - x) < 1e-10) return 1e18; // tránh chia cho 0
    return log(pow(2*x*x+1,2)) + 9*x  + 3*exp(x*x)-5;
   // return pow(1-2.0/exp(x),2);
   // return (exp(2*x) + 3*x*x + 8*x) / (35.0 - x) - 5*x;
}

//đạo hàm f'(x)
double gradFunc(double x) {
  //  return 2.0 * (1.0 - 2.0 / exp(x)) * (2.0 / exp(x));
    return 8.0*x/(2*x*x+1) +9 + 6.0*x*exp(x*x);  
    // return ((3.0f * expf(3.0f * x) + 24.0f * x + 5.0f) * (12.0f - 2.0f * x) + 2.0f * (expf(3.0f * x) + 12.0f * x * x + 5.0f * x)) / ((12.0f - 2.0f * x) * (12.0f - 2.0f * x)) - 25.0f;
}
void optimize(double gamma, double alpha, double x_init, 
              double (*objFunc)(double), double (*gradFunc)(double)) {
    double x = x_init;
    double v = 0.0; //vận tốc ban đầu
    int iterations = 0;
    
    while (iterations < MAX_ITER) {
        iterations++;
        double x_prev = x;
        v = alpha * v + gamma * gradFunc(x);
        x = x - v;
        if (iterations % 100 == 0 || iterations <= 5){
        cout << "Iter " << iterations << ": x = " << x 
             << ", f(x) = " << objFunc(x) 
             << ", f'(x) = " << gradFunc(x) << endl;
        }
        if (fabs(x - x_prev) < eps) {
            cout << "\nConverged after " << iterations << " iterations." << endl;
            cout << "Optimal x = " << x << ", f(x) = " << objFunc(x) << endl;
            break;
        }
    }
    
    if (iterations == MAX_ITER) {
        cout << "Reached maximum iterations without convergence." << endl;
        cout << "Optimal x = " << x << ", f(x) = " << objFunc(x) << endl;
    }
}

int main() {
    double gamma = 0.001; 
    double alpha = 0.5;  
    double x_init = -1.0000; 
    
    optimize(gamma, alpha, x_init, function1, gradFunc);
    return 0;
}