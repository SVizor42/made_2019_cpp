#ifndef format_h
#define format_h

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <vector>

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
	int operation = 0, i = 0;
	while (i < input.size()) {
		if (input[i] == '}') {
			if (operation == 2) {
				operation = 0;
				i++;
			}
			else {
				throw std::runtime_error("'}' without '{' or empty argument!");
			}
		}
		else {
			if (input[i] == '{') {
				if (!operation) {
					operation = 1;
					i++;
				}
				else {
					throw std::runtime_error("'}' without '{' or valid argument!");
				}
			}
			else {
				if (operation == 1) {
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
						if (index >= func_args.size()) {
							throw std::runtime_error("Specified argument doesn't exist!");
						}
						output += func_args[index];
						operation = 2;
					}
				}
				else {
					output += input[i];
					i++;
				}
			}		
		}
	}
	
	if (operation) {
		throw std::runtime_error("Incorrect bracket sequence!");
	}

	return output;
}

#endif
