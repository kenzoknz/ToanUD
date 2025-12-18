#include <stdio.h>
#include <math.h>
#include "factor.h"
#define ll long long
int isPerfectNumber(ll n) {
    primeFactorization(n);
    return (sigma() - n == n);
}
void printPerfectNumbers(ll a, ll b)
{
    for (ll i = a; i < b; i++)
    {
        if (isPerfectNumber(i))
        {
            printf("%lld ", i);
        }
    }
}
int main()
{
    ll a, b;
    do{
    printf("Nhap a < b: ");
    scanf("%lld %lld", &a, &b);
    }
    while (a <= 0 || b <= 0 || a >= b);
    printPerfectNumbers(a, b);
    return 0;
}
