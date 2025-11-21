#include <string>

namespace json_parser{
    class JsonValue{
    public:
        virtual std::string to_string() const = 0;
        virtual ~JsonValue() {}
    };

    class JsonNumber : public JsonValue{
        double value;
    public:
        JsonNumber(double value_) : value(value_) { }
        std::string to_string() const override {
            return std::to_string(value);
        }
    };

    class JsonString : public JsonValue{
        std::string value;
    public:
        JsonString(const std::string& value_) : value(value_) {}
        std::string to_string() const override {
            using std::string_literals::operator""s;
            return "\""s  + value + "\""s;
        }
    };

    class JsonBool : public JsonValue{
        bool value;
    public:
        JsonBool(bool value_) : value(value_) {}
        std::string to_string() const override{
            using std::string_literals::operator""s;
            return value ? "true"s : "false"s;
        }
    };

    class JsonNull : public JsonValue {
    public:
        JsonNull() {}
        std::string to_string() const override{
            return "null";
        }
    };
}

