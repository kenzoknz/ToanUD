#include <stdio.h>

void listFactors(long long n) {
    printf("Cac uoc so cua %lld la: ", n);
    for(long long i = 1; i <= n; i++) {
        if(n % i == 0) {
            printf("%lld ", i);
        }
    }
    printf("\n");
}

int countFactors(long long n) {
    int count = 0;
    for(long long i = 1; i <= n; i++) {
        if(n % i == 0) {
            count++;
        }
    }
    return count;
}

long long sumOfFactors(long long n) {
    long long sum = 0;
    for(long long i = 1; i <= n; i++) {
        if(n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    long long n;
    printf("Nhap so nguyen duong n: ");
    scanf("%lld", &n);
    listFactors(n);
    int count = countFactors(n);
    printf("So luong uoc so cua %lld la: %d\n", n, count);
    long long sum = sumOfFactors(n);
    printf("Tong cac uoc so cua %lld la: %lld\n", n, sum);

    return 0;
}
