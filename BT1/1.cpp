#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
bool isPrime(long long  n){
	if (n<=1) return false;
	for (long long i = 2; i<= sqrt(n); i++)
		if (!(n%i)) return false;
		
	return true;
}
void primeFactorization(int n, vector<int>& primes, vector<int>& exps) {
    int count;

    if (n % 2 == 0) {
        count = 0;
        while (n % 2 == 0) {
            n /= 2;
            count++;
        }
        primes.push_back(2);
        exps.push_back(count);
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            primes.push_back(i);
            exps.push_back(count);
        }
    }

    if (n > 2) {
        primes.push_back(n);
        exps.push_back(1);
    }
}

long long tau(const vector<int>& exps) {
    long long res = 1;
    for (int e : exps) res *= (e + 1);
    return res;
}

long long sigma(const vector<int>& primes, const vector<int>& exps) {
    long long res = 1;
    for (size_t i = 0; i < primes.size(); i++) {
        long long p = primes[i];
        int e = exps[i];
        long long term = 1;
        long long power = 1;
        for (int k = 1; k <= e; k++) {
            power *= p;
            term += power;
        }
        res *= term;
    }
    return res;
}

long long mu(int n, long long tau_n) {
    long double powResult = pow((long double)n, tau_n / 2.0L);
    return (long long)(powResult + 0.5L); 
}

void listDivisors(const vector<int>& primes, const vector<int>& exps, int idx, int current, vector<int>& divisors) {
    if (idx == primes.size()) {
        divisors.push_back(current);
        return;
    }
    int p = primes[idx];
    int e = exps[idx];
    int value = 1;
    for (int i = 0; i <= e; i++) {
        listDivisors(primes, exps, idx + 1, current * value, divisors);
        value *= p;
    }
}

bool isPerfectNumber(int n, long long sigma_n) {
    if (n == 1) return false; 
    return (sigma_n - n) == n; 
}

int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;

    vector<int> primes, exps;
    primeFactorization(n, primes, exps);

    cout << "Phan tich thua so nguyen to: ";
    for (size_t i = 0; i < primes.size(); i++) {
        cout << primes[i];
        if (exps[i] > 1) cout << "^" << exps[i];
        if (i + 1 < primes.size()) cout << " * ";
    }
    cout << "\n";

    long long tau_n = tau(exps);
    long long sigma_n = sigma(primes, exps);
    long long mu_n = mu(n, tau_n);

    cout << "So luong uoc so (tau): " << tau_n << "\n";
    cout << "Tong cac uoc so (sigma): " << sigma_n << "\n";
    cout << "Tich cac uoc so (mu): " << mu_n << "\n";

    vector<int> divisors;
    listDivisors(primes, exps, 0, 1, divisors);
    sort(divisors.begin(), divisors.end());

    cout << "Cac uoc so: ";
    for (int d : divisors) cout << d << " ";
    cout << "\n";

    if (isPerfectNumber(n, sigma_n)) {
        cout << n << " la so hoan hao.\n";
    } else {
        cout << n << " khong phai la so hoan hao.\n";
    }

    return 0;
}