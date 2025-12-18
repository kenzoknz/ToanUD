#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    while(a!=b){
        if(a>b) a = a-b;  
        else    b = b-a;
        
    }
    return a;
}

long long gcd2(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    return gcd2(b, a%b);
}

long long lcm(long long a, long long b){
    if(a == 0 || b == 0)
        return 0;
    long long GCD = gcd(a,b);
    long long LCM = (a*b)/GCD;
    return LCM;
}

int main(){
    long long a,b,n;
    
    printf("Nhap a: ");
    scanf("%lld", &a);
    printf("Nhap b: ");
    scanf("%lld", &b);
    printf("GCD(%lld, %lld) = %lld\n", a, b, gcd(a,b));
    printf("GCD(%lld, %lld) v2 = %lld\n", a, b, gcd2(a,b));
    printf("LCM(%lld, %lld) = %lld\n", a, b, lcm(a,b));
    return 0;
}