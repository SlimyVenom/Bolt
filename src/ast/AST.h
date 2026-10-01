#pragma once

#include <string>
#include <memory>
#include <utility>
#include <vector>

// Top node:
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// Expression node:
class Expr : public ASTNode {
public:
    virtual ~Expr() = default;
};

// Statement node:
class Stmt : public ASTNode {
public:
    virtual ~Stmt() = default;
};

// Program node:
class Program: public ASTNode {
public:
    std::vector<std::unique_ptr<Stmt>> statements;
};

// EXPRESSION NODES:
class IntegerLiteralExpr : public Expr {
public:
    int value;
    explicit IntegerLiteralExpr(int value) : value(value) {}
};

class FloatLiteralExpr : public Expr {
public:
    float value;
    explicit FloatLiteralExpr(float value) : value(value) {}
};


// STATEMENT NODES:

// Let statement:
enum class BoltType {
    Int,
    Float
};
class LetStmt : public Stmt {
public:
    std::string name;
    BoltType declaredType;
    std::unique_ptr<Expr> initializer;

    LetStmt(
        std::string name,
        BoltType declaredType,
        std::unique_ptr<Expr> initializer
    )
        : name(name),
          declaredType(declaredType),
          initializer(std::move(initializer)) {}
};
