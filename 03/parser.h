#ifndef parser_h
#define parser_h

#include <vector>
#include <functional>
#include <algorithm>

typedef std::function<void()> onBeginCallback;
typedef std::function<void(const std::string& str)> onEndCallback;
typedef std::function<void(const int number)> onNumberCallback;
typedef std::function<void(const std::string& str)> onStringCallback;

class Parser {
public:
	std::string Parse(std::string input);
	void registerNumFunc(onNumberCallback func);
	void registerStrFunc(onStringCallback func);
	void setBeginFunc(onBeginCallback func);
	void setEndFunc(onEndCallback func);
	
private:
	onBeginCallback beginFunction;
	onEndCallback endFunction;
	std::vector<onNumberCallback> numberFunction;
	std::vector<onStringCallback> stringFunction;
};

#endif
