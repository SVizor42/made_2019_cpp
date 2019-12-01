#include <stdexcept>
#include "big_int.h"

BigInt::BigInt()
	: digits(new char[1])
	, size_(1)
	, is_negative(0)
{
	digits[0] = '0';
};

BigInt::BigInt(const int value) {
	if (!value) {
		is_negative = 0;
		size_ = 1;
		digits = new char[1]{ '0' };
	}
	else {
		is_negative = (value < 0 ? 1 : 0);

		size_ = 0;
		int temp = abs(value);
		while (temp) {
			temp /= 10;
			size_++;
		}

		digits = new char[size_];
		temp = abs(value);
		for (size_t i = 0; i < size_; i++) {
			digits[i] = '0' + (temp % 10);
			temp /= 10;
		}
	}
}

BigInt::BigInt(const std::string& str) {
	for (size_t i = 1; i < str.size(); i++) {
		if (!isdigit(str[i]))
			throw std::invalid_argument("Incorrect string format!");
	}

	if (str[0] != '-' && (!isdigit(str[0])))
		throw std::invalid_argument("Incorrect string format!");

	if (str[0] == '-') {
		size_ = str.size() - 1;
		is_negative = 1;
	}
	else {
		size_ = str.size();
		is_negative = 0;
	}

	digits = new char[size_];
	for (size_t i = 0; i < str.size() - is_negative; i++)
		digits[i] = str[str.size() - 1 - i];
}

BigInt::BigInt(const BigInt& copied)
	: digits(new char[copied.size_])
	, size_(copied.size_)
	, is_negative(copied.is_negative)
{
	std::copy(copied.digits, copied.digits + size_, digits);
}

BigInt& BigInt::operator = (const BigInt& copied) {
	if (this == &copied)
		return *this;

	char* new_digits = new char[copied.size_];
	delete[] digits;
	digits = new_digits;
	size_ = copied.size_;
	is_negative = copied.is_negative;
	std::copy(copied.digits, copied.digits + size_, digits);
	return *this;
}

BigInt::BigInt(BigInt&& moved)
	: digits(moved.digits)
	, size_(moved.size_)
	, is_negative(moved.is_negative)
{
	moved.digits = nullptr;
	moved.size_ = 0;
	moved.is_negative = 0;
}

BigInt& BigInt::operator = (BigInt&& moved) {
	if (this == &moved)
		return *this;

	delete[] digits;
	digits = moved.digits;
	size_ = moved.size_;
	is_negative = moved.is_negative;
	moved.digits = nullptr;
	moved.size_ = 0;
	moved.is_negative = 0;
	return *this;
}

BigInt::~BigInt() {
	delete[] digits;
	digits = nullptr;
	size_ = 0;
	is_negative = 0;
}

const BigInt BigInt::operator + (const BigInt& other) const {
	if (other == BigInt(0))
		return BigInt(*this);

	// first = negative
	if (is_negative) {
		// second = negative
		if (other.is_negative) {
			return -((-*this) + (-other));
		}
		// second = positive
		return (other - (-*this));
	}
	// first = positive
	else {
		// second = negative
		if (other.is_negative) {
			return (*this - (-other));
		}
		// second = positive
		if (*this < other)
		    return (other + (*this));
		
		BigInt result(*this);
		std::memset(result.digits, '0', size_ + 1);

		int carry = 0, temp = 0;
		for (size_t i = 0; i < size_ || carry; i++) {
			temp = ((i < size_) ? (digits[i] - '0') : 0);
			temp += carry + ((i < other.size_) ? (other.digits[i] - '0') : 0);
			carry = temp >= 10;
			if (carry) temp -= 10;
			result.digits[i] = '0' + temp;
		}
		if (result.digits[result.size_] != '0')
			result.size_++;

		return result;
	}
}

const BigInt BigInt::operator - (const BigInt& other) const {
	if (*this == other)
		return BigInt(0);

	// first = negative
	if (is_negative) {
		// second = negative
		if (other.is_negative) {
			return ((-other) - (-*this));
		}
		// second = positive
		return -((-*this) + other);
	}
	// first = positive
	else {
		// second = negative
		if (other.is_negative) {
			return (*this + (-other));
		}
		// second = positive
		if (*this < other)
		    return -(other - (*this));
		
		BigInt result(*this);
		std::memset(result.digits, '0', size_ + 1);

		int carry = 0, temp = 0;
		for (size_t i = 0; i < size_ || carry; i++) {
			temp = digits[i] - '0';
			temp -= carry + ((i < other.size_) ? (other.digits[i] - '0') : 0);
			carry = temp < 0;
			if (carry) temp += 10;
			result.digits[i] = '0' + temp;
		}
		while (result.digits[result.size_ - 1] == '0')
			result.size_--;

		return result;
	}
}

BigInt BigInt::operator - () {
	if (*this == BigInt(0))
		return BigInt(0);

	BigInt result(*this);
	result.is_negative = (!result.is_negative);
	return result;
}

const BigInt BigInt::operator - () const {
	BigInt result(*this);
	return -result;
}

bool BigInt::operator == (const BigInt& other) const {
	if (this == &other)
		return true;

	if (size_ != other.size_ || is_negative != other.is_negative)
		return false;

	for (size_t i = size_; i > 0; i--) {
		if (digits[i - 1] != other.digits[i - 1])
			return false;
	}

	return true;
}

bool BigInt::operator != (const BigInt& other) const {
	return (!(*this == other));
}

bool BigInt::operator < (const BigInt& other) const {
	// first = negative
	if (is_negative) {
		// second = negative
		if (other.is_negative) {
			// sizes aren't equal
			if (size_ != other.size_) {
				return size_ > other.size_;
			}
			for (size_t i = size_; i > 0; i--) {
				// digits aren't equal
				if (digits[i - 1] != other.digits[i - 1])
					return digits[i - 1] > other.digits[i - 1];
			}
			return false;
		}
		return true;
	}
	// first = positive
	else {
		// second = positive
		if (!other.is_negative) {
			// sizes aren't equal
			if (size_ != other.size_) {
				return size_ < other.size_;
			}
			for (size_t i = size_; i > 0; i--) {
				// digits aren't equal
				if (digits[i - 1] != other.digits[i - 1])
					return digits[i - 1] < other.digits[i - 1];
			}
			return false;
		}
		return false;
	}
}

bool BigInt::operator > (const BigInt& other) const {
	return (other < *this);
}

bool BigInt::operator <= (const BigInt& other) const {
	return (!(*this > other));
}

bool BigInt::operator >= (const BigInt& other) const {
	return (!(*this < other));
}

const BigInt operator + (const int first, const BigInt& second) {
	return (BigInt(first) + second);
}

const BigInt operator - (const int first, const BigInt& second) {
	return (BigInt(first) - second);
}

bool operator == (const int first, const BigInt& second) {
	return (BigInt(first) == second);
}

bool operator != (const int first, const BigInt& second) {
	return (BigInt(first) != second);
}

bool operator > (const int first, const BigInt& second) {
	return (BigInt(first) > second);
}

bool operator < (const int first, const BigInt& second) {
	return (BigInt(first) < second);
}

bool operator >= (const int first, const BigInt& second) {
	return (BigInt(first) >= second);
}

bool operator <= (const int first, const BigInt& second) {
	return (BigInt(first) <= second);
}

std::ostream& operator << (std::ostream& stream, const BigInt& big_int) {
	if (big_int.is_negative)
		stream << '-';

	for (size_t i = 0; i < big_int.size_; i++)
		stream << big_int.digits[big_int.size_ - 1 - i];

	return stream;
}
