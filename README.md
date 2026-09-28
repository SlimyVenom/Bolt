# Bolt

**Bolt** is a from-scratch compiler and programming language project written in modern C++, focused on understanding compiler architecture, LLVM, and systems-level software engineering.

The project is being developed incrementally, with each version introducing new language and compiler capabilities while exploring the design decisions behind each stage of the compilation pipeline.

## Project Goals

Bolt is primarily a learning and engineering project. The goal is to understand how a high-level program is progressively transformed into a lower-level representation rather than treating the compiler as a collection of black-box components.

The project explores:

- Lexical analysis and tokenization
- Parsing and Abstract Syntax Trees (ASTs)
- Static semantic analysis
- Symbol tables and type checking
- Intermediate representations
- LLVM IR generation
- Compiler optimizations
- Code generation and lower-level program representation
- C++ systems engineering and compiler architecture

## Compilation Pipeline

The intended compilation pipeline is:

```text
Source Code
    ↓
Lexer
    ↓
Tokens
    ↓
Parser
    ↓
Abstract Syntax Tree
    ↓
Semantic Analysis
    ↓
LLVM IR Generation
    ↓
LLVM
    ↓
Machine Code / Object Code
```

The architecture will evolve as the compiler grows. Components will be introduced when they solve concrete problems encountered during development.

## Current Status

### v0.1 — Variables

The first version establishes the foundation of the compiler and introduces statically typed variable declarations.

Example Bolt program:

```bolt
let x: int = 42;
let pi: float = 3.14;
```

Current language features include:

- `int` and `float` types
- Variable declarations using `let`
- Explicit type annotations
- Required initialization
- Exact type checking
- Lexical analysis of identifiers, keywords, literals, operators, and punctuation

Features such as reassignment, expressions, control flow, functions, strings, and collections will be introduced in later versions as new compiler problems to solve.

## Design Philosophy

Bolt is built around a few principles:

1. **Understand before abstracting** — compiler components are introduced to solve concrete problems rather than following a predetermined architecture blindly.
2. **Build from first principles** — important compiler concepts are implemented and explored directly before relying on higher-level abstractions.
3. **Experiment and verify** — design decisions are tested through small programs, compiler output, and invalid inputs.
4. **Keep stages well-defined** — each compiler stage should have a clear responsibility and contract with the stages around it.
5. **Grow incrementally** — the language and compiler architecture evolve together as new requirements emerge.

## Technology

- **Language:** C++
- **Compiler Infrastructure:** LLVM
- **Build System:** CMake
- **Platform:** Linux

## Project Status

Bolt is an ongoing project. The language, compiler architecture, and implementation will continue to evolve as new stages of the compilation pipeline are implemented and studied.

## License

License information will be added as the project develops.
