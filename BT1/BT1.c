#include <stdio.h>

void factor(int n) {
    int i = 2;
    printf("%d = ", n);
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
    int n;
    do {
        printf("Nhap n: ");
        scanf("%d", &n);
    }  while (n < 1);
    factor(n);
    return 0;
}