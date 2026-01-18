#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

void buildTransitionMatrix(const vector<string> &data,
                           vector<string> &states,
                           vector<vector<double>> &P)
{
    map<string, int> stateIndex;

    for (const string &item : data)
    {
        if (stateIndex.find(item) == stateIndex.end())
        {
            stateIndex[item] = states.size();
            states.push_back(item);
        }
    }

    int n = states.size();

    vector<vector<int>> count(n, vector<int>(n, 0));

    for (int i = 0; i < data.size() - 1; i++)
    {
        int from = stateIndex[data[i]];
        int to = stateIndex[data[i + 1]];
        count[from][to]++;
    }

    P.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        int total = 0;
        for (int j = 0; j < n; j++)
        {
            total += count[i][j];
        }

        if (total > 0)
        {
            for (int j = 0; j < n; j++)
            {
                P[i][j] = (double)count[i][j] / total;
            }
        }
    }
}

void printTransitionMatrix(const vector<string> &states,
                           const vector<vector<double>> &P)
{
    int n = states.size();

    cout << "MA TRAN CHUYEN TRANG THAI P (Transition Matrix)\n";
    cout << "P[i][j] = Xac suat chuyen tu trang thai i sang trang thai j\n\n";

    cout << setw(12) << "From \\ To";
    for (const string &state : states)
    {
        cout << setw(12) << state;
    }
    cout << "\n";
    cout << string(12 + 12 * n, '-') << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << setw(12) << states[i];
        for (int j = 0; j < n; j++)
        {
            cout << setw(12) << fixed << setprecision(3) << P[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

double getProbability(const vector<string> &states,
                      const vector<vector<double>> &P,
                      const string &from,
                      const string &to)
{
    int fromIndex = -1, toIndex = -1;

    for (int i = 0; i < states.size(); i++)
    {
        if (states[i] == from)
            fromIndex = i;
        if (states[i] == to)
            toIndex = i;
    }

    if (fromIndex == -1 || toIndex == -1)
    {
        cout << "Loi: Trang thai khong ton tai!\n";
        return -1;
    }

    return P[fromIndex][toIndex];
}

void printStatistics(const vector<string> &data,
                     const vector<string> &states,
                     const vector<vector<double>> &P)
{

    map<string, int> frequency;
    for (const string &item : data)
    {
        frequency[item]++;
    }

    cout << "Tan suat xuat hien cac mon:\n";
    for (const string &state : states)
    {
        cout << "  " << setw(10) << state << ": "
             << frequency[state] << " lan ("
             << fixed << setprecision(2)
             << (frequency[state] * 100.0 / data.size()) << "%)\n";
    }
}

vector<vector<double>> multiplyMatrix(const vector<vector<double>> &A, const vector<vector<double>> &B)
{
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n; ++k)
        {
            if (A[i][k] == 0.0)
                continue;
            for (int j = 0; j < n; ++j)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<vector<double>> matrixPower(vector<vector<double>> P, int power)
{
    int n = P.size();

    vector<vector<double>> result(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        result[i][i] = 1.0;

    while (power > 0)
    {
        if (power & 1)
            result = multiplyMatrix(result, P);
        P = multiplyMatrix(P, P);
        power >>= 1;
    }
    return result;
}

vector<double> multiplyVectorMatrix(const vector<double> &v, const vector<vector<double>> &M)
{
    int n = v.size();
    vector<double> res(n, 0.0);
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            res[j] += v[i] * M[i][j];
        }
    }
    return res;
}

double probabilityAfterNDays(const vector<string> &states,
                             const vector<vector<double>> &P,
                             const string &start,
                             const string &target,
                             int days)
{
    int n = states.size();
    int startIdx = -1, targetIdx = -1;
    for (int i = 0; i < n; ++i)
    {
        if (states[i] == start)
            startIdx = i;
        if (states[i] == target)
            targetIdx = i;
    }
    if (startIdx == -1 || targetIdx == -1)
        return 0.0;

    if (days == 0)
        return (startIdx == targetIdx) ? 1.0 : 0.0;

    vector<vector<double>> Ppower = matrixPower(P, days);

    vector<double> v(n, 0.0);
    v[startIdx] = 1.0;

    vector<double> vAfter = multiplyVectorMatrix(v, Ppower);
    return vAfter[targetIdx];
}

int main()
{

    vector<string> data = {
        "Pho", "Banh my", "Bun", "Pho", "Pizza",
        "Bun", "Banh my", "Pho", "Pho", "Pizza",
        "Banh my", "Bun", "Pho", "Banh my", "Bun",
        "Pho", "Pizza", "Banh my", "Pizza", "Pho",
        "Bun", "Pho", "Banh my"};

    cout << "PHAN TICH CHUOI MARKOV - AN SANG\n";

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
         << fixed << setprecision(3) << prob << "\n";

    string start = to;
    string target = "Pizza";
    int days = 3;
    double prob_after_3 = probabilityAfterNDays(states, P, start, target, days);
    cout << "Xac suat de nguoi do an '" << target << "' sau " << days << " ngay (bat dau tu '" << start << "'): "
         << fixed << setprecision(3) << prob_after_3 << "\n";
    prob_after_3 = probabilityAfterNDays(states, P, from, target, days); // vì đề không rõ ràng, nên tính cả 2 trường hợp
    cout << "Xac suat de nguoi do an '" << target << "' sau " << days << " ngay (bat dau tu '" << from << "'): "
         << fixed << setprecision(3) << prob_after_3 << "\n";

    return 0;
}
