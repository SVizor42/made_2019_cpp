#ifndef matrix_h
#define matrix_h

#include <vector>
#include <iostream>

class Matrix {
public:
	class Proxy {
	public:
		Proxy(std::vector<int>& row) : row_(row) {};
		int& operator[](const size_t index);

	private:
		std::vector<int>& row_;
	};

	Matrix(size_t rows, size_t cols);
	size_t getRows() const;
	size_t getColumns() const;
	Proxy operator[](const size_t index);
	void operator*=(const int value);
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

private:
	std::vector< std::vector<int> > data_;
};

#endif