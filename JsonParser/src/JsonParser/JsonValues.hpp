#include <string>
#include <vector>
#include <memory>
#include <map>

namespace json_parser{
    class JsonValue{
    public:
        virtual std::string to_string() const = 0;
        virtual ~JsonValue() {}
    };

    class JsonNumber : public JsonValue{
        double value;
    public:
        JsonNumber(double value_ = 0);
        std::string to_string() const override;
    };

    class JsonString : public JsonValue{
        std::string value;
    public:
        JsonString(const std::string& value_ = std::string{});
        std::string to_string() const override;
    };

    class JsonBool : public JsonValue{
        bool value;
    public:
        JsonBool(bool value_ = false);
        std::string to_string() const override;
    };

    class JsonNull : public JsonValue {
    public:
        std::string to_string() const override;
    };

    class JsonObject : public JsonValue{
        std::map<std::string, std::unique_ptr<JsonValue>> map_list;
    public:
        void add(const std::string& item_name, std::unique_ptr<JsonValue> value);

        std::string to_string() const override;
    };

    class JsonArray : public JsonValue{
        std::vector<std::unique_ptr<JsonValue>> array_list;
    public:
        void add(std::unique_ptr<JsonValue> value);

        std::string to_string() const override;
    };
}

