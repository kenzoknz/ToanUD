#include <stdio.h>
#include <math.h>

int is_prime(int x) {
	if (x <= 1) return 0;
	if (x <= 3) return 1;
	if (x % 2 == 0) return 0;
	int r = (int)floor(sqrt((double)x));
	for (int d = 3; d <= r; d += 2) {
		if (x % d == 0) return 0;
	}
	return 1;
}

int sum_proper_divisors(int n) {
	if (n <= 1) return 0;
	int sum = 1; 
	int r = (int)floor(sqrt((double)n));
	for (int d = 2; d <= r; ++d) {
		if (n % d == 0) {
			int other = n / d;
			sum += d;
			if (other != d) sum += other;
		}
	}
	return sum;
}

int find_perfects_below(int N, int *out, int max_out) {
	int count = 0;
	for (int i = 2; i < N; ++i) {
		if (count >= max_out) break;
		if (sum_proper_divisors(i) == i) {
			out[count++] = i;
		}
	}
	return count;
}

int find_nearest_primes(int M, int *prime_below, int *prime_above) {
	*prime_below = -1;
	*prime_above = -1;
	int d = 0;
	while (1) {
		int below = M - d;
		int above = M + d;
		if (below >= 2 && *prime_below == -1) {
			if (is_prime(below)) *prime_below = below;
		}
		if (*prime_above == -1) {
			if (above >= 2 && is_prime(above)) *prime_above = above;
		}
		if (*prime_below != -1 || *prime_above != -1) return d;
		++d;
		if (d > 100000) return -1; // safety cap
	}
}

void run_program(int N) {

	const int MAX_OUT = 100;
	int perfects[MAX_OUT];
	int count = find_perfects_below(N, perfects, MAX_OUT);
	printf("N = %d\n",N);
	if (count == 0) {
		printf("No perfect numbers found < %d\n", N);
		return;
	}

	printf("Perfect numbers: ");
	for (int i = 0; i < count; ++i) {
		if (i) printf(", ");
		printf("%d", perfects[i]);
	}
	printf("\nTotal: %d perfect number(s) < %d\n", count, N);

	int M = perfects[count - 1];
	printf("\nLargest perfect number M = %d\n", M);

	int prime_below, prime_above;
	int min_dist = find_nearest_primes(M, &prime_below, &prime_above);
	if (min_dist < 0) {
		printf("Search for nearest prime failed.\n");
		return;
	}

	if (prime_below != -1 && prime_above != -1) {
		int dist_b = abs(M - prime_below);
		int dist_a = abs(prime_above - M);
		if (dist_b < dist_a) {
			printf("Nearest prime to %d is %d (distance %d)\n", M, prime_below, dist_b);
		} else if (dist_a < dist_b) {
			printf("Nearest prime to %d is %d (distance %d)\n", M, prime_above, dist_a);
		} else {
			printf("Two primes are equally near %d: %d and %d (distance %d)\n", M, prime_below, prime_above, dist_a);
		}
	} else if (prime_below != -1) {
		printf("Nearest prime to %d is %d (below)\n", M, prime_below);
	} else if (prime_above != -1) {
		printf("Nearest prime to %d is %d (above)\n", M, prime_above);
	} else {
		printf("No nearby prime found for %d\n", M);
	}
}

int main(void) {
	const int N = 9000;
	run_program(N);
	return 0;
}
