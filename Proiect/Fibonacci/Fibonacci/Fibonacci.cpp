#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;

int fibonacci_iterative(int n) {
    int* fib = (int*)calloc(n + 2, sizeof(int));
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main() {
    int n;
    start = clock();
    for (n = 1; n <= 50000; n++) {
        fibonacci_iterative(n);
        //printf("Fibonacci(%d): %d\n", n, fibonacci_iterative(n));
    }
    end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.2f\n", cpu_time_used);

    return 0;
}
