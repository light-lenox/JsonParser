#include "JsonPrimitiveValues.hpp"
#include <memory>
#include <map>

namespace json_parser{
    class JsonObject : public JsonValue{
        std::map<std::string, std::unique_ptr<JsonValue>> map_list;
    public:
        void add(const std::string& item_name, std::unique_ptr<JsonValue> value);

        std::string to_string() const override;
    };
}