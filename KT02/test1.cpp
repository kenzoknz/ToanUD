#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define MAX_INNER_ITERATIONS 10000
#define MAX_OUTER_ITERATIONS 100
#define INNER_EPS 1e-6 // Convergence tolerance for the inner loop (gradient norm)
#define OUTER_EPS 1e-5 // Convergence tolerance for the constraint h(x,y,z) = 0

using namespace std;

// Objective function f(x,y,z)
double objectiveFunction(const vector<double> &vars) {
    double x = vars[0];
    double y = vars[1];
    double z = vars[2];
    double sum_sq = x * x + y * y + z * z;
    return sum_sq - 0.5 * log(1.0 + sum_sq);
}

// Constraint function h(x,y,z)
double constraintFunction(const vector<double> &vars) {
    double x = vars[0];
    double y = vars[1];
    double z = vars[2];
    return x * x + y + z - 2.0;
}

// Gradient of objective function f
vector<double> grad_f(const vector<double> &vars) {
    double x = vars[0];
    double y = vars[1];
    double z = vars[2];
    double sum_sq = x * x + y * y + z * z;
    double denom = 1.0 + sum_sq;

    vector<double> gradient(3);
    gradient[0] = 2.0 * x - x / denom;
    gradient[1] = 2.0 * y - y / denom;
    gradient[2] = 2.0 * z - z / denom;
    return gradient;
}

// Gradient of constraint function h
vector<double> grad_h(const vector<double> &vars) {
    vector<double> gradient(3);
    gradient[0] = 2.0 * vars[0]; // ∂h/∂x = 2x
    gradient[1] = 1.0;           // ∂h/∂y = 1
    gradient[2] = 1.0;           // ∂h/∂z = 1
    return gradient;
}

// Gradient of the Augmented Lagrangian L_A
vector<double> grad_LA(const vector<double> &vars, double lambda, double r) {
    vector<double> grad_f_val = grad_f(vars);
    vector<double> grad_h_val = grad_h(vars);
    double h_val = constraintFunction(vars);

    vector<double> grad_LA_val(3);
    for (int i = 0; i < 3; ++i) {
        grad_LA_val[i] = grad_f_val[i] + (lambda + r * h_val) * grad_h_val[i];
    }
    return grad_LA_val;
}

// Inner loop optimization using Gradient Descent with Momentum
vector<double> optimizeInner(vector<double> &vars_init, double lambda, double r, double inner_gamma, double inner_beta) {
    vector<double> x = vars_init;
    vector<double> v(3, 0.0); // Momentum vector
    
    for (int iter = 0; iter < MAX_INNER_ITERATIONS; ++iter) {
        vector<double> x_prev = x;
        vector<double> gradient_LA = grad_LA(x, lambda, r);

        // Update momentum
        for (int i = 0; i < 3; ++i) {
            v[i] = inner_beta * v[i] + (1.0 - inner_beta) * gradient_LA[i];
        }
        // Update variables
        for (int i = 0; i < 3; ++i) {
            x[i] = x[i] - inner_gamma * v[i];
        }

        // Check for inner loop convergence (norm of change in x)
        double norm_diff_x = 0.0;
        for (int i = 0; i < 3; ++i) {
            norm_diff_x += (x[i] - x_prev[i]) * (x[i] - x_prev[i]);
        }
        if (sqrt(norm_diff_x) < INNER_EPS * 0.1) { // A stricter inner loop convergence
            // Alternative: check norm of gradient
            double grad_norm = 0.0;
            for(double g_val : gradient_LA) {
                grad_norm += g_val * g_val;
            }
            if (sqrt(grad_norm) < INNER_EPS) break; 
        }
    }
    return x;
}

int main() {
    // Initial guess for x, y, z
    vector<double> vars = {1.0, 1.0, 1.0};
    
    // ALM parameters
    double lambda = 0.0; // Initial Lagrange multiplier
    double r = 1.0;      // Initial penalty coefficient
    double rho = 10.0;   // Factor to increase r

    // Inner loop (Gradient Descent with Momentum) parameters
    double inner_gamma = 0.01; // Learning rate for inner loop
    double inner_beta = 0.9;   // Momentum coefficient for inner loop

    cout << "Starting Augmented Lagrangian Method (ALM)" << endl;
    cout << "Initial x,y,z: (" << vars[0] << ", " << vars[1] << ", " << vars[2] << ")" << endl;
    cout << "Inner loop learning rate (gamma): " << inner_gamma << endl;
    cout << "Inner loop momentum (beta): " << inner_beta << endl;
    cout << "Outer loop convergence tolerance (eps): " << OUTER_EPS << endl << endl;

    cout << fixed << setprecision(6);

    for (int outer_iter = 0; outer_iter < MAX_OUTER_ITERATIONS; ++outer_iter) {
        // Step 1: Solve the unconstrained subproblem
        vector<double> prev_vars = vars; // Store for checking convergence of h
        vars = optimizeInner(vars, lambda, r, inner_gamma, inner_beta);

        double h_val = constraintFunction(vars);
        double f_val = objectiveFunction(vars);

        cout << "Iter " << outer_iter << ": lambda = " << lambda 
             << ", r = " << r 
             << ", x=" << vars[0] << ", y=" << vars[1] << ", z=" << vars[2] 
             << ", h=" << h_val 
             << ", f=" << f_val << endl;

        // Step 2: Check outer loop convergence
        if (abs(h_val) < OUTER_EPS) {
            cout << "\nConvergence reached for constraint |h(x,y,z)| < " << OUTER_EPS << endl;
            cout << "Minimum value: " << setprecision(8) << objectiveFunction(vars) << endl;
            cout << "At point: x = " << setprecision(8) << vars[0]
                 << ", y = " << vars[1] << ", z = " << vars[2] << endl;
            return 0;
        }

        // Step 3: Update Lagrange multiplier
        lambda = lambda + r * h_val;

        // Step 4: Update penalty coefficient (increase if constraint not satisfied well enough)
        // A common strategy is to increase r if h_val hasn't decreased sufficiently from the previous iteration,
        // or just always increase it after a few iterations.
        // For simplicity, we'll just increase it always here.
        r = rho * r; 
    }

    cout << "\nMaximum outer iterations reached (" << MAX_OUTER_ITERATIONS << ")." << endl;
    cout << "Final minimum value: " << setprecision(8) << objectiveFunction(vars) << endl;
    cout << "At point: x = " << setprecision(8) << vars[0]
         << ", y = " << vars[1] << ", z = " << vars[2] << endl;
    cout << "Constraint h(x,y,z) = " << setprecision(8) << constraintFunction(vars) << endl;

    return 0;
}