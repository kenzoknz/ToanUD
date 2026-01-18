#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define ull unsigned long long
ull fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    
    ull f1 = 1, f2 = 1, fn;
    for (int i = 3; i <= n; i++) {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return f2;
}

bool kiemTraNguyenTo(ull num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    ull sqrtNum = sqrt(num);
    for (ull i = 3; i <= sqrtNum; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void lietKeFibonacciNguyenTo(int n) {
    vector<pair<int, ull>> danhSach;
    
    cout << "\nCac so Fibonacci nguyen to trong " << n << " so dau tien:" << endl;
    cout << string(60, '-') << endl;
    
    for (int i = 1; i <= n; i++) {
        ull fib = fibonacci(i);
        if (kiemTraNguyenTo(fib)) {
            danhSach.push_back(make_pair(i, fib));
            cout << fib << " ";
        }
    }

    cout << "\nTONG SO CAC SO FIBONACCI NGUYEN TO: " << danhSach.size() << endl;
    cout << string(60, '=') << endl;
}

int main() {
    int n = 100;

    ull fn = fibonacci(n);
    cout << "F(" << n << ") = " << fn << endl;
    
    if (kiemTraNguyenTo(fn)) {
        cout << "=> F(" << n << ") LA SO NGUYEN TO" << endl;
    } else {
        cout << "=> F(" << n << ") KHONG PHAI LA SO NGUYEN TO" << endl;
    }
    
    
    lietKeFibonacciNguyenTo(n);
    
    return 0;
}