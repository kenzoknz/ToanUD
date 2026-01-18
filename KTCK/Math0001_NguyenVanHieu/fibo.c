#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long fib(unsigned int n) {
	if (n == 0) return 0ULL;
	if (n == 1) return 1ULL;
	unsigned long long a = 0ULL, b = 1ULL, c;
	for (unsigned int i = 2; i <= n; ++i) {
		c = a + b;
		
		if (c < b) return b;
		a = b;
		b = c;
	}
	return b;
}


unsigned long long nearest_multiple_of_7_leq(unsigned long long x) {
	return x - (x % 7ULL);
}

unsigned long long largest_fib_div_by_7_leq(unsigned int n) {
	unsigned long long limit = fib(n);
	unsigned long long a = 0ULL, b = 1ULL;
	unsigned long long best = (a % 7ULL == 0ULL) ? a : 0ULL; 
	if (0ULL == limit) return 0ULL; 

	if (1ULL <= limit && (1ULL % 7ULL == 0ULL)) best = 1ULL;

	for (unsigned int i = 2; ; ++i) {
		unsigned long long c = a + b;
		if (c < b) break; 
		if (c > limit) break;
		if (c % 7ULL == 0ULL) best = c;
		a = b;
		b = c;
	}
	return best;
}


int main(void) {
	unsigned int n;
	printf("Nhap n (n >= 0): ");
	if (scanf("%u", &n) != 1) {
		printf("Du lieu khong hop le.\n");
		return 1;
	}

	unsigned long long fn = fib(n);
	printf("f(%u) = %llu\n", n, fn);

	unsigned long long nearest7 = nearest_multiple_of_7_leq(fn);
	printf("So chia het cho 7 gan nhat va <= f(%u): %llu\n", n, nearest7);

	unsigned long long fib7 = largest_fib_div_by_7_leq(n);
	if (fib7 == 0ULL) {
		
		if (fn == 0ULL) printf("Trong day Fibonacci, f(%u)=0 (chia het cho 7).\n", n);
		else printf("Khong co so Fibonacci (>0) nao chia het cho 7 va <= f(%u).\n", n);
	} else {
		printf("So trong day Fibonacci chia het cho 7 va gan nhat <= f(%u): %llu\n", n, fib7);
	}

	return 0;
}
