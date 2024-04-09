#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random matrix of given size
vector<vector<int>> generateRandomMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100; // Adjust the range based on your requirements
        }
    }
    return matrix;
}

// Naive Matrix Multiplication
vector<vector<int>> naiveMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    vector<vector<int>> result(m, vector<int>(p, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Function to print a matrix (for debugging purposes)
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    // Set the seed for random number generation
    srand(time(nullptr));

    // Generate large random matrices
    const int matrixSize = 1000; // Adjust the size based on your benchmarking needs
    vector<vector<int>> matrixA = generateRandomMatrix(matrixSize, matrixSize);
    vector<vector<int>> matrixB = generateRandomMatrix(matrixSize, matrixSize);

    // Benchmark naive multiplication
    clock_t start = clock();
    vector<vector<int>> naiveResult = naiveMultiply(matrixA, matrixB);
    clock_t end = clock();

    // Print results (commented out to avoid flooding the output)
    // printMatrix(naiveResult);

    // Print benchmarking time
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%.2f\n", cpu_time_used);

    return 0;
}
