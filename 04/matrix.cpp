#include "matrix.h"
#include <stdexcept>

int& Matrix::Proxy::operator[](const size_t index) {
	if ((index < 0) || (index >= row_.size())) {
		throw std::out_of_range("Column index is out of range!");
	}
	else {
		return row_[index];
	}
}

Matrix::Matrix(size_t rows, size_t cols) {
	data_.assign(rows, std::vector<int> (cols));
}

size_t Matrix::getRows() const {
	return data_.size();
}

size_t Matrix::getColumns() const {
	return data_[0].size();
}

Matrix::Proxy Matrix::operator[](const size_t index) {
	if ((index < 0) || (index >= data_.size())) {
		throw std::out_of_range("Row index is out of range!");
	}
	else {
		return Proxy(data_[index]);
	}
}

void Matrix::operator*=(const int value) {
	for (size_t i = 0; i < getRows(); i++)
		for (size_t j = 0; j < getColumns(); j++) {
			data_[i][j] *= value;
		}
}

bool Matrix::operator==(const Matrix& other) const {
	if (this == &other) {
		return true;
	}

	if (getRows() != other.getRows() || getColumns() != other.getColumns()) {
		return false;
	}

	for (size_t i = 0; i < getRows(); i++)
		for (size_t j = 0; j < getColumns(); j++)
			if (data_[i][j] != other.data_[i][j]) {
				return false;
			}

	return true;
}

bool Matrix::operator!=(const Matrix& other) const {
	return !(*this == other);
}
