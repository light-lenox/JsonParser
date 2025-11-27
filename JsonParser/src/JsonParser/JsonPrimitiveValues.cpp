#include "JsonPrimitiveValues.hpp"

namespace json_parser{
    JsonNumber::JsonNumber(double value_) : value(value_) { }
    std::string JsonNumber::to_string() const {
        return std::to_string(value);
    }

    JsonString::JsonString(const std::string& value_) : value(value_) {}
    std::string JsonString::to_string() const {
        using std::string_literals::operator""s;
        return "\""s  + value + "\""s;
    }

    JsonBool::JsonBool(bool value_) : value(value_) {}
    std::string JsonBool::to_string() const{
        using std::string_literals::operator""s;
        return value ? "true"s : "false"s;
    }
    
    std::string JsonNull::to_string() const{
        return "null";
    }
}

