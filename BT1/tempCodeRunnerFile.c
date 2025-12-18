#include <stdio.h>
#include <math.h>
#include <stdbool.h>
bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int countPrime(int n) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    printf("Nhap n: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Vui long nhap n >= 2\n");
        return 0;
    }

    int actual_count = countPrime(n);
    printf("So luong so nguyen to thuc te: %d\n", actual_count);
    int estimated_count = lroundf(n / log(n));
    printf("Uoc luong so luong so nguyen to (n/ln(n)): %d\n", estimated_count);
  
    return 0;
}
