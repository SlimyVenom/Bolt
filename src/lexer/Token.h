#include <string>

enum class TokenKind {
    Let,
    Identifier,
    Colon,
    Int,
    Float,
    Equal,
    Sign,
    IntegerLiteral,
    FloatLiteral,
    Semicolon,
    EndOfFile,
	Invalid
};

struct Token {
    TokenKind kind;
    std::string value;
};