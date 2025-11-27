#include "JsonObject.hpp"
namespace json_parser{
    void JsonObject::add(const std::string& item_name, std::unique_ptr<JsonValue> value){
        map_list[item_name] = move(value);
    }

    std::string JsonObject::to_string() const {
        using std::string_literals::operator""s;
        std::string buffer = "{"s;
        const size_t buffer_start_size = buffer.size();
        for(auto& [item_name, value] : map_list){
            buffer += "\""s + item_name + "\": "s + value->to_string() + ","s;
        }
        if(buffer.size() > buffer_start_size){
            size_t last_comma_pos = buffer.rfind(',');
            if(last_comma_pos != std::string::npos)
                buffer[last_comma_pos] = '}';
        }
        else
            buffer += "}"s;
        return buffer;
    }
}