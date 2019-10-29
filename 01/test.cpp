#include <cmath>
#include <iostream>
#include "calc.h"

void check(const std::string& test, const float target) {
   	std::cout << (fabs((processing(test) - target))<=1e-4 ? "OK" : "FAILED") << std::endl;
}
 
int main(int argc, const char* argv[]) {
	check("2 + 3 * 4 - -2", 2 + 3 * 4 - -2);
	check("2 + 3 * 4 - +2", 2 + 3 * 4 - +2);
	check("-2", -2);
	check(" -2--3", -2+3);
	check("-2--3 --4 ", -2+3+4);
	check(" -5 * 6 ", -5*6);
	check("-5*-6", -5*-6);
	check("-5 / 6", (double) -5/6);
	check("-5 / +6", (double) -5/6);
	check("-5 / -6", (double) -5/-6);
	check("1 * -2 * 3 / 4 / -5", (double) 1 * -2 * 3 / 4 / -5);
    return 0;
 }
