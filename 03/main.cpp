#include <iostream>
#include "parser.h"

void printStart() {
	std::cout << "Parsing started!" << std::endl;
}

void printParsed(const std::string& str) {
	std::cout << "All parsed tokens are:" << std::endl;
	std::cout << str << std::endl;	
}

void makeNegative(int number) {
	std::cout << "Negative of " << number << " is: ";	
	std::cout << -number << std::endl;
}

void incInt(int number) {
	std::cout << "The incremented value of " << number << " is: ";
	std::cout << number + 1 << std::endl;
}

void getStrSize(const std::string& str) {
	std::cout << "Size of token '" << str << "' = ";
	std::cout << str.length() << std::endl;
}

int main(int argc, const char* argv[])
{
	Parser parser;
	parser.setBeginFunc(printStart);
	parser.setEndFunc(printParsed);
	parser.registerNumFunc(makeNegative);
	parser.registerNumFunc(incInt);
	parser.registerStrFunc(getStrSize);
	parser.Parse("  The 1    string to check	!");
	parser.Parse("Here is\nthe 2389 22	");
	return 0;
}
