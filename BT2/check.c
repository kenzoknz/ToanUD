#include <stdio.h>
#include <math.h>

#define ll long long

int check_formulas(ll x, ll y, ll m) {
    return (x + y) % m == ((x % m) + (y % m)) % m;
}

int check_formulas2(ll x, ll y, ll m) {
    return (x - y) % m == ((x % m) - (y % m)) % m;
}

int check_formulas3(ll x, ll y, ll m) {
    return (x * y) % m == ((x % m) * (y % m)) % m;
}

int check_formulas4(ll x, ll n, ll m){
    ll a = pow(x,n);
    ll a1 = pow(x%m, n);
    return a%m == a1%m;
 }

int main() {
    ll x, y, m, n;
    printf("Enter x, y, m, n: ");
    scanf("%lld%lld%lld%lld", &x, &y, &m, &n);

    printf("check_formulas: ");
    if (check_formulas(x, y, m)) printf("True\n");
    else printf("False\n");

    printf("check_formulas2: ");
    if (check_formulas2(x, y, m)) printf("True\n");
    else printf("False\n");

    printf("check_formulas3: ");
    if (check_formulas3(x, y, m)) printf("True\n");
    else printf("False\n");

    printf("check_formulas4: ");
    if (check_formulas4(x, n, m)) printf("True\n");
    else printf("False\n");

    return 0;
}
