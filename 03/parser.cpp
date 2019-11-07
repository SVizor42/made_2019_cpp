#include "parser.h"

bool isNumber(const std::string& str)
{
	return !str.empty() && std::find_if(str.begin(), 
		str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
}

void rtrim(std::string& str) {
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int c) {
		return !std::isspace(c);
	}).base(), str.end());
}

std::string Parser::Parse(std::string input) {
	beginFunction();

    rtrim(input);

	std::string output = "";
	std::string delimiter = " \t\n";
	std::string token;
	size_t pos = 0;
	while ((pos = input.find_first_of(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		if (token != "") {
			if (isNumber(token)) {
				for (auto& func : numberFunction) {
					func(std::stoi(token));
				}
			} 
			else {
				for (auto& func : stringFunction) {
					func(token);
				}				
			}
			output += (token + '\n');
		}
		input.erase(0, pos + 1);
	}
	for (auto& func : stringFunction) {
		func(input);
	}
	output += input;

	endFunction(output);
	
	return output;
}

void Parser::setBeginFunc(onBeginCallback func) {
	 beginFunction = func;
}

void Parser::setEndFunc(onEndCallback func) {
	 endFunction = func;
}

void Parser::registerNumFunc(onNumberCallback func) {
	numberFunction.push_back(func);
}

void Parser::registerStrFunc(onStringCallback func) {
	stringFunction.push_back(func);
}
