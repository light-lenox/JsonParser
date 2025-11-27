#include "JsonValues.hpp"

namespace json_parser{
    JsonNumber::JsonNumber(double value_ = 0) : value(value_) { }
    std::string JsonNumber::to_string() const {
        return std::to_string(value);
    }

    JsonString::JsonString(const std::string& value_ = std::string{}) : value(value_) {}
    std::string JsonString::to_string() const {
        using std::string_literals::operator""s;
        return "\""s  + value + "\""s;
    }

    JsonBool::JsonBool(bool value_ = false) : value(value_) {}
    std::string JsonBool::to_string() const{
        using std::string_literals::operator""s;
        return value ? "true"s : "false"s;
    }
    
    std::string JsonNull::to_string() const{
        return "null";
    }

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

    void JsonArray::add(std::unique_ptr<JsonValue> value){
        array_list.push_back(move(value));
    }

    std::string JsonArray::to_string() const{
        using std::string_literals::operator""s;
        std::string buffer = "[";
        const size_t buffer_start_size = buffer.size();
        for(auto& value : array_list) {
            buffer += value->to_string() + ","s;
        }
        if(buffer.size() > buffer_start_size){
            size_t last_comma_pos = buffer.rfind(',');
            if(last_comma_pos != std::string::npos)
                buffer[last_comma_pos] = ']';
        }
        else
            buffer += "]"s;
        return buffer;
    }
}

