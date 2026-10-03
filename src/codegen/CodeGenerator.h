#pragma once

#include "../ast/AST.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <string>
#include <iostream>

class CodeGenerator {
private:
    llvm::LLVMContext context;
    llvm::Module module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    llvm::Function* mainFunction;

public:
    CodeGenerator()
        : module("BoltModule", context),
          builder(std::make_unique<llvm::IRBuilder<>>(context)),
          mainFunction(nullptr) {}

    void generate(Program& program) {
        auto* returnType = llvm::Type::getInt32Ty(context);
        auto* functionType = llvm::FunctionType::get(returnType, false);
        mainFunction = llvm::Function::Create(
            functionType,
            llvm::Function::ExternalLinkage,
            "main",
            module
        );

        auto* entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunction);
        builder->SetInsertPoint(entryBlock);

        for (const auto& statement : program.statements) {
            auto* letStmt = dynamic_cast<LetStmt*>(statement.get());
            generateLetStatement(*letStmt);
        }
        builder->CreateRet(llvm::ConstantInt::get(returnType, 0)
        );
    }

    void generateLetStatement(const LetStmt& statement) {
        llvm::Type* type = nullptr;

        if (statement.declaredType == BoltType::Int) type = llvm::Type::getInt32Ty(context);
        if (statement.declaredType == BoltType::Float) type = llvm::Type::getFloatTy(context);

        auto* variable = builder->CreateAlloca(type, nullptr, statement.name);

        if (statement.declaredType == BoltType::Int) {
            auto* literal = dynamic_cast<IntegerLiteralExpr*>(statement.initializer.get());
            auto* value = llvm::ConstantInt::get(type, literal->value);
            builder->CreateStore(value, variable);
        }
        if (statement.declaredType == BoltType::Float) {
            auto* literal = dynamic_cast<FloatLiteralExpr*>(statement.initializer.get());
            auto* value = llvm::ConstantFP::get(type,literal->value);
            builder->CreateStore(value, variable);
        }
    }

    void writeIR(const std::string& filename) {
        std::error_code error;
        llvm::raw_fd_ostream output(filename, error);

        if (error) {
            std::cerr << "Codegen error: could not open LLVM IR file: "
                    << error.message() << '\n';
            return;
        }

        module.print(output, nullptr);
    }

    void dump() {
        module.print(llvm::outs(), nullptr);
    }
};
