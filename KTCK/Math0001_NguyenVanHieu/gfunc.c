#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>


static void fib_mod_pair(unsigned long long n, unsigned long long mod, unsigned long long *fn, unsigned long long *fn1) {
    if (mod == 1ULL) {
        *fn = 0ULL; *fn1 = 0ULL; return;
    }
    unsigned long long a = 0ULL, b = 1ULL; 
    unsigned long long res_f = 0ULL, res_f1 = 1ULL;

    
    unsigned long long mask = 1ULL;
    while ((mask << 1) && (mask << 1) <= n) mask <<= 1;

    unsigned long long cur_f = 0ULL, cur_f1 = 1ULL; 

    for (; mask; mask >>= 1) {
        
        unsigned long long f = cur_f;
        unsigned long long g = cur_f1;

        
        unsigned long long t1 = (2 * g % mod + mod - f % mod) % mod; 
        unsigned long long f2k = ( (__uint128_t)(f % mod) * t1 ) % mod;
        
        unsigned long long f2k1 = ( ( (__uint128_t)(f % mod) * (f % mod) ) + ( (__uint128_t)(g % mod) * (g % mod) ) ) % mod;

        cur_f = f2k;
        cur_f1 = f2k1;

        if (n & mask) {
            
            unsigned long long next_f = cur_f1 % mod;
            unsigned long long next_f1 = ( (cur_f + cur_f1) % mod );
            cur_f = next_f;
            cur_f1 = next_f1;
        }
    }

    *fn = cur_f % mod;
    *fn1 = cur_f1 % mod;
}


static unsigned long long fib_mod(unsigned long long n, unsigned long long mod) {
    unsigned long long a, b;
    fib_mod_pair(n, mod, &a, &b);
    return a;
}


static unsigned long long powmod(unsigned long long a, unsigned long long e, unsigned long long mod) {
    if (mod == 1ULL) return 0ULL;
    unsigned long long res = 1ULL % mod;
    unsigned long long base = a % mod;
    while (e) {
        if (e & 1ULL) res = (unsigned long long)((__uint128_t)res * base % mod);
        base = (unsigned long long)((__uint128_t)base * base % mod);
        e >>= 1ULL;
    }
    return res;
}


static unsigned long long gcd_u64(unsigned long long a, unsigned long long b) {
    while (b) {
        unsigned long long t = a % b; a = b; b = t;
    }
    return a;
}


static unsigned long long phi(unsigned long long n) {
    if (n == 0ULL) return 0ULL;
    unsigned long long result = n;
    unsigned long long temp = n;
    for (unsigned long long p = 2ULL; p * p <= temp; ++p) {
        if (temp % p == 0ULL) {
            while (temp % p == 0ULL) temp /= p;
            result = result / p * (p - 1ULL);
        }
    }
    if (temp > 1ULL) result = result / temp * (temp - 1ULL);
    return result;
}


static int fib_ge_threshold(unsigned long long n, unsigned long long threshold) {
    if (threshold == 0ULL) return 1; 
    unsigned long long a = 0ULL, b = 1ULL;
    if (n == 0ULL) return (0ULL >= threshold) ? 1 : 0;
    if (a >= threshold || b >= threshold) return 1;
    for (unsigned long long i = 2ULL; i <= n; ++i) {
        unsigned long long c = a + b;
        if (c < b) return 1; 
        if (c >= threshold) return 1;
        a = b; b = c;
    }
    return 0;
}



static unsigned long long g_fn_pow_fm_mod_m(unsigned long long n, unsigned long long m) {
    if (m == 0ULL) {
        
        return 0ULL;
    }
    if (m == 1ULL) return 0ULL;

    unsigned long long base = fib_mod(n, m);

    
    unsigned long long ph = phi(m);

    
    unsigned long long exp_mod = 0ULL;
    if (ph == 0ULL) {
        
        exp_mod = 0ULL;
    } else {
        exp_mod = fib_mod(m, ph);
    }

    
    int exp_ge = 0;
    if (ph > 0ULL) exp_ge = fib_ge_threshold(m, ph);

    unsigned long long exponent_for_pow = exp_mod;
    if (exp_ge) exponent_for_pow += ph;

    
    if (exponent_for_pow == 0ULL) return 1ULL % m;

    return powmod(base, exponent_for_pow, m);
}

int main() {
    unsigned long long n, m;
    printf("Nhap hai so nguyen n m (m>0): ");
    if (scanf("%" SCNu64 " %" SCNu64, &n, &m) != 2) {
        fprintf(stderr, "Nhap khong hop le\n");
        return 1;
    }

    if (m == 0ULL) {
        fprintf(stderr, "m phai > 0\n");
        return 1;
    }

    unsigned long long result = g_fn_pow_fm_mod_m(n, m);
    printf("g(%" PRIu64 ", %" PRIu64 ") = %" PRIu64 "\n", n, m, result);
    return 0;
}
