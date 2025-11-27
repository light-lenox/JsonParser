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
        JsonNumber(double value_);
        std::string to_string() const override;
    };

    class JsonString : public JsonValue{
        std::string value;
    public:
        JsonString(const std::string& value_);
        std::string to_string() const override;
    };

    class JsonBool : public JsonValue{
        bool value;
    public:
        JsonBool(bool value_);
        std::string to_string() const override;
    };

    class JsonNull : public JsonValue {
    public:
        std::string to_string() const override;
    };
}

