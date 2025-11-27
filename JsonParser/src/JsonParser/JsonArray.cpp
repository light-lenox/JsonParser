#include "JsonArray.hpp"

namespace json_parser{
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