#include <stdio.h>
//  Euclid 
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int a, m;
    printf("Nhap a va m (a*x ≡ 1 mod m): ");
    scanf("%d%d", &a, &m);

    int inv = mod_inverse(a, m);
    if ((a * inv) % m == 1)
        printf("Nghich dao modulo (x^-1) la: %d\n", inv);
    else
        printf("Khong ton tai nghich dao modulo.\n");

    return 0;
}