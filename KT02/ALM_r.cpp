#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
double goldenSection(const function<double(double)> &func, double a, double b, double tol = 1e-6)
{
    const double gr = (sqrt(5) + 1) / 2;
    double c = b - (b - a) / gr;
    double d = a + (b - a) / gr;
    while (fabs(c - d) > tol)
    {
        if (func(c) < func(d))
            b = d;
        else
            a = c;
        c = b - (b - a) / gr;
        d = a + (b - a) / gr;
    }
    return (b + a) / 2;
}
vector<double> powellMethod(const function<double(double, double, double)> &func,
                            vector<double> iniGuess, double tol, int maxIter = 100)
{
    int count = 1;
    double searchRange[] = {-1, 1};
    vector<vector<double>> directions = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<double> X = iniGuess;
    vector<double> Y = X;
    int n = directions.size();
    bool doLoop = true;
    while (doLoop && count <= maxIter)
    {
        for (int q = 0; q < n; ++q)
        {
            auto func_gS = [&](double alphaValue)
            {
                return func(X[0] + alphaValue * directions[q][0], 
                           X[1] + alphaValue * directions[q][1],
                           X[2] + alphaValue * directions[q][2]);
            };
            double alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
            X[0] += alphaOpti * directions[q][0];
            X[1] += alphaOpti * directions[q][1];
            X[2] += alphaOpti * directions[q][2];
            if (q == n - 1)
            {
                count++;
                vector<double> newDir = {X[0] - Y[0], X[1] - Y[1], X[2] - Y[2]};
                double normNewDir = sqrt(newDir[0] * newDir[0] + newDir[1] * newDir[1] + newDir[2] * newDir[2]);
                if (normNewDir > 0)
                {
                    directions.push_back({newDir[0] / normNewDir, newDir[1] / normNewDir, newDir[2] / normNewDir});
                    directions.erase(directions.begin());
                }
                Y = X;
                alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
                X[0] += alphaOpti * directions[q][0];
                X[1] += alphaOpti * directions[q][1];
                X[2] += alphaOpti * directions[q][2];
                double diffNorm = sqrt(pow(Y[0] - X[0], 2) + pow(Y[1] - X[1], 2) + pow(Y[2] - X[2], 2));
                if (diffNorm < tol)
                {
                    doLoop = false;
                }
            }
            if (count == maxIter)
            {
                directions = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
                count = 1;
                break;
            }
        }
    }
    if (count > maxIter)
    {
        cout << "No solution found after " << maxIter << " iterations" << endl;
        return {};
    }
    return X;
}
// Objective function: f(x,y,z) = x² + y² + z² - (1/2)*ln(1+x²+y²+z²)
double objectiveFunction(double x, double y, double z) {
    double r2 = x*x + y*y + z*z;
    return r2 - 0.5 * log(1 + r2);
}

// Constraint function: h(x,y,z) = x² + y + z - 2 = 0
double constraintFunction(double x, double y, double z) {
    return x*x + y + z - 2;
}

void augmentedLagrangianMethod()
{
    int iteration = 1;
    double lambda = 0;
    double r = 1;
    double x = 1, y = 1, z = 1; // Starting point
    double tol = 1e-5;
    int maxIter = 100;
    
    cout << "Starting Augmented Lagrangian Method for problem:" << endl;
    cout << "f(x,y,z) = x² + y² + z² - (1/2)*ln(1+x²+y²+z²)" << endl;
    cout << "h(x,y,z) = x² + y + z - 2 = 0" << endl;
    cout << "Starting point: (" << x << ", " << y << ", " << z << ")" << endl << endl;

    while (iteration <= maxIter)
    {
        // Define augmented Lagrangian function
        auto Afunc = [&](double x1, double x2, double x3) -> double {
            double f_val = objectiveFunction(x1, x2, x3);
            double h_val = constraintFunction(x1, x2, x3);
            return f_val + lambda * h_val + (r / 2) * h_val * h_val;
        };

        vector<double> x0 = {x, y, z};
        vector<double> minX;
        
        minX = powellMethod(Afunc, x0, 1e-6);

        if (minX.empty()) {
            cout << "Powell method failed to find a solution." << endl;
            return;
        }

        x = minX[0]; y = minX[1]; z = minX[2];
        double h_val = constraintFunction(x, y, z);

        cout << "iter " << iteration << ": lambda = " << fixed << setprecision(6) << lambda;
        cout << ", r = " << r << ", x y z = " << x << " " << y << " " << z;
        cout << " and h = " << h_val << endl;

        if (abs(h_val) < tol) {
            cout << "\nConverged after " << iteration << " iterations" << endl;
            cout << "Optimal point: (" << x << ", " << y << ", " << z << ")" << endl;
            cout << "Constraint violation: " << h_val << endl;
            cout << "Objective function value: " << objectiveFunction(x, y, z) << endl;
            return;
        }

        // Update lambda and r
        lambda = lambda + r * h_val;
        if (abs(h_val) > 0.25 * abs(constraintFunction(x, y, z)))
            r = 10 * r;

        iteration++;
    }
    
    cout << "Maximum iterations reached without convergence" << endl;
}
int main()
{
    augmentedLagrangianMethod();
    return 0;
}