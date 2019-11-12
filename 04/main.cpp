#include <assert.h>
#include "matrix.h"

int main(int argc, const char* argv[])
{
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);

	Matrix m1(rows, cols);

	if (m1 == m) {
		std::cout << "m1 is equal to m !" << std::endl;
	}

	m[1][2] = 5; // строка 1, колонка 2
	double x = m[4][1];
//	x = m[5][1]; // throws exception

	std::cout << "m[1][2] = " << m[1][2] << std::endl;
	std::cout << "x = " << x << std::endl;

	m *= 3; // умножение на число
	std::cout << "m[1][2] = " << m[1][2] << std::endl;

	std::cout << "Print matrix m:" << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			m[i][j] = i + j;
			std::cout << m[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	if (m1 != m) {
		std::cout << "m1 is not equal to m !" << std::endl;
	}

	const Matrix m2(rows, cols);
	std::cout << "m2[2][2] = " << m2[2][2] << std::endl;
	int y = m2[2][2];
	m[1][0] = m2[2][2];
	
//	m2[2][2] = 1; // compilation error
//	m2 *= 2; // compilation error

	if (m2 == m1) {
		std::cout << "Const matrix m2 is equal to m1 !" << std::endl;
	}

	return 0;
}
