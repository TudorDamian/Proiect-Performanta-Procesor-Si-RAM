#include <stdio.h>
#include <time.h>

int main() {
    int n, i;
    unsigned long long fact = 1;

    clock_t start, end;

    start = clock();
    for (n = 1000000; n <= 200000000; n += 1000000) {

        for (i = 1; i <= n; ++i) {
            fact *= i;
        }

        fact = 1;
    }
    end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.2f\n", cpu_time_used);

    return 0;
}
