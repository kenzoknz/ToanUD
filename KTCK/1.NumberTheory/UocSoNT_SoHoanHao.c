#include <stdio.h>
#include <stdbool.h>

long largestPrimeDivisor(long n) {
    long maxPrime = -1;
    while (n % 2 == 0) {
        maxPrime = 2;
        n /= 2;
    }
    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            maxPrime = i;
            n /= i;
        }
    }
    if (n > 1)
        maxPrime = n;

    return maxPrime;
}

bool isPerfect(long n) {
    if (n < 2) return false;

    long sum = 1;
    for (long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            long d = n / i;
            if (d != i)
                sum += d;
        }
    }
    return sum == n;
}

int main(void) {
    long N = 95777;
    long M = largestPrimeDivisor(N);
    printf("N = %ld\n", N);
    if (M > 0)
        printf("Uoc so nguyen to lon nhat cua N = %ld\n\n", M);
    else {
        printf("Khong tim thay uoc so nguyen to\n");
        return 0;
    }
    
    int count = 0;
    long sum = 0;

    printf("Cac so hoan hao nho hon %ld:\n", M);
    for (long i = 2; i < M; ++i) {
        if (isPerfect(i)) {
            printf("%ld ", i);
            count++;
            sum += i;
        }
    }

    if (count == 0)
        printf("None");

    printf("\n\nSo luong: %d\nTong: %ld\n", count, sum);

    return 0;
}
