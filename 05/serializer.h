#ifndef serialize_h
#define serializer_h

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
    Error operator()(ArgsT... args) {
        return process(args...);
    }
    
private:
    std::ostream& out_;
    
    template <class T>
    Error process(T value) {
        return value.serialize(*this);
    }
    
    template <class T, class... ArgsT>
    Error process(T value, ArgsT... args) {
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
            if (!isdigit(text[i]))
                return Error::CorruptedArchive;
                
        value = std::stoull(text);
        return Error::NoError;
    }
};

#endif
