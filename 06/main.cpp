#include <cassert>
#include <sstream>
#include "big_int.h"

int main() {
	BigInt(15);
	std::cout << BigInt(0) << std::endl;

	BigInt x = 1234567800;
	std::cout << "x = " << x << std::endl;
	std::string y = "-12345678900000000000000";
	BigInt z(y);
	std::cout << "z = " << z << std::endl;

	std::cout << BigInt("-1") << std::endl;
	std::cout << BigInt("0") << std::endl;
	std::cout << BigInt("1") << std::endl;

	std::cout << "Comparision functions: " << std::endl; 
	BigInt t("232145235342121211255099921");
	std::cout << "t = " << t << std::endl;
	std::cout << "x == t ? " << (x == t) << std::endl;
	t = z;
	std::cout << "z == t ? " << (z == t) << std::endl;

	BigInt x1("12345678900000000000000");
	BigInt x2("12345678900000000000000");
	std::cout << "x1 > x2 ? " << (x1 > x2) << std::endl;

	BigInt c = -9;
	int d = -8;
	std::cout << "c + 1 <= d? " << ((c + 1) <= d) << std::endl;

	std::cout << "Sum tests: " << std::endl; 
	BigInt a1 = -9;
	BigInt b1 = -9991;
	std::cout << "a1 + b1 = " << (a1 + b1) << std::endl;	// -10000
	BigInt a2 = -9;
	BigInt b2 = 9991;
	std::cout << "a2 + b2 = " << (a2 + b2) << std::endl;	// 9982
	BigInt a3 = 9;
	BigInt b3 = -9991;
	std::cout << "a3 + b3 = " << (a3 + b3) << std::endl;	// -9982
	BigInt a4 = 9;
	BigInt b4 = 9991;
	std::cout << "a4 + b4 = " << (a4 + b4) << std::endl;	// 10000

	BigInt a = 1;
	BigInt b = a;
	int k = 2;
	c = a + k + b + 2;
	std::cout << "c = "	<< c << std::endl;	// c = 6

	std::cout << "Diff tests: " << std::endl; 
	a1 = 10008;
	b1 = 9;
	std::cout << "a1 - b1 = " << (a1 - b1) << std::endl;	// 9999
	std::cout << "b1 - a1 = " << (b1 - a1) << std::endl;    // -9999
	a2 = -10008;
	b2 = 9;
	std::cout << "a2 - b2 = " << (a2 - b2) << std::endl;    // -10017
	std::cout << "b2 - a2 = " << (b2 - a2) << std::endl;    // 10017
	a3 = 10008;
	b3 = -9;
	std::cout << "a3 - b3 = " << (a3 - b3) << std::endl;    // 10017
	std::cout << "b3 - a3 = " << (b3 - a3) << std::endl;    // -10017
	a4 = -10008;
	b4 = -9;
	std::cout << "a4 - b4 = " << (a4 - b4) << std::endl;    // -9999
	std::cout << "b4 - a4 = " << (b4 - a4) << std::endl;    // 9999

	a = -3;
	b = 5;
	k = 2;
	c = a - k - b + 2;
	std::cout << "c = "	<< c << std::endl;	// c = -8

	std::stringstream stream;
	stream << c;
	assert(stream.str() == "-8");

	stream.str("");
	stream << BigInt("1234567800");
	assert(stream.str() == "1234567800");

	return 0;
}
