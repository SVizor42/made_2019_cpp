#ifndef format_h
#define format_h

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <vector>

enum OpType {
	CLOSE,
	OPEN,
	READ
};

template <class T>
std::string covert_to_str(T&& arg) {
	std::ostringstream ostream;
	ostream << arg;
	return ostream.str();
}

template <class... TArgs>
std::string format(const std::string& input, TArgs&&... args) {
	std::vector<std::string> func_args = { covert_to_str(std::forward<TArgs>(args))... };

	std::string output = "";
	OpType operation = CLOSE; 
	int i = 0;
	while (i < input.size()) {
		switch(input[i]) {
			case '}':
				if (operation == READ) {
					operation = CLOSE;
					i++;
				}
				else {
					throw std::runtime_error("'}' without '{' or empty argument!");
				}
				break;
			case '{':
				if (operation == CLOSE) {
					operation = OPEN;
					i++;
				}
				else {
					throw std::runtime_error("'}' without '{' or valid argument!");
				}
				break;
			default:	
				if (operation == OPEN) {
					std::string arg = "";
					while (input[i] != '}' && i < input.size()) {
						arg += input[i];
						i++;
					}
					if (!arg.size() || (i == input.size() && input[input.size() - 1] != '}') || (arg.size() > 1 && arg[0] == '0')) {
						throw std::runtime_error("Invalid argument!");
					}
					else {
						for (int j = 0; j < arg.size(); j++)
							if (!isdigit(arg[j]))
								throw std::runtime_error("Invalid argument!");
						size_t index = stoi(arg);
						if (index >= func_args.size())
							throw std::runtime_error("Specified argument doesn't exist!");
						output += func_args[index];
						operation = READ;
					}
				}
				else {
					output += input[i];
					i++;
				}						
		}
	}
	
	if (operation != CLOSE) {
		throw std::runtime_error("Incorrect bracket sequence!");
	}

	return output;
}

#endif
