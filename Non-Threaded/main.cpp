
#include "matrix.h"
#include <chrono>

#define SIZE 100

int main()
{
	matrix A(SIZE, SIZE);
	matrix B{SIZE, SIZE };

	cout << "Matrix A:" << endl;
	A.print();

	cout << "\nMatrix B:" << endl;
	B.print();

	auto start = chrono::high_resolution_clock::now();

	matrix C = A * B;

	auto end = chrono::high_resolution_clock::now();

	cout << "\nMatrix C (A * B):" << endl;
	C.print();

	chrono::duration<double> duration = end - start;
	cout << "\nTime taken: " << duration.count() << " seconds" << endl;

}