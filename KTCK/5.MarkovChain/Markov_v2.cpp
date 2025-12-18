#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> multiplyMatrix(const vector<vector<double>> &A, const vector<vector<double>> &B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            double aik = A[i][k];
            if (aik == 0.0) continue;
            for (int j = 0; j < n; ++j) {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<double>> matrixPower(vector<vector<double>> base, long long power) {
    int n = base.size();
    vector<vector<double>> result(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) result[i][i] = 1.0;

    while (power > 0) {
        if (power & 1LL) result = multiplyMatrix(result, base);
        base = multiplyMatrix(base, base);
        power >>= 1LL;
    }
    return result;
}

vector<double> multiplyRowVectorByMatrix(const vector<double> &v, const vector<vector<double>> &M) {
    int n = v.size();
    vector<double> res(n, 0.0);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            res[j] += v[i] * M[i][j];
        }
    }
    return res;
}

vector<double> stateAfterK(const vector<double> &initialState, const vector<vector<double>> &P, long long k) {
    if (k == 0) return initialState;
    vector<vector<double>> Pk = matrixPower(P, k);
    return multiplyRowVectorByMatrix(initialState, Pk);
}

int main() {
   
    vector<vector<double>> P = {
        {0.00, 0.75, 0.20, 0.05},
        {0.05, 0.20, 0.30, 0.45},
        {0.10, 0.40, 0.30, 0.20},
        {0.00, 0.15, 0.30, 0.55}
    };

    vector<double> initialState = {0.0, 1.0, 0.0, 0.0}; // start in state 2 (index 1)

    long long k;
    cout << "Enter number of steps k: ";
    if (!(cin >> k)) {
        cerr << "Invalid input for k" << endl;
        return 1;
    }

    if (k < 0) {
        cerr << "k must be non-negative" << endl;
        return 1;
    }
    cout << "Transition Matrix P:\n";
    for (int i = 0; i < P.size(); ++i) {
        for (int j = 0; j < P[i].size(); ++j) {
        std::cout << fixed << setprecision(2) << P[i][j] << " ";
            }
        std::cout << endl;
    }
    
    vector<double> result = stateAfterK(initialState, P, k);

    cout << fixed << setprecision(6);
    cout << "State probabilities after " << k << " steps:\n[ ";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << (i + 1 < result.size() ? ", " : " ");
    }
    cout << "]\n";

    return 0;
}
