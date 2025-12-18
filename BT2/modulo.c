#include <stdio.h>
#include <math.h>

#define ll long long
ll mod(ll x, ll n, ll m){ 
    return ((ll)pow(x, n) % m);
}
ll modpow(ll x, ll n, int m ){
    if (n==0) return 1%m;
    ll u = modpow(x,n/2,m);
    u =  (u*u)%m;
    if (n%2) u = (u*x)%m;
    return u;
}
int main(){
    ll x,m,n;
    printf("Enter x, n, m (x^n mod m):");
    scanf("%lld %lld %lld",&x, &n, &m);
    printf("1. x^n mod m = %lld\n", mod(x,n,m));
    printf("2. x^n mod m = %lld\n", modpow(x,n,m));
    return 0;
}