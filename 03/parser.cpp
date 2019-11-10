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

void Parser::Parse(std::string& input) {
	if (beginFunction != nullptr) {
		beginFunction();
	}

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
		input = input.substr(pos + 1);
	}
	for (auto& func : stringFunction) {
		func(input);
	}
	output += input;

	if (endFunction != nullptr) {
		endFunction(output);
	}

	input = output;
}

void Parser::setBeginFunc(const onBeginCallback& func) {
	 beginFunction = func;
}

void Parser::setEndFunc(const onEndCallback& func) {
	 endFunction = func;
}

void Parser::registerNumFunc(const onNumberCallback& func) {
	numberFunction.push_back(func);
}

void Parser::registerStrFunc(const onStringCallback& func) {
	stringFunction.push_back(func);
}
