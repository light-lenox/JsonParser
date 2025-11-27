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
        bool is_eos = false;

    public:
        Lexer(const std::string& input_);
        bool eos();
        Token next_token();

    private:
        char peek() const;
        bool starts_with(const std::string& target) const;
        void advance(size_t amount = 1);
        Token read_number();
        Token read_string();
    };
}
