#include <stdio.h>
#define MAX 100
int primes[MAX];
int exponents[MAX];
int factorCount = 0;

void primeFactorization(long long n) {
    factorCount = 0;
    
    for (long long i = 2; i * i <= n; i += (i == 2 ? 1 : 2)) { //dung ?: de tang buoc nhay 
        if (n % i == 0) {
            primes[factorCount] = i;
            exponents[factorCount] = 0;
            while (n % i == 0) {
                exponents[factorCount]++;
                n /= i;
            }
            factorCount++;
        }
    }
    
    if (n > 1) {
        primes[factorCount] = n;
        exponents[factorCount] = 1;
        factorCount++;
    }
}
long long sigma() {// hàm sigma
    long long sum = 1;
    for (int i = 0; i < factorCount; i++) {
        long long term = 1;
        long long power = primes[i];
        for (int j = 1; j <= exponents[i]; j++) {
            term += power;
            power *= primes[i];
        }
        sum *= term;
    }
    return sum;
}
int tau() {
    int result = 1;
    for (int i = 0; i < factorCount; i++) {
        result *= (exponents[i] + 1);
    }
    return result;
}
long long mu(long long n) {
    int t = tau();
    long long result = 1;
    //  n^(tau/2)
    for (int i = 0; i < t/2; i++) {
        result *= n;
    }
    if (t % 2 == 1) {
        long long sqrtn = 1;
        for (int i = 0; i < factorCount; i++) {
            for (int j = 0; j < exponents[i]/2; j++) {
                sqrtn *= primes[i];
            }
        }
        result *= sqrtn;
    }
    
    return result;
}