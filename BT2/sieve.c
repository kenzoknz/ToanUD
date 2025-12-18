#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void segmented_sieve(int l, int r) {
    int size = r - l + 1;
    bool* is_prime = (bool*)malloc(size * sizeof(bool)); // cấp phát bộ nhớ
    for (int i = 0; i < size; ++i) is_prime[i] = true;

    int limit = (int)sqrt(r) + 1;
    bool* prime = (bool*)malloc((limit + 1) * sizeof(bool));
    for (int i = 0; i <= limit; ++i) prime[i] = true;

    for (int i = 2; i * i <= limit; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                prime[j] = false;
        }
    }

    // Đánh dấu bội của các base_primes trong đoạn [l, r]
    for (int p = 2; p <= limit; ++p) {
        if (prime[p]) {
            int start = p * p > l ? p * p : ((l + p - 1) / p) * p;
            for (int j = start; j <= r; j += p) {
                is_prime[j - l] = false;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        if (is_prime[i] && (i + l) > 1)
            printf("%d ", i + l);
    }
    printf("\n");

    free(is_prime);
    free(prime);
}

int main() {
    int l,r;
    do {
    printf("Nhap khoang [l, r]: ");
    scanf("%d %d", &l, &r);
    }
    while (l < 0 || r < 0 || l > r);
    segmented_sieve(l, r);
    return 0;
}