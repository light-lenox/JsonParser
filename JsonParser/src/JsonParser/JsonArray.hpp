#include "JsonPrimitiveValues.hpp"
#include <vector>
#include <memory>

namespace json_parser{
    class JsonArray : public JsonValue{
        std::vector<std::unique_ptr<JsonValue>> array_list;
    public:
        void add(std::unique_ptr<JsonValue> value);

        std::string to_string() const override;
    };
}
