#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long isPrime(long long n) {
    if (n<=1) return 0;
    for (long long i=2; i<=sqrt(n); i++) {
        if (n%i==0) return 0;
    }
    return 1;
}

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    return gcd(b, a%b);
}

long long euler_phi(long long n) {
    long long result = n;
    
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Hàm tính tổng các số nguyên tố cùng nhau với N
long long sum_coprime(long long n) {
    long long sum = 0;
    long long count = 0;
    for (long long i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            sum += i;
            count++;
            
        }
    }
    printf("\n\nSo luong cac so nguyen to cung nhau: %d\n", count);
    
    return sum;
}

long long sum_coprime_optimized(long long n) {
    long long phi_n = euler_phi(n);
    return (long long)n * phi_n / 2;
}

long long SoNTGanNhat(long long m)
{
    long long lower = m - 1, upper = m + 1;
    while (lower >= 2 || upper < 1000000) {
        if (lower >= 2 && isPrime(lower)) {
            return lower;
        }
        if (isPrime(upper)) {
            return upper;
        }
        lower--;
        upper++;
    }
    return -1;
}

int main (){
    long long N = 25000;
    printf("N = %lld\n", N);
    // long long phi_N = euler_phi(N);
    // printf("So luong cac coprime la Phi(%lld) = %lld\n", N, phi_N);
    long long sum_optimized = sum_coprime(N);
    printf("Tong cac so nguyen to cung nhau voi %lld: %lld\n", N, sum_optimized);
    long long nearest_prime = SoNTGanNhat(N);
    if (nearest_prime != -1) {
        printf("So nguyen to gan nhat voi %lld la: %lld\n", N, nearest_prime);
    } else {
        printf("Khong tim thay so nguyen to gan nhat voi %lld trong khoang cho phep.\n", N);
    }
    
    return 0;
}