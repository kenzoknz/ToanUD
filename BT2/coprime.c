#include <stdio.h>
#include <math.h>
#define MAX 100
int primes[MAX];
int exponents[MAX];
int factorCount = 0;
int isPrime(long long  n){
	if (n<=1) return 0;
	for (long long i = 2; i<= sqrt(n); i++)
		if (!(n%i)) return 0;
	return 1;
}
long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    return gcd(b, a%b);
}
void primeFact(long long n) {
    factorCount = 0;
    
    for (long long i = 2; i * i <= n; i += (i == 2 ? 1 : 2)) { 
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
//O(√n)
long long eulerTotient(long long n) {
    if (isPrime(n)) return n-1; //neu n nguyen to thi phi = n-1
    primeFact(n);
    long long result = 1;
   //p_i^(alpha_i - 1) * (p_i - 1)
    for (int i = 0; i < factorCount; i++) {
        result *= (primes[i] - 1) * (long long)pow(primes[i], exponents[i] - 1);
    }
    return result;
}
//O(nlog(n))
void listCoprimes(long long n) {
    long long sum =0;
    printf("Cac so nguyen to cung nhau voi %lld la: ", n);
    for (long long i = 1; i < n; i++) {
       
        if (gcd(n, i) == 1) {
            printf("%lld ", i);
            sum += i;
        }
        
    }
    printf("\nTong cac so nguyen to cung nhau voi %lld la: %lld\n", n, sum);
}

int main() {
    long long n;
    printf("n: ");
    scanf("%lld", &n);

    long long phi = eulerTotient(n);
    printf("phi(%lld): %lld\n", n, phi);
    listCoprimes(n);

    return 0;
}

