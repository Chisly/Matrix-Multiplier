
#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "BigInt.h"

class matrix {
private:

	int rows;
	int cols;
	vector<vector<BigInt>> data; // 2D matrix

public:

	matrix(int n_rows, int n_cols) : rows(n_rows), cols(n_cols), data(n_rows, vector<BigInt>(n_cols))
	{
		rows = n_rows;
		cols = n_cols;

		// fill the matrix with random BigInt values between 0-100
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				data[i][j] = BigInt(to_string(rand())); // int -> string -> big int convert
			}
		}
	}

	// matrix multiplication
	matrix operator*(const matrix& other) const
	{
		// ensure multiplcation is possible 
		if (cols != other.rows)
		{
			cerr << "Number of columns in matrix A must be equal to rows in matrix B\n";
		}

		// make a result matrix
		matrix result(rows, other.cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < other.cols; ++j) {
				result.data[i][j] = BigInt("0");  // Initialize the result element to zero
				for (int k = 0; k < cols; ++k) {
					result.data[i][j] = result.data[i][j] + (data[i][k] * other.data[k][j]);
				}
			}
		}

		return result;
	}

	// Print matrix
	void print() const {
		for (int i = 0; i < rows; i++)
		{
			cout << " | ";
			for (int j = 0; j < cols; j++) {
				cout << data[i][j] << " ";  // Print each element followed by a space
			}
			cout << "| \n";  // End the row with a newline
		}
	}

	// Getter for rows
	int getRows() const {
		return rows;
	}

	// Getter for columns
	int getCols() const {
		return cols;
	}

	// Getter for an element
	BigInt getElement(int row, int col) const {
		return data[row][col];
	}

	// Setter for an element
	void setElement(int row, int col, const BigInt& value) {
		data[row][col] = value;
	}

};


#endif