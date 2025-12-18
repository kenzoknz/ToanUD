#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <vector>
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
    vector<vector<double>> directions = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<double> X = iniGuess;
    vector<double> X_prev = X;

    int n = directions.size();
    double searchRange[] = {-5, 5};

    for (int iter = 0; iter < maxIter; ++iter)
    {
        X_prev = X;

        for (int q = 0; q < n; ++q)
        {
            auto func_gS = [&](double alpha)
            {
                return func(X[0] + alpha * directions[q][0],
                            X[1] + alpha * directions[q][1],
                            X[2] + alpha * directions[q][2]);
            };
            double alphaOpt = goldenSection(func_gS, searchRange[0], searchRange[1]);
            for (int i = 0; i < 3; i++)
                X[i] += alphaOpt * directions[q][i];
        }

        // Cập nhật hướng mới (Powell)
        vector<double> newDir(3);
        for (int i = 0; i < 3; i++)
            newDir[i] = X[i] - X_prev[i];
        double normNew = sqrt(newDir[0] * newDir[0] + newDir[1] * newDir[1] + newDir[2] * newDir[2]);
        if (normNew > 0)
        {
            for (int i = 0; i < 3; i++)
                newDir[i] /= normNew;
            directions.erase(directions.begin());
            directions.push_back(newDir);
        }

        double diffNorm = sqrt(pow(X[0] - X_prev[0], 2) + pow(X[1] - X_prev[1], 2) + pow(X[2] - X_prev[2], 2));
        if (diffNorm < tol)
            break;
    }

    return X;
}

double objectiveFunction(double x, double y, double z)
{
    double r2 = x * x + y * y + z * z;
    return r2 - 0.5 * log(1 + r2);
}

double constraintFunction(double x, double y, double z)
{
    return x * x + y + z - 2;
}

void augmentedLagrangianMethod()
{
    double lambda = 0.0, r = 1.0;
    double x = 1, y = 1, z = 1;
    double tol = 1e-5;
    double h_prev = 0;
    int maxIter = 100;

    cout << "Starting Augmented Lagrangian Method:\n";
    cout << "f(x,y,z) = x² + y² + z² - (1/2)*ln(1+x²+y²+z²)\n";
    cout << "h(x,y,z) = x² + y + z - 2 = 0\n\n";

    for (int iteration = 1; iteration <= maxIter; iteration++)
    {
        auto Afunc = [&](double x1, double x2, double x3) -> double
        {
            double f = objectiveFunction(x1, x2, x3);
            double h = constraintFunction(x1, x2, x3);
            return f + lambda * h + (r / 2.0) * h * h;
        };

        vector<double> minX = powellMethod(Afunc, {x, y, z}, 1e-6);
        x = minX[0];
        y = minX[1];
        z = minX[2];

        double h_val = constraintFunction(x, y, z);

        cout << "Iter " << iteration << ": λ = " << lambda
             << ", r = " << r
             << ", (x,y,z) = (" << x << ", " << y << ", " << z << ")"
             << ", h = " << h_val << endl;

        if (fabs(h_val) < tol)
        {
            cout << "\nConverged after " << iteration << " iterations.\n";
            cout << "Optimal point: (" << x << ", " << y << ", " << z << ")\n";
            cout << "Constraint violation: " << h_val << endl;
            cout << "Objective value: " << objectiveFunction(x, y, z) << endl;
            return;
        }

        lambda += r * h_val;
        double gamma_r = 10.0;
        double penaltyMax = 1e6;
        r *= gamma_r;
        if (r > penaltyMax)
            r = penaltyMax;

        h_prev = h_val;
    }

    cout << "\nReached max iterations without convergence.\n";
}

int main()
{
    augmentedLagrangianMethod();
    return 0;
}
