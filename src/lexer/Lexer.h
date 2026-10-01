#pragma once

#include "Token.h"
#include <string>

class Lexer {
private:
    const std::string& source;
    std::size_t position = 0;

public:
    Lexer(const std::string& s) : source(s) {}

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

        if (position == source.size()) {
            return {TokenKind::EndOfFile, ""};
        }

        // Colon
        if (source[position] == ':') {
            position++;
            return {TokenKind::Colon, ":"};
        }

        // Semi-Colon
        if (source[position] == ';') {
            position++;
            return {TokenKind::Semicolon, ";"};
        }

        // Equal
        if (source[position] == '=') {
            position++;
            return {TokenKind::Equal, "="};
        }

        // Sign (+ / -)
        if (source[position] == '+' || source[position] == '-') {
            char sign = source[position];
            position++;
            return {TokenKind::Sign, std::string(1, sign)};
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

            if (curr == '.')
                dots++;

            if (position == source.size())
                break;

            curr = source[position];
        }

        // Invalid character
        if (word == "") {
            char invalidCharacter = source[position];
            position++;
            return {TokenKind::Invalid, std::string(1, invalidCharacter)};
        }

        // Keyword / Type / Identifier
        if ((word[0] >= 'a' && word[0] <= 'z') ||
            (word[0] >= 'A' && word[0] <= 'Z')) {

            if (word == "let") return {TokenKind::Let, word};
            else if (word == "int") return {TokenKind::Int, word};
            else if (word == "float") return {TokenKind::Float, word};
            else if (dots == 0) return {TokenKind::Identifier, word};
            else return {TokenKind::Invalid, word};
        }

        // Numeric literal
        if (word[0] >= '0' && word[0] <= '9') {

            if (dots == 0) return {TokenKind::IntegerLiteral, word};
            else if (dots == 1) return {TokenKind::FloatLiteral, word};
            else return {TokenKind::Invalid, word};
        }

        return {TokenKind::Invalid, word};
    }
};
