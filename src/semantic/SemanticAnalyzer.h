#pragma once

#include "../ast/AST.h"
#include <iostream>

class SemanticAnalyzer {
public:
    bool analyze(Program& program) {
        for (const auto& statement : program.statements) {
            auto* letStmt = dynamic_cast<LetStmt*>(statement.get());

            if (!checkLetStatement(*letStmt)) {
                return false;
            }
        }

        return true;
    }

private:
    bool checkLetStatement(const LetStmt& statement) {
        BoltType varType = statement.declaredType;

        auto* tryInt =
            dynamic_cast<IntegerLiteralExpr*>(statement.initializer.get());

        auto* tryFloat =
            dynamic_cast<FloatLiteralExpr*>(statement.initializer.get());

        if (varType == BoltType::Int && tryInt == nullptr) {
            std::cout << "Semantic error: variable '" << statement.name
                    << "' declared as int but initialized with float\n";
            return false;
        }

        if (varType == BoltType::Float && tryFloat == nullptr) {
            std::cout << "Semantic error: variable '" << statement.name
                    << "' declared as float but initialized with int\n";
            return false;
        }

        return true;
    }
};
