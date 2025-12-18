#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <vector>
using namespace std;

// ---------------- GOLDEN SECTION SEARCH ----------------
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

// ---------------- POWELL METHOD ----------------
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
                double diffNorm = sqrt(pow(Y[0] - X[0], 2) + pow(Y[1] - X[1], 2) + pow(Y[2] - X[2], 2));
                if (diffNorm < tol)
                {
                    doLoop = false;
                }
            }
        }
    }
    return X;
}

// ---------------- PROBLEM DEFINITION ----------------
// f(x, y, z) = x² + y² + z² - 0.5 * ln(1 + x² + y² + z²)
double objectiveFunction(double x, double y, double z)
{
    double r2 = x * x + y * y + z * z;
    return r2 - 0.5 * log(1 + r2);
}

// h(x, y, z) = x² + y + z - 2 = 0
double constraintFunction(double x, double y, double z)
{
    return x * x + y + z - 2;
}

// ---------------- AUGMENTED LAGRANGIAN METHOD ----------------
void augmentedLagrangianMethod()
{
    int iteration = 1;
    double lambda = 0.0;
    double r = 1.0; // penalty parameter starts at 1
    double x = 1.0, y = 1.0, z = 1.0;
    double tol = 1e-5;
    int maxIter = 100;

    cout << "=== AUGMENTED LAGRANGIAN METHOD ===" << endl;
    cout << "Objective: f(x,y,z) = x² + y² + z² - 0.5*ln(1+x²+y²+z²)" << endl;
    cout << "Constraint: h(x,y,z) = x² + y + z - 2 = 0" << endl;
    cout << "Start point: (" << x << ", " << y << ", " << z << ")" << endl << endl;

    while (iteration <= maxIter)
    {
        // Augmented Lagrangian
        auto Afunc = [&](double x1, double x2, double x3)
        {
            double f_val = objectiveFunction(x1, x2, x3);
            double h_val = constraintFunction(x1, x2, x3);
            return f_val + lambda * h_val + (r / 2.0) * h_val * h_val;
        };

        vector<double> X0 = {x, y, z};
        vector<double> Xopt = powellMethod(Afunc, X0, 1e-6);

        x = Xopt[0];
        y = Xopt[1];
        z = Xopt[2];

        double h_val = constraintFunction(x, y, z);
        double f_val = objectiveFunction(x, y, z);

        cout << "Iter " << setw(3) << iteration
             << " | lambda = " << setw(10) << setprecision(6) << lambda
             << " | r = " << setw(8) << r
             << " | h(x) = " << setw(10) << h_val
             << " | f(x) = " << setw(12) << f_val << endl;

        // Kiểm tra hội tụ
        if (fabs(h_val) < tol)
        {
            cout << "\nConverged after " << iteration << " iterations." << endl;
            cout << "Optimal point: (" << x << ", " << y << ", " << z << ")" << endl;
            cout << "Constraint violation: " << h_val << endl;
            cout << "Objective value: " << f_val << endl;
            return;
        }

        // Update λ và r (r tăng dần đều)
        lambda = lambda + r * h_val;
        r = r + 1.0; // tăng nhẹ mỗi lần

        iteration++;
    }

    cout << "\n⚠️ Maximum iterations reached without convergence." << endl;
}

// ---------------- MAIN ----------------
int main()
{
    augmentedLagrangianMethod();
    return 0;
}
