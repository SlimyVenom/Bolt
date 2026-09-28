#include "lexer/Lexer.h"
#include <iostream>
#include <string>

std::string tokenKindToString(TokenKind kind) {
    switch (kind) {
        case TokenKind::Let:
            return "Let";
        case TokenKind::Identifier:
            return "Identifier";
        case TokenKind::Colon:
            return "Colon";
        case TokenKind::Int:
            return "Int";
        case TokenKind::Float:
            return "Float";
        case TokenKind::Equal:
            return "Equal";
        case TokenKind::Sign:
            return "Sign";
        case TokenKind::IntegerLiteral:
            return "IntegerLiteral";
        case TokenKind::FloatLiteral:
            return "FloatLiteral";
        case TokenKind::Semicolon:
            return "Semicolon";
        case TokenKind::EndOfFile:
            return "EndOfFile";
        case TokenKind::Invalid:
            return "Invalid";
    }

    return "Unknown";
}

int main() {
    std::string source =
        "let x: int = 42;\n"
        "let y: float = 3.14;";

    Lexer lexer(source);

    while (true) {
        Token token = lexer.nextToken();

        std::cout << tokenKindToString(token.kind)
                  << " -> \"" << token.value << "\"   ";
        std::cout << "\n";

        if (token.kind == TokenKind::EndOfFile)
            break;
    }
}