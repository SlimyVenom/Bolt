#pragma once

#include "../lexer/Lexer.h"
#include "../ast/AST.h"
#include <memory>
#include <string>
#include <iostream>

class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    void advance() {currentToken = lexer.nextToken();}

public:
    Parser(Lexer& lexer) : lexer(lexer) {advance();}

    bool expect(TokenKind kind) {
        if (currentToken.kind != kind) return false;
        advance();
        return true;
    }

    std::unique_ptr<Program> parseProgram() {
        auto prog = std::make_unique<Program>();

        while (currentToken.kind != TokenKind::EndOfFile) {
            if (currentToken.kind == TokenKind::Let) {
                prog->statements.push_back(parseLetStatement());
            }
        }

        return prog;
    }

    std::unique_ptr<LetStmt> parseLetStatement() {
        // let x: int = 10;
        expect(TokenKind::Let);

        std::string name = currentToken.value;
        expect(TokenKind::Identifier);
        expect(TokenKind::Colon);

        BoltType type;
        if (currentToken.kind == TokenKind::Int) {
            type = BoltType::Int;
            expect(TokenKind::Int);
        }
        if (currentToken.kind == TokenKind::Float) {
            type = BoltType::Float;
            expect(TokenKind::Float);
        }

        expect(TokenKind::Equal);

        std::unique_ptr<Expr> expression;
        if (type == BoltType::Int) {
            expression = std::make_unique<IntegerLiteralExpr>(std::stoi(currentToken.value));
            expect(TokenKind::IntegerLiteral);
        }
        if (type == BoltType::Float) {
            expression = std::make_unique<FloatLiteralExpr>(std::stof(currentToken.value));
            expect(TokenKind::FloatLiteral);
        }

        expect(TokenKind::Semicolon);
        return std::make_unique<LetStmt>(name, type, std::move(expression));
    }
};
