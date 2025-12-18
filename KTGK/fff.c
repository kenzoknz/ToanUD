#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(long long n) {
    if (n<=1) return 0;
    for (int i=2; i<=sqrt(n); i++) {
        if (n%i==0) return 0;
    }
    return 1;
}


long long findPrimes(long long M, long long N, long long *primes) {
    int count = 0;
    
    for (int i = M + 1; i < N; i++) {
        if (isPrime(i)) {
            primes[count++] = i;
        }
    }
    
    return count;
}

long long calculateSum(long long arr[], long long n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

long long timsogannhat(long long arr[], long long n, long long target) {
    if (n == 0) return -1;
    
    long long closestNumber = arr[0];
    long long minDifference = abs(arr[0] - target);
    
    for (int i = 1; i < n; i++) {
        long long difference = abs(arr[i] - target);
        
        if (difference < minDifference) {
            minDifference = difference;
            closestNumber = arr[i];
        }
    }
    
    return closestNumber;
}

int main() {
    long long M = 50;
    long long N = 500;
    long long target = 300;
    
    long long *primes = (long long*)malloc((N - M) * sizeof(long long)); 
    long long count = findPrimes(M, N, primes);
    long long sum = calculateSum(primes, count);
    long long closest = timsogannhat(primes, count, target);
    
    printf("So luong so nguyen to trong khoang (%lld, %lld): %lld\n", M, N, count);
    
    printf("Cac so nguyen to tim duoc:\n");
    for (long long i = 0; i < count; i++) {
        printf("%lld ", primes[i]);
        if ((i + 1) % 20 == 0) printf("\n");
    }
    printf("\n");
    
    printf("Tong cac so nguyen to: %lld\n", sum);
    printf("So nguyen to gan voi %lld nhat trong cac so tim duoc: %lld\n", target, closest);
    
    free(primes);
    
    return 0;
}
