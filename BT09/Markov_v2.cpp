#include <iostream>
#include <vector>
using namespace std;

void markovSteps(vector<double> initialState, vector<vector<double>> transitionMatrix, int k) {
    int n = transitionMatrix.size();

    vector<double> currentState = initialState;

    for (int step = 1; step <= k; ++step) {
        vector<double> nextState(n, 0);
		
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                nextState[i] += currentState[j] * transitionMatrix[j][i];
            }
        }
	
        currentState = nextState;

        cout << "Buoc " << step << ": ";
        cout <<  "[ ";
        for (double state : currentState) {
            cout << state << " ";
        }
        	cout << "]";
        cout << endl;
        cout << "Xac suat sinh vien A se tro thanh R sau " << step << " buoc thoi gian la " << currentState[0]<< endl;
    }
}

int main() {
    std::vector<std::vector<double>> matrix = {
    {0, 0.75, 0.20, 0.05},
    {0.05, 0.20, 0.30, 0.45},
    {0.10, 0.40, 0.30, 0.20},
    {0, 0.15, 0.30, 0.55}
	};

    int k = 3;
    vector<double> initialState = {0, 1, 0, 0};
    markovSteps(initialState, matrix, k);

    return 0;
}
