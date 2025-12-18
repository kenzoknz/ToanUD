#include <stdio.h>
#include "factor.h"

int main() {
    long long n;
    printf("Nhap so nguyen duong n: ");
    scanf("%lld", &n);
    
    if(n <= 0) {
        printf("Vui long nhap so nguyen duong!\n");
        return 1;
    }
    primeFactorization(n);

    printf("Tong cac uoc so: %lld\n", sigma());
    printf("Tich cac uoc so: %lld\n", mu(n));
    
    return 0;
}
