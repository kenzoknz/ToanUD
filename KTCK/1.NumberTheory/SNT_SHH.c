#include <stdio.h>
#include <math.h>

int isPrime(long n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

long nearestPrime(long N) {
    if (N <= 2) return 2;
    if (isPrime(N)) return N;
    for (long d = 1; ; ++d) {
        long a = N - d;
        long b = N + d;
        if (a >= 2 && isPrime(a)) return a;
        if (isPrime(b)) return b;
    }
}

int isPerfect(long n) {
    if (n < 2) return 0;
    long sum = 1;
    for (long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            long d = n / i;
            if (d != i) sum += d;
        }
    }
    return sum == n;
}

int main(void) {
    long N = 503; 
    long M = nearestPrime(N);

    printf("N = %ld\n", N);
    printf("SNT M gan N nhat = %ld\n\n", M);

    int count = 0;
    long sum = 0;
    printf("Cac so hoan hao nho hon %ld:\n", M);
    for (long i = 2; i < M; ++i) {
        if (isPerfect(i)) {
            printf("%ld ", i);
            ++count;
            sum += i;
        }
    }
    if (count == 0) printf("None");
    printf("\nSo luong = %d\nTong = %ld\n", count, sum);

    return 0;
}
