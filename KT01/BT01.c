#include <stdio.h>

void factor(int n) {
    int i = 2;
    int first = 1;
    while (n > 1) {
        int count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }
        if (count > 0) {
            if (!first) printf(" * ");
            printf("%d", i);
            if (count > 1) printf("^%d", count);
            first = 0;
        }
        i++;
    }
    printf("\n");
}

int main() {
    int n = 30000;
    printf("Phan tich thua so nguyen cua %d la: ", n);
    factor(n);
    return 0;
}