#include <iostream>
#include <complex>
#include <cmath>
#include <random>
#include <time.h>

using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1);

int m;
clock_t start, endd;

void generateData(Complex* x, int n) {
    for (int i = 0; i < n; ++i) {
        double random = rand() / double(RAND_MAX);
        double angle = PI * 2 * random;

        // Generate a mix of random, trigonometric, and other values
        if (random < 0.3) {
            x[i] = random; // Random number
        }
        else if (random < 0.5) {
            x[i] = Complex(cos(angle), sin(angle)); // Trigonometric function
        }
        else if (random < 0.7) {
            x[i] = exp(Complex(0, angle)); // Complex exponential
        }
        else {
            x[i] = sqrt(2.0) / 2.0 * Complex(1.0, 1.0) + sqrt(2.0) / 2.0 * Complex(-1.0, 1.0); // Complex number with absolute value 1
        }
    }
}

void fft(Complex* x, int n) {
    if (n == 1) return;

    m = n / 2;

    static Complex w[1000]; // Declare w as a static array
    for (int i = 0; i < m; ++i) {
        double ang = 2 * PI * i / n;
        w[i] = Complex(cos(ang), sin(ang));
    }

    static Complex even[1000], odd[1000]; // Declare even and odd as static arrays
    for (int i = 0; i < n; i += 2) {
        even[i / 2] = x[i];
        odd[i / 2] = x[i + 1];
    }

    fft(even, m);
    fft(odd, m);

    for (int i = 0; i < m; ++i) {
        x[i] = even[i] + w[i] * odd[i];
        x[i + m] = even[i] - w[i] * odd[i];
    }
}

void ifft(Complex* x, int n) {
    fft(x, n);
    for (int i = 0; i < n; ++i) {
        x[i] /= Complex(n, 0);
    }
}

int main() {
    const int size = 1000;
    static Complex x[1000]; // Declare x as a static array
    generateData(x, size);

    start = clock();
    // Measure FFT + IFFT time
    for (int k = 0; k <= 100000; k++) {
        fft(x, size);
        ifft(x, size);
    }
    endd = clock();

    double cpu_time_used = ((double)(endd - start)) / CLOCKS_PER_SEC;
    printf("%.2f\n", cpu_time_used);

    return 0;
}