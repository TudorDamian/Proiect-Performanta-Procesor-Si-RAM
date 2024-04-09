#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <time.h>

clock_t start, end;

void factorize(unsigned long long n) {
    if (n <= 1) {
        return;
    }

    unsigned long long i = 2;
    while (n > 1) {
        if (n % i == 0) {
            //printf("%llu ", i);
            n /= i;

            while (n % i == 0) {
                n /= i;
            }
        }

        i++;
    }
}

int main() {
    unsigned long long n;

    start = clock();
    for (n = 10000000; n >= 100; n -= 1237) {
        factorize(n);
        //printf("%llu ", n);
    }
    end = clock();

    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.2f\n", cpu_time_used);

    return 0;
}