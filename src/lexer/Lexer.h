#include "Token.h"
#include <string>

class Lexer {
private:
    std::string source;
    std::size_t position = 0;

public:

    Lexer(std::string &s) {
        source = s;
    }

    void skipWhiteSpaces() {
        if (position == source.size())
            return;

        char whiteSpaces[4] = {'\n', '\t', '\r', ' '};
        char curr = source[position];

        while ((curr == whiteSpaces[0]) || (curr == whiteSpaces[1]) ||
               (curr == whiteSpaces[2]) || (curr == whiteSpaces[3])) {
            position++;

            if (position == source.size())
                break;

            curr = source[position];
        }
    }

    Token nextToken() {
        skipWhiteSpaces();

        // Colon
        if (source[position] == ':') {
            Token token;
            token.kind = TokenKind::Colon;
            token.value = ":";
            position++;
            return token;
        }

        // Semi-Colon
        if (source[position] == ';') {
            Token token;
            token.kind = TokenKind::Semicolon;
            token.value = ";";
            position++;
            return token;
        }

        if (position == source.size()) {
            Token token;
            token.kind = TokenKind::EndOfFile;
            token.value = "";

            return token;
        }

        std::string word = "";
        std::size_t dots = 0;
        char curr = source[position];

        while ((curr >= 'a' && curr <= 'z') ||
               (curr >= 'A' && curr <= 'Z') ||
               (curr >= '0' && curr <= '9') ||
               (curr == '.')) {

            word += curr;
            position++;
            if (curr == '.') dots++;
            if (position == source.size()) break;
            curr = source[position];
        }

        Token token;
        token.value = word;

        // Invalid character
        if (word == "") {
            token.kind = TokenKind::Invalid;
            token.value = source[position];
            position++;

            return token;
        }

        // Keyword / Type / Identifier
        if ((word[0] >= 'a' && word[0] <= 'z') ||
            (word[0] >= 'A' && word[0] <= 'Z')) {

            if (word == "let") {
                token.kind = TokenKind::Let;
            }
            else if (word == "int") {
                token.kind = TokenKind::Int;
            }
            else if (word == "float") {
                token.kind = TokenKind::Float;
            }
            else if (dots == 0) {
                token.kind = TokenKind::Identifier;
            }
            else {
                token.kind = TokenKind::Invalid;
            }

            return token;
        }

        // Numeric literal
        if (word[0] >= '0' && word[0] <= '9') {

            if (dots == 0) {
                token.kind = TokenKind::IntegerLiteral;
            }
            else if (dots == 1) {
                token.kind = TokenKind::FloatLiteral;
            }
            else {
                token.kind = TokenKind::Invalid;
            }

            return token;
        }

        return token;
    }
};