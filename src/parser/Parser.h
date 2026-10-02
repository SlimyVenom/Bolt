#pragma once

#include "../lexer/Lexer.h"
#include "../ast/AST.h"
#include <memory>
#include <string>
#include <iostream>

inline std::string tokenKindToString(TokenKind kind) {
    switch (kind) {
        case TokenKind::Let: return "Let";
        case TokenKind::Identifier: return "Identifier";
        case TokenKind::Colon: return "Colon";
        case TokenKind::Int: return "Int";
        case TokenKind::Float: return "Float";
        case TokenKind::Equal: return "Equal";
        case TokenKind::IntegerLiteral: return "IntegerLiteral";
        case TokenKind::FloatLiteral: return "FloatLiteral";
        case TokenKind::Semicolon: return "Semicolon";
        case TokenKind::EndOfFile: return "EndOfFile";
        case TokenKind::Invalid: return "Invalid";
        case TokenKind::Sign: return "Sign";
    }

    return "Unknown";
}

class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    void advance() {currentToken = lexer.nextToken();}

public:
    Parser(Lexer& lexer) : lexer(lexer) {advance();}

    bool expect(TokenKind kind) {
        if (currentToken.kind != kind) {
            std::cout << "Parser error: expected token: "
                    << tokenKindToString(kind)
                    << ", got: "
                    << tokenKindToString(currentToken.kind)
                    << '\n';
            return false;
        }

        advance();
        return true;
    }

    std::unique_ptr<Program> parseProgram() {
        auto prog = std::make_unique<Program>();

        while (currentToken.kind != TokenKind::EndOfFile) {
            if (currentToken.kind == TokenKind::Let) {
                auto statement = parseLetStatement();
                if (statement == nullptr) return nullptr;
                prog->statements.push_back(std::move(statement));
            }
            else {
                std::cout << "Parser error: expected token: Let, got: "
                        << tokenKindToString(currentToken.kind) << '\n';
                return nullptr;
            }
        }

        return prog;
    }

    std::unique_ptr<LetStmt> parseLetStatement() {
        // let x: int = 10;
        if (!expect(TokenKind::Let)) return nullptr;

        // x
        std::string name = currentToken.value;
        if (!expect(TokenKind::Identifier)) return nullptr;
        if (!expect(TokenKind::Colon)) return nullptr;

        // int
        BoltType type;
        if (currentToken.kind != TokenKind::Int &&
            currentToken.kind != TokenKind::Float) {
            std::cout << "Parser error: expected token: Int or Float, got: "
                    << tokenKindToString(currentToken.kind) << '\n';
            return nullptr;
        }
        if (currentToken.kind == TokenKind::Int) {
            type = BoltType::Int;
            expect(TokenKind::Int);
        }
        if (currentToken.kind == TokenKind::Float) {
            type = BoltType::Float;
            expect(TokenKind::Float);
        }
        if (!expect(TokenKind::Equal)) return nullptr;

        // 10;
        std::unique_ptr<Expr> expression;
        if (type == BoltType::Int) {
            expression = std::make_unique<IntegerLiteralExpr>(std::stoi(currentToken.value));
            if (!expect(TokenKind::IntegerLiteral)) return nullptr;
        }
        if (type == BoltType::Float) {
            expression = std::make_unique<FloatLiteralExpr>(std::stof(currentToken.value));
            if (!expect(TokenKind::FloatLiteral)) return nullptr;
        }

        if (!expect(TokenKind::Semicolon)) return nullptr;
        return std::make_unique<LetStmt>(name, type, std::move(expression));
    }
};
