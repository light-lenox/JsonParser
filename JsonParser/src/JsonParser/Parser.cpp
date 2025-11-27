#include "Parser.hpp"

namespace json_parser{
    Parser::Parser(const std::string& input) : lex(input) {}

    std::unique_ptr<JsonValue> Parser::parse(){
        auto parsed_value = parse_value();
        if(lex.next_token().type == TokenType::END && parsed_value)
            return move(parsed_value);
        ; // error
        return nullptr;
    }

    std::unique_ptr<JsonValue> Parser::parse_value(){
        auto curr_token = lex.next_token();
        switch(curr_token.type){
            case TokenType::LBRACE: return std::make_unique<JsonValue>(make_object());
            case TokenType::LBRACKET: return std::make_unique<JsonValue>(make_array());
            case TokenType::STRING: return std::make_unique<JsonValue>(make_string(curr_token.value));
            case TokenType::NUMBER: return std::make_unique<JsonValue>(make_number(curr_token.value));
            case TokenType::TRUE: return std::make_unique<JsonValue>(true);
            case TokenType::FALSE: return std::make_unique<JsonValue>(false);
            case TokenType::NUL: return std::make_unique<JsonValue>();
        }
        return nullptr;
    }

    JsonString Parser::make_string(const std::string& value){
        if(value.size() < 2)
            return JsonString{};
        return JsonString(value.substr(1, value.size() - 2));
    }

    JsonNumber Parser::make_number(const std::string& value){
        return JsonNumber(std::stod(value));
    }

    JsonObject Parser::make_object(){
        JsonObject obj;

        auto curr_token = lex.next_token();
        while(curr_token.type != TokenType::RBRACE){
            if(curr_token.type == TokenType::END)
                ; // error
            auto key_token = lex.next_token();
            if(key_token.type != TokenType::STRING)
                ; // error
            if(lex.next_token().type != TokenType::COLON)
                ; // error
            auto value = parse_value();
            if(value)
                obj.add(key_token.value, move(value));
            else
                ; // error
            if(lex.next_token().type != TokenType::COMMA)
                ; // error
            curr_token = lex.next_token();
        }     

        return obj;
    }

    JsonArray Parser::make_array(){
        JsonArray array;

        auto curr_token = lex.next_token();
        while(curr_token.type != TokenType::RBRACKET){
            if(curr_token.type == TokenType::END)
                ; // error
            auto value = parse_value();
            if(value)
                array.add(move(value));
            else
                ; // error
            if(lex.next_token().type != TokenType::COMMA)
                ; // error
            curr_token = lex.next_token();
        }

        return array;
    }
}