#ifndef parser_h
#define parser_h

#include <vector>
#include <functional>
#include <algorithm>
#include <string>

typedef std::function<void()> onBeginCallback;
typedef std::function<void(const std::string& str)> onEndCallback;
typedef std::function<void(const int number)> onNumberCallback;
typedef std::function<void(const std::string& str)> onStringCallback;

class Parser {
public:
	void Parse(std::string& input);
	void registerNumFunc(const onNumberCallback& func);
	void registerStrFunc(const onStringCallback& func);
	void setBeginFunc(const onBeginCallback& func);
	void setEndFunc(const onEndCallback& func);
	
private:
	onBeginCallback beginFunction;
	onEndCallback endFunction;
	std::vector<onNumberCallback> numberFunction;
	std::vector<onStringCallback> stringFunction;
};

#endif
