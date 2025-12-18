#include <stdio.h>
#include "factor.h"

void listFactors(long long n) {
    printf("Cac uoc so cua %lld la: ", n);
    for(long long i = 1; i <= n; i++) {
        if(n % i == 0) {
            printf("%lld ", i);
        }
    }
    printf("\n");

}

int main() {
    long long n;
    printf("Nhap so nguyen duong n: ");
    scanf("%lld", &n);
    primeFactorization(n);
    listFactors(n);
    printf("So luong uoc so cua %lld la: %d\n", n, tau());
    
    return 0;
}
