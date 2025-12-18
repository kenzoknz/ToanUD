#include <stdio.h>

long long mul_mod(long long a, long long b, long long mod)
{
    return (a % mod) * (b % mod) % mod;
}

long long extended_gcd(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

long long mod_inverse(long long a, long long m)
{
    long long x, y;
    long long g = extended_gcd(a, m, &x, &y);
    if (g != 1)
    {
        return -1;
    }
    else
    {
        return (x % m + m) % m;
    }
}

long long chinese_remainder_theorem(int n, long long a[], long long m[], long long *M_out)
{
    long long M = 1;
    for (int i = 0; i < n; i++)
    {
        M *= m[i];
    }
    *M_out = M;

    long long result = 0;
    for (int i = 0; i < n; i++)
    {
        long long Mi = M / m[i];
        long long inv = mod_inverse(Mi, m[i]);
        result = (result + mul_mod(mul_mod(a[i], Mi, M), inv, M)) % M;
    }

    return (result + M) % M;
}

int main()
{
    /*  x = 2 (mod 5), x = 4 (mod 7), x = 6 (mod 11) */
    int n;
    printf("Nhap so luong he pt: ");
    scanf("%d", &n);
    long long a[n], m[n];
    for (int i = 0; i < n; i++)
    {
        printf("Nhap pt thu %d: (a mod m): ", i + 1);
        scanf("%lld %lld", &a[i], &m[i]);
    }

    long long M;
    long long x0 = chinese_remainder_theorem(n, a, m, &M);

    printf("Nghiem nho nhat x = %lld\n", x0);
    printf("Nghiem tong quat: x = %lld + k*%lld, voi k la so nguyen\n", x0, M);

    return 0;
}
