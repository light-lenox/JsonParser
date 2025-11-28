#include "../src/JsonParser/Parser.hpp"
#include <iostream>


int main(){
    using std::string_literals::operator""s;
    auto obj = std::make_unique<json_parser::JsonObject>();
    obj->add("number", std::make_unique<json_parser::JsonNumber>(1e3));
    obj->add("string_1", std::make_unique<json_parser::JsonString>());
    obj->add("string_2", std::make_unique<json_parser::JsonString>("ciao"));
    obj->add("bool_true", std::make_unique<json_parser::JsonBool>(true));
    obj->add("bool_false", std::make_unique<json_parser::JsonBool>(false));
    obj->add("null", std::make_unique<json_parser::JsonNull>());
    json_parser::JsonArray array;
    array.add(std::make_unique<json_parser::JsonNumber>());
    array.add(move(obj));
    std::cout << array.to_string() << std::endl;
    
    std::string input = R"([0.000000,{"bool_false": false,"bool_true": true,"null": null,"number": 1000.000000,"string_1": "","string_2": "ciao"}])";
    std::string input_2 = R"(["bool_true",null,"string_1","ciao"])";
    json_parser::Parser my_parser(input);
    auto parsed_obj = my_parser.parse();
    std::cout << parsed_obj->to_string() << std::endl;
}