#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// Hàm xây dựng ma trận chuyển trạng thái P từ dữ liệu lịch sử
void buildTransitionMatrix(const vector<string>& data, 
                          vector<string>& states,
                          vector<vector<double>>& P) {
    map<string, int> stateIndex;
    
    for (const string& item : data) {
        if (stateIndex.find(item) == stateIndex.end()) {
            stateIndex[item] = states.size();
            states.push_back(item);
        }
    }
    
    int n = states.size();
    
    vector<vector<int>> count(n, vector<int>(n, 0));
    
    for (int i = 0; i < data.size() - 1; i++) {
        int from = stateIndex[data[i]];
        int to = stateIndex[data[i + 1]];
        count[from][to]++;
    }
    
    P.resize(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {
        int total = 0;
        for (int j = 0; j < n; j++) {
            total += count[i][j];
        }
        
        if (total > 0) {
            for (int j = 0; j < n; j++) {
                P[i][j] = (double)count[i][j] / total;
            }
        }
    }
}

// Hàm in ma trận chuyển trạng thái
void printTransitionMatrix(const vector<string>& states, 
                          const vector<vector<double>>& P) {
    int n = states.size();
    
    cout << "MA TRAN CHUYEN TRANG THAI P (Transition Matrix)\n";
    cout << "P[i][j] = Xac suat chuyen tu trang thai i sang trang thai j\n\n";
    
    // In header
    cout << setw(12) << "From \\ To";
    for (const string& state : states) {
        cout << setw(12) << state;
    }
    cout << "\n";
    cout << string(12 + 12 * n, '-') << "\n";
    
    // In ma trận
    for (int i = 0; i < n; i++) {
        cout << setw(12) << states[i];
        for (int j = 0; j < n; j++) {
            cout << setw(12) << fixed << setprecision(4) << P[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

// Hàm tính xác suất chuyển từ một trạng thái sang trạng thái khác
double getProbability(const vector<string>& states,
                     const vector<vector<double>>& P,
                     const string& from,
                     const string& to) {
    int fromIndex = -1, toIndex = -1;
    
    for (int i = 0; i < states.size(); i++) {
        if (states[i] == from) fromIndex = i;
        if (states[i] == to) toIndex = i;
    }
    
    if (fromIndex == -1 || toIndex == -1) {
        cout << "Loi: Trang thai khong ton tai!\n";
        return -1;
    }
    
    return P[fromIndex][toIndex];
}

// Hàm in thống kê dữ liệu
void printStatistics(const vector<string>& data,
                    const vector<string>& states,
                    const vector<vector<double>>& P) {

    
    // Đếm tần suất xuất hiện của mỗi món
    map<string, int> frequency;
    for (const string& item : data) {
        frequency[item]++;
    }
    
    cout << "Tan suat xuat hien cac mon:\n";
    for (const string& state : states) {
        cout << "  " << setw(10) << state << ": " 
             << frequency[state] << " lan ("
             << fixed << setprecision(2) 
             << (frequency[state] * 100.0 / data.size()) << "%)\n";
    }
}

int main() {
    // Dữ liệu lịch sử ăn sáng
    vector<string> data = {
        "Banh my", "Pho", "Bun", "Pizza", 
        "Banh my", "Pho", "Bun", "Pizza", 
        "Pizza", "Banh my", "Banh my", "Pho", 
        "Pho", "Pho", "Bun", "Pho"
    };
    
    cout << "PHAN TICH CHUOI MARKOV - AN SANG\n";
    // cout << "Du lieu lich su an sang:\n";
    // for (int i = 0; i < data.size(); i++) {
    //     cout << "Ngay " << setw(2) << i + 1 << ": " << data[i] << "\n";
    // }
    
    vector<string> states;
    vector<vector<double>> P;
    buildTransitionMatrix(data, states, P);
    
    printStatistics(data, states, P);
    
    printTransitionMatrix(states, P);
    
    string from = "Pho";
    string to = "Banh my";
    
    double prob = getProbability(states, P, from, to);
    
    cout << "TINH XAC SUAT\n";
    cout << "Hom qua an: " << from << "\n";
    cout << "Hom nay an: " << to << "\n";
    cout << "Xac suat P(" << to << " | " << from << ") = " 
         << fixed << setprecision(4) << prob << "\n";

   
    
    return 0;
}
