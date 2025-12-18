
#include <stdio.h>
#define MAX 100

int sieve[MAX];

void createSieve() {
    for (int i = 0; i < MAX; i++) sieve[i] = 1;
    sieve[0] = sieve[1] = 0;
    
    for (int i = 2; i * i < MAX; i++) {
        if (sieve[i]) {
            for (int j = i * i; j < MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int isPrime(int n) {
    if (n < 0 || n >= MAX) return 0;
    return sieve[n];
}
int isPerfect(int n) {
    int sum = 1;
    for (int i = 2; i <= n/2; ++i)
        if (n % i == 0) sum += i;
    return n > 1 && sum == n;
}

void printPerfectNumbers(int m) {
    printf("Cac so hoan hao nho hon %d: ", m);
    for (int i = 2; i < m; ++i) {
        if (isPerfect(i)) printf("%d ", i);
    }
    printf("\n");
}
int decompose(int* p, int* a, int n)
{
    int i = 0;

    if (n % 2 == 0) {
        p[i] = 2;
        a[i] = 0;
        while (n % 2 == 0) {
            a[i]++;
            n /= 2;
        }
        i++;
    }

    for (int x = 3; x * x <= n; x += 2) {
        if (n % x == 0) {
            p[i] = x;
            a[i] = 0;
            while (n % x == 0) {
                a[i]++;
                n /= x;
            }
            i++;
        }
    }

    if (n > 2) {
        p[i] = n;
        a[i] = 1;
        i++;
    }

    return i;
}

int SoNTGanNhat(int m)
{
    int lower = m - 1, upper = m + 1;
    while (lower >= 2 || upper < 1000000) {
        if (lower >= 2 && isPrime(lower)) {
            return lower;
        }
        if (isPrime(upper)) {
            return upper;
        }
        lower--;
        upper++;
    }
    return -1;
}

int find_prime(int m) {
    int sum = 0;
    printf("Cac so nguyen to nho hon %d: ", m);
    for (int i = 2; i < m; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nTong cac so nguyen to nho hon %d la: %d\n", m, sum);
    return sum;
}

int find_primes_in_range(int a, int m) {
    int sum = 0;
    printf("Cac so nguyen to trong khoang %d den %d: ", a, m);
    for (int i = a; i <= m; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
            sum += i;
        }
    }
    printf("\nTong cac so nguyen to trong khoang %d den %d la: %d\n", a, m, sum);
    return sum;
}

int main()
{
    createSieve(); // sieve prime
    
    int p[MAX], A[MAX];
    int n =8303;

     int i = decompose(p, A, n);
 

    int m = p[i-1];
    printf("m = %d \n", m);
    printf("Uoc so nguyen to lon nhat la: %d\n", m);

    int nearestPrime = SoNTGanNhat(m);
    if (nearestPrime != -1) {
        printf("So nguyen to gan nhat voi %d la: %d\n", m, nearestPrime);
    } else {
        printf("Khong tim thay so nguyen to gan voi %d\n", m);
    }

    printPerfectNumbers(m);
    find_prime(m);

    int a;
    do {
        printf("Nhap so a de tim cac so nguyen to trong khoang a den %d: ", m);
        scanf("%d", &a);
        if (a < 2 || a >= m) {
            printf("Vui long nhap a trong khoang [2, %d)\n", m);
        }
    } while (a >= m);
    find_primes_in_range(a, m);

    return 0;
}