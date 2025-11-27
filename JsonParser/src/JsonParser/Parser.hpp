#include "Lexer.hpp"
#include "JsonValues.hpp"

namespace json_parser{
    class Parser{
        Lexer lex;

    public:
        Parser(const std::string& input);

        std::unique_ptr<JsonValue> parse();

    private:
        std::unique_ptr<JsonValue> parse_value();
        JsonObject make_object();
        JsonArray make_array();
        JsonString make_string(const std::string& value);
        JsonNumber make_number(const std::string& value);
    };
}