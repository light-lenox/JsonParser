#include "Parser.hpp"
#include <cassert>

namespace json_parser{
    Parser::Parser(const std::string& input) : lex(input) {}

    std::unique_ptr<JsonValue> Parser::parse(){
        auto parsed_value = parse_value();
        if(lex.get_token().type == TokenType::END && parsed_value)
            return move(parsed_value);
        return nullptr;
    }

    std::unique_ptr<JsonValue> Parser::parse_value(){
        auto curr_token = lex.get_token();
        lex.consume();
        switch(curr_token.type){
            case TokenType::LBRACE: return std::make_unique<JsonObject>(make_object());
            case TokenType::LBRACKET: return std::make_unique<JsonArray>(make_array());
            case TokenType::STRING: return std::make_unique<JsonString>(make_string(curr_token.value));
            case TokenType::NUMBER: return std::make_unique<JsonNumber>(make_number(curr_token.value));
            case TokenType::TRUE: return std::make_unique<JsonBool>(true);
            case TokenType::FALSE: return std::make_unique<JsonBool>(false);
            case TokenType::NUL: return std::make_unique<JsonNull>();
        }
        return nullptr;
    }

    JsonString Parser::make_string(const std::string& value){
        return value;
    }

    JsonNumber Parser::make_number(const std::string& value){
        return JsonNumber(std::stod(value));
    }

    JsonObject Parser::make_object(){
        JsonObject obj;
        
        if(lex.get_token().type == TokenType::RBRACE){
            lex.consume();
            return obj;
        }

        while(true){
            auto key_token = lex.get_token();
            lex.consume();
            assert(key_token.type == TokenType::STRING);
            assert(lex.get_token().type == TokenType::COLON);
            lex.consume();
            auto value = parse_value();
            assert(value);
            obj.add(key_token.value, move(value));
            auto comma_token = lex.get_token();
            lex.consume();
            if(comma_token.type == TokenType::RBRACE)
                break;
            assert(comma_token.type == TokenType::COMMA);
        }
        
        return obj;
    }

    JsonArray Parser::make_array(){
        JsonArray array;

        if(lex.get_token().type == TokenType::RBRACKET){
            lex.consume();
            return array;
        }

        while(true){
            auto curr_value = parse_value();
            assert(curr_value);
            array.add(move(curr_value));
            auto comma_token = lex.get_token();
            lex.consume();
            if(comma_token.type == TokenType::RBRACKET)
                break;
            assert(comma_token.type == TokenType::COMMA);
        }

        return array;
    }
}