#include "Lexer.hpp"

namespace json_parser{
    Token::Token(TokenType type_, const std::string& value_) : type(type_){
        using std::string_literals::operator""s;
        switch(type_){
            case TokenType::LBRACE: value = "{"s; break;
            case TokenType::RBRACE: value = "}"s; break;
            case TokenType::LBRACKET: value = "["s; break;
            case TokenType::RBRACKET: value = "]"s; break;
            case TokenType::COLON: value = ":"s; break;
            case TokenType::COMMA: value = ","s; break;
            case TokenType::STRING: value = value_; break;
            case TokenType::NUMBER: value = value_ == ""s ? "0"s : value_; break;
            case TokenType::TRUE: value = "true"s; break;
            case TokenType::FALSE: value = "false"s; break;
            case TokenType::NUL: value = "null"s; break;
            case TokenType::END: value = ""s; break;
            default: ""s; break;
        }
    }

    Lexer::Lexer(const std::string& input_) : input(input_) { }

    char Lexer::peek() const{
        return input[pos];
    }

    bool Lexer::eos(){
        return pos >= input.size();
    }

    void Lexer::advance(size_t amount){
        pos += amount;
    }

    bool Lexer::starts_with(const std::string& target) const{
        std::string_view sv(input.data() + pos, input.size() - pos);
        return sv.starts_with(target);
    }

    void Lexer::skip_white_spaces(){
        while(std::isspace(static_cast<unsigned char>(peek())))
            advance();
    }

    Token Lexer::get_token(){
        pos = prev_pos;
        if(eos())
            return Token(TokenType::END);
        skip_white_spaces();
        switch(peek()){
            case '{': advance(); return Token(TokenType::LBRACE);
            case '}': advance(); return Token(TokenType::RBRACE);
            case '[': advance(); return Token(TokenType::LBRACKET);
            case ']': advance(); return Token(TokenType::RBRACKET);
            case ':': advance(); return Token(TokenType::COLON);
            case ',': advance(); return Token(TokenType::COMMA);
            case '"': return read_string();
        }
        if(std::isdigit(peek()) || peek() == '-')
            return read_number();
        if(starts_with("true")){
            advance(4);
            return Token(TokenType::TRUE);
        }
        if(starts_with("false")){
            advance(5);
            return Token(TokenType::FALSE);
        }
        if(starts_with("null")){
            advance(4);
            return Token(TokenType::NUL);
        }
        return Token(TokenType::END);
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

    void Lexer::consume(){
        if(prev_pos == pos)
            get_token();
        prev_pos = pos;
    }

}