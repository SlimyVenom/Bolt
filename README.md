# Bolt

**Bolt** is a from-scratch compiler and programming language project written in modern C++, focused on understanding compiler architecture, LLVM, and systems-level software engineering.

The project is developed incrementally, with each version introducing new language and compiler capabilities while exploring the design decisions behind each stage of the compilation pipeline.

## Project Goals

Bolt is primarily a learning and engineering project. The goal is to understand how a high-level program is progressively transformed into a lower-level representation rather than treating the compiler as a collection of black-box components.

The project explores:

- Lexical analysis and tokenization
- Parsing and Abstract Syntax Trees (ASTs)
- Static semantic analysis
- Type checking
- LLVM IR generation
- Native code generation
- Compiler architecture
- C++ systems engineering

As the language grows, additional compiler concepts such as symbol tables, control-flow analysis, intermediate representations, and optimization may be introduced when they solve concrete problems.

## Compilation Pipeline

The current Bolt v1 compilation pipeline is:

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
Native Executable
```

Each stage has a specific responsibility and produces a representation that is more suitable for the next stage of compilation.

## Current Status

### v1 — Variables

Bolt v1 establishes the complete end-to-end compiler pipeline for a minimal statically typed language.

A Bolt v1 program can contain variable declarations of the form:

```bolt
let x: int = 42;
let pi: float = 3.14;
```

The current language supports:

- `int` and `float` types
- Variable declarations using `let`
- Explicit type annotations
- Required initialization
- Integer and floating-point literals
- Exact type checking
- Parser error handling
- Semantic error handling
- LLVM IR generation
- Native executable generation

For v1, the initializer type must exactly match the declared type.

For example:

```bolt
let x: int = 42;       // valid
let pi: float = 3.14;  // valid

let x: int = 3.14;     // semantic error
let pi: float = 42;    // semantic error
```

v1 intentionally does not include reassignment, expressions, control flow, functions, strings, collections, or other advanced language features.

These will be introduced in later versions as new compiler problems to solve.

## Technology

- **Language:** C++
- **Compiler Infrastructure:** LLVM
- **Platform:** Linux

## Project Status

**Bolt v1 is complete.**

The current implementation can take a Bolt source program containing statically typed variable declarations, parse it into an AST, perform semantic type checking, generate LLVM IR, and produce a native executable.

Future versions will expand the language and compiler incrementally.

## License

License information will be added as the project develops.
