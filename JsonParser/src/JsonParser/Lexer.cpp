#include "Lexer.hpp"
#include <map>

namespace json_parser{
    Token::Token(TokenType type_, const std::string& value_ = std::string{}){
        using std::string_literals::operator""s;
        type = type_;
        switch(type_){
            case TokenType::LBRACE: value = "{"s; break;
            case TokenType::RBRACE: value = "}"s; break;
            case TokenType::LBRACKET: value = "["s; break;
            case TokenType::RBRACKET: value = "]"s; break;
            case TokenType::COLON: value = ":"s; break;
            case TokenType::COMMA: value = ","s; break;
            case TokenType::STRING: value = "\""s + value_ + "\""s; break;
            case TokenType::NUMBER: value = value_ == ""s ? "0"s : value_; break;
            case TokenType::TRUE: value = "true"s; break;
            case TokenType::FALSE: value = "false"s; break;
            case TokenType::NUL: value = "null"s; break;
            case TokenType::END: value = ""s; break;
        }
    }

    Lexer::Lexer(const std::string& input_) : input(input_) {}

    char Lexer::peek(){
        return input[pos];
    }

    bool Lexer::eos(){
        if(is_eos) return true;
        return is_eos = pos >= input.size();
    }

    void Lexer::advance(size_t amount = 1){
        if(eos()) return;
        pos += amount;
        if(eos())
            pos = input.size() - 1;
    }

    bool Lexer::starts_with(const std::string& target){
        std::string_view sv(input.data() + pos, input.size() - pos);
        return sv.starts_with(target);
    }

    Token Lexer::next_token(){
        if(eos())
            return Token(TokenType::END);
        switch(peek()){
            case '{': pos++; return Token(TokenType::LBRACE);
            case '}': pos++; return Token(TokenType::RBRACE);
            case '[': pos++; return Token(TokenType::LBRACKET);
            case ']': pos++; return Token(TokenType::RBRACKET);
            case ':': pos++; return Token(TokenType::COLON);
            case ',': pos++; return Token(TokenType::COMMA);
            case '"': return read_string();
        }
        if(std::isdigit(peek()) || peek() == '-')
            return read_number();
        if(starts_with("true"))
            return Token(TokenType::TRUE);
        if(starts_with("false"))
            return Token(TokenType::FALSE);
        if(starts_with("null"))
            return Token(TokenType::NUL);
    }

    Token Lexer::read_string(){
        int start = pos;
        advance();

        while(not eos() && peek() != '\"'){
            advance();
        }

        advance();

        return Token(TokenType::STRING, input.substr(start + 1, pos - start - 2));
    }

    Token Lexer::read_number(){
        size_t start = pos;
        if(peek() == '-') 
            advance();
        while(not eos() && std::isdigit(peek())) 
            advance();

        if(not eos() && peek() == '.') 
            advance();
        while(not eos() && std::isdigit(peek())) 
            advance();

        if(not eos() && peek() == 'e' || peek() == 'E'){
            advance();
            if(not eos() && peek() == '+' || peek() == '-') 
                advance();
            while(eos() && std::isdigit(peek()))
                advance();
        }

        return Token(TokenType::NUMBER, input.substr(start, pos - start));
    }


}