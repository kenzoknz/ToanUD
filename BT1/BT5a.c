#include <stdio.h>
#include "factor.h"
int isPerfectNumber(long long n){
    int sum = 0;
    for(int i = 1; i <= n/2; i++){
        if(n % i == 0) sum += i;
    }
    return (sum == n);

}
int isPerfectNumber2(long long n){
    if (sigma()-n == n) {
        return 1; // n is a perfect number
    }
    return 0;
}

int main(){
    long long n;
    printf("Nhap so nguyen duong n: ");
    scanf("%lld", &n);
    primeFactorization(n);
    if (isPerfectNumber(n)) { //cach 1
        printf("%lld la so hoan hao.\n", n);
    } else {
        printf("%lld khong la so hoan hao.\n", n);
    }
    if (isPerfectNumber2(n)) {//cach 2
        printf("%lld la so hoan hao.\n", n);
    } else {
        printf("%lld khong la so hoan hao.\n", n);
    }
    return 0;
}
    