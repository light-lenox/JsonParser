#include <string>

namespace json_parser{
    enum class TokenType{
        LBRACE, RBRACE, LBRACKET, RBRACKET,
        COLON, COMMA,
        STRING, NUMBER,
        TRUE, FALSE, NUL,
        END
    };

    struct Token{
        TokenType type;
        std::string value;

        Token(TokenType type_, const std::string& value_ = std::string{});
    };
}

namespace json_parser{
    class Lexer{
        const std::string& input;
        size_t pos = 0;
        size_t prev_pos = 0;
        
        public:
        Lexer(const std::string& input_);
        bool eos();
        Token get_token();
        void consume();

    private:
        char peek() const;
        bool starts_with(const std::string& target) const;
        void advance(size_t amount = 1);
        void skip_white_spaces();
        Token read_number();
        Token read_string();
    };
}
