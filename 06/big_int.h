#ifndef big_int_h
#define big_int_h

#include <iostream>
#include <cstring>

class BigInt {
public:
	BigInt();
	BigInt(const int value);
	BigInt(const std::string& str);
	BigInt(const BigInt& copied);
	BigInt& operator = (const BigInt& copied);
	BigInt(BigInt&& moved);
	BigInt& operator = (BigInt&& moved);
	~BigInt();

	const BigInt operator + (const BigInt& other) const;
	const BigInt operator - (const BigInt& other) const;

	BigInt operator - ();
	const BigInt operator - () const;

	bool operator == (const BigInt& other) const;
	bool operator != (const BigInt& other) const;
	bool operator < (const BigInt& other) const;
	bool operator > (const BigInt& other) const;
	bool operator <= (const BigInt& other) const;
	bool operator >= (const BigInt& other) const;

	friend const BigInt operator + (const int first, const BigInt& second);
	friend const BigInt operator - (const int first, const BigInt& second);

	friend bool operator == (const int first, const BigInt& second);
	friend bool operator != (const int first, const BigInt& second);
	friend bool operator < (const int first, const BigInt& second);
	friend bool operator > (const int first, const BigInt& second);
	friend bool operator <= (const int first, const BigInt& second);
	friend bool operator >= (const int first, const BigInt& second);
	friend std::ostream& operator << (std::ostream& stream, const BigInt& big_int);

private:
	char* digits;
	size_t size_;
	bool is_negative;
};

#endif
