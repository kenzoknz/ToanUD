#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#define max 30000
#define eps 1e-5
using namespace std;

double objectiveFunction(const vector<double> &vars)
{
    double x = vars[0];
    double y = vars[1];
    double z = vars[2];
    return (x * x + y * y + z * z) / 2.0 + 3.0 * sin(x + y) / 10.0 + 3.0 * cos(y + z) / 10.0 + 1.0 / (1.0 + x * x + y * y + z * z);
}

vector<double> computeGradient(const vector<double> &vars)
{
    double x = vars[0];
    double y = vars[1];
    double z = vars[2];

    vector<double> gradient(3);
    double denominator = 1.0 + x * x + y * y + z * z;
    gradient[0] = x + 3.0 * cos(x + y) / 10.0 - 2.0 * x / (denominator * denominator);
    gradient[1] = y + 3.0 * cos(x + y) / 10.0 - 3.0 * sin(y + z) / 10.0 - 2.0 * y / (denominator * denominator);
    gradient[2] = z - 3.0 * sin(y + z) / 10.0 - 2.0 * z / (denominator * denominator);

    return gradient;
}

void optimizeMomentum(double gamma, double beta, const vector<double> &x_init)
{
    vector<double> x = x_init;
    vector<double> v(3, 0.0);
    int iterations = 0;

    while (iterations < max)
    {
        iterations++;
        vector<double> x_prev = x;
        vector<double> gradient = computeGradient(x);

        //  v = βv + γ∇f(x), x = x - v
        for (int i = 0; i < 3; i++)
        {
            v[i] = beta * v[i] + gamma * gradient[i];
            x[i] = x[i] - v[i];
        }

        double func_value = objectiveFunction(x);

        cout << "Objective function value at iteration " << iterations
             << ": x = " << setprecision(6) << fixed << x[0]
             << ", y = " << x[1]
             << ", z = " << x[2]
             << ", function value = " << func_value << endl;

        double norm_diff = 0.0;
        for (int i = 0; i < 3; i++)
        {
            norm_diff += (x[i] - x_prev[i]) * (x[i] - x_prev[i]);
        }
        norm_diff = sqrt(norm_diff);

        if (norm_diff < eps)
        {
            cout << "Convergence reached after " << iterations << " iterations." << endl;
            cout << "Minimum value: " << setprecision(8) << fixed << func_value << endl;
            cout << "At point: x = " << setprecision(8) << fixed << x[0]
                 << ", y = " << x[1] << ", z = " << x[2] << endl;
            return;
        }
    }

    if (iterations == max)
    {
        double func_value = objectiveFunction(x);
        cout << "Maximum iterations reached (" << max << ")." << endl;
        cout << "Minimum value: " << setprecision(8) << fixed << func_value << endl;
        cout << "At point: x = " << setprecision(8) << fixed << x[0]
             << ", y = " << x[1] << ", z = " << x[2] << endl;
    }
}

int main()
{
    double gamma = 0.01;
    double beta = 0.9;   
    vector<double> x_init = {1.0, 1.0, 1.0};

    cout << "Function: f(x,y,z) = (x²+y²+z²)/2 + 3*sin(x+y)/10 + 3*cos(y+z)/10 + 1/(1+x²+y²+z²)" << endl;
    cout << "Initial point: (" << x_init[0] << ", " << x_init[1] << ", " << x_init[2] << ")" << endl;
    cout << "Learning rate (gamma): " << gamma << endl;
    cout << "Momentum coefficient (beta): " << beta << endl;
    cout << "Convergence tolerance: " << eps << endl
         << endl;

    optimizeMomentum(gamma, beta, x_init);

    return 0;
}
