#include <iostream>
#include <sstream>
#include <cassert>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
    std::ostream& out_;
    
    template <class T>
    Error process(T& value) {
        return value.serialize(*this);
    }
    
    template <class T, class... Args>
    Error process(T& value, Args&... args) {
        if (process(value) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else {
            out_ << Separator;
            return process(args...);
        }
    }
    
    Error process(bool value) {
        std::string text;
        if (value)
            text = "true";
        else
            text = "false";
            
        out_ << text;
        return Error::NoError;
    }
    
    Error process(uint64_t value) {
        out_ << value;
        return Error::NoError;
    }
};

class Deserializer {
public:
    explicit Deserializer(std::istream& in)
        : in_(in) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
    std::istream& in_;
    
    template <class T>
    Error process(T& value) {
        return value.serialize(*this);
    }
    
    template <class T, class... Args>
    Error process(T& value, Args&... args) {
        if (process(value) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else
            return process(args...);
    }
    
    Error process(bool& value) {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }
    
    Error process(uint64_t& value) {
        std::string text;
        in_ >> text;
        
        if (!text.size())
            return Error::CorruptedArchive;
            
        for (int i = 0; i < text.size(); i++)
            if (!isdigit)
                return Error::CorruptedArchive;
                
        value = std::stoull(text);
        return Error::NoError;
    }
};

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }
};

int main() {

    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    
    return 0;
}

