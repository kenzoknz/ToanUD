#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int* primenumbers = NULL;
int primeCount = 0;

int isPerfectNumber(int num)
{
    int sum = 1;
    int i;
    for (i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            sum += i;
            if (i != num / i)
            {
                sum += num / i;
            }
        }
    }
    return sum == num;
}

int isPrime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int N = 3000, M = -1, j = 1;
    
    for (int i = N - 1; i > 1; i--)
    {
        if (isPerfectNumber(i))
        {
            M = i;
            break;
        }
    }
    
    if (M != -1)
    {
        printf("So hoan hoan gan %d la: %d\n", N, M);
        int sumPrimes = 0;
        printf("Cac so nguyen to nho hon %d la: ", M);

       // count prime numbers for memory allocation
        int countPrimes = 0;
        for (int i = 2; i < M; i++)
        {
            if (isPrime(i))
            {
                countPrimes++;
            }
        }
        // allocate memory
        primenumbers = (int*)malloc(countPrimes * sizeof(int));
        if (primenumbers == NULL)
        {
            printf("Loi cap phat bo nho\n");
            return 1;
        }
        
        for (int i = 2; i < M; i++)
        {
            if (isPrime(i))
            {
                primenumbers[primeCount++] = i;
                sumPrimes += i;
            }
        }
        
        for (int i = 0; i < primeCount; i++)
        printf("%d ", primenumbers[i]);  
        
        printf("\n");
        printf("Tong cac so nguyen to nho hon %d la: %d\n", M, sumPrimes);
        free(primenumbers);
    }
    else
    {
        printf("Khong co so hoan hao nho hon %d\n", N);
    }
    
    return 0;
}
