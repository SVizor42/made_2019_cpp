#include <string>   
#include <stdexcept>   
#include <algorithm> 

// throw spaces
void remove_spaces(std::string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}
 
// get numbers
int number(std::string& str_dec) {
	std::string::size_type sz;

	int i_dec = std::stoi(str_dec, &sz);
	str_dec = str_dec.substr(sz);
	return i_dec;
}

// MUL & DIV
double term(std::string& input) {
	double left = number(input);
    
	while (!input.empty()) {
		switch (input.at(0)) {
			case '/':
				input = input.substr(1);
				if (int divisor = number(input))  {
					left /= divisor; 
				}
				else {
					throw std::invalid_argument("Division by zero");
				}
				break;
			case '*':
				input = input.substr(1);
				left *= number(input);
				break;
			default:
				return left;
 		}
	}
}

// ADD & SUB
double expr(std::string& input) {
	double left = term(input);
    
	while (!input.empty()) {
		switch (input.at(0)) {
			case '+':
				input = input.substr(1);
				left += term(input);
				break;
			case '-':
				input = input.substr(1);
				left -= term(input);
				break;
			default:
				throw std::invalid_argument("Only [+][-][*][/] operations available");
		}
	}
	return left;
}

double processing(const std::string& str) {
	std::string input = str;
	remove_spaces(input);
	return expr(input);
};
