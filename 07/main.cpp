#include <cassert>
#include <iostream>
#include "format.h"

template <class... TArgs>
void try_catch_error(const std::string& str, TArgs&&... args) {
	std::string text;
	try {
		text = format(str, std::forward<TArgs>(args)...);
	} catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return;
	}
	std::cout << text << std::endl;
}

int main() {
	try_catch_error("{1}+{1} = {0}", 2, "one");
	try_catch_error("{0} any text {1} {0}", 2.6, 'd');
	try_catch_error("One symbol test: {1}", 2.6, 'd', 3);
	try_catch_error("{5}{1}{2}{1}{0}", 1, ' ', "by", 2.4, -7, "one");
	try_catch_error("{0}{0}{0}", "");
	try_catch_error("{0}", "only");
	try_catch_error("Without formatting", 2, "one");

	try_catch_error("{0}{}", "one");
	try_catch_error("{{0}", "one");
	try_catch_error("{0}{", "one");
	try_catch_error("{{0}}", "one");
	try_catch_error("{0}{1a}", "one", 1);
	try_catch_error("{1}+{1} = {0}", "one");
	try_catch_error("1} bracket test", "one");
	try_catch_error("test { } test", "one");
	try_catch_error("test {test} test", "one");

	return 0;
}
