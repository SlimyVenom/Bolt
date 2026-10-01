#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/AST.h"

#include <iostream>
#include <string>

int main() {
    std::string source =
        "let age: int = 21;\n"
        "let score: float = 99.8;";

    std::cout << "=== Bolt Compiler ===\n\n";

    std::cout << "Source:\n";
    std::cout << source << "\n";

    std::cout << "--------------------\n";
    std::cout << "Lexing + Parsing...\n";

    Lexer lexer(source);
    Parser parser(lexer);

    std::unique_ptr<Program> program = parser.parseProgram();

    std::cout << "--------------------\n";
    std::cout << "AST:\n";

    for (const auto& statement : program->statements) {
        auto* letStmt = dynamic_cast<LetStmt*>(statement.get());

        std::cout << "LetStmt\n";
        std::cout << "  name: " << letStmt->name << '\n';

        if (letStmt->declaredType == BoltType::Int) {
            std::cout << "  type: int\n";
        }

        if (letStmt->declaredType == BoltType::Float) {
            std::cout << "  type: float\n";
        }

        auto* integerExpr =
            dynamic_cast<IntegerLiteralExpr*>(letStmt->initializer.get());

        if (integerExpr != nullptr) {
            std::cout << "  value: " << integerExpr->value << '\n';
        }

        auto* floatExpr =
            dynamic_cast<FloatLiteralExpr*>(letStmt->initializer.get());

        if (floatExpr != nullptr) {
            std::cout << "  value: " << floatExpr->value << '\n';
        }

        std::cout << '\n';
    }

    std::cout << "Compilation frontend finished!\n";
}
