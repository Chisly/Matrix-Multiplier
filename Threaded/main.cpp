#include "matrix.h"
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

#define SIZE 100

// Function to multiply a row of matrix A by all columns of matrix B
void multiplyRow(const matrix& A, const matrix& B, matrix& C, int row) {
    for (int j = 0; j < B.getCols(); ++j) {
        C.setElement(row, j, BigInt("0"));  // Initialize the result element to zero
        for (int k = 0; k < A.getCols(); ++k) {
            C.setElement(row, j, C.getElement(row, j) + (A.getElement(row, k) * B.getElement(k, j)));
        }
    }
}

int main() {
    matrix A(SIZE, SIZE);
    matrix B(SIZE, SIZE);

    std::cout << "Matrix A:" << std::endl;
    A.print();

    std::cout << "\nMatrix B:" << std::endl;
    B.print();

    auto start = std::chrono::high_resolution_clock::now();

    matrix C(SIZE, SIZE);
    std::vector<std::thread> threads;

    // Launch a thread for each row of matrix C
    for (int i = 0; i < SIZE; ++i) {
        threads.emplace_back(multiplyRow, std::ref(A), std::ref(B), std::ref(C), i);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "\nMatrix C (A * B):" << std::endl;
    C.print();

    std::chrono::duration<double> duration = end - start;
    std::cout << "\nTime taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}