#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int is_coprime(int a, int b) {
    return gcd(a, b) == 1;
}

int sum_proper_divisors(int n) {
    if (n <= 1) return 0;
    int sum = 1; // 1 luôn là ước của n > 1
    int sqrt_n = (int)floor(sqrt((double)n));
    
    for (int d = 2; d <= sqrt_n; ++d) {
        if (n % d == 0) {
            sum += d;
            int other = n / d;
            if (other != d) {
                sum += other;
            }
        }
    }
    return sum;
}

int is_perfect(int n) {
    return n > 1 && sum_proper_divisors(n) == n;
}

int build_coprime_set(int N, int *M, int max_size) {
    int count = 0;
    for (int i = 1; i < 500 && count < max_size; ++i) {
        if (is_coprime(i, N)) {
            M[count++] = i;
        }
    }
    return count;
}

int find_perfects_in_set(int *M, int m_size, int *perfects, int max_perfects) {
    int count = 0;
    for (int i = 0; i < m_size && count < max_perfects; ++i) {
        if (is_perfect(M[i])) {
            perfects[count++] = M[i];
        }
    }
    return count;
}

int sum_array(int *arr, int size) {
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += arr[i];
    }
    return total;
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        if (i > 0) printf(", ");
        printf("%d", arr[i]);
    }
}

int main() {
    int N=173;
    const int MAX_M = 500;
    const int MAX_PERFECTS = 100;
    int M[MAX_M];
    int perfects[MAX_PERFECTS];
    
    
    printf("N = %d\n\n", N);
    printf("Step 1: Build set M = {m | 1 <= m < 500, gcd(m, N) = 1}\n");
    int m_size = build_coprime_set(N, M, MAX_M);
    printf("Number of elements in M: %d\n", m_size);
    
    printf("Step 2: Find perfect numbers in M\n");
    int perfect_count = find_perfects_in_set(M, m_size, perfects, MAX_PERFECTS);
    
    if (perfect_count == 0) {
        printf("Result: No perfect numbers found in M\n");
    } else {
        printf("Number of perfect numbers in M: %d\n", perfect_count);
        printf("Perfect numbers in M: ");
        print_array(perfects, perfect_count);
        printf("\n");
        
        // Bước 3: Tính tổng
        int total = sum_array(perfects, perfect_count);
        printf("Sum of perfect numbers: %d\n", total);
    }
    return 0;
}
