# Teeny Tiny C Compiler

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

This project is an implementation of a compiler for the Teeny Tiny C language, a simplified subset of the C language. The compiler includes a Lexical Analyzer and a Syntax Analyzer (Parser).

## Overview

The Teeny Tiny C Compiler is designed to compile a simplified version of the C language. The compiler is split into two main components:

1. **Lexical Analyzer**: Responsible for tokenizing the source code into a stream of tokens.
2. **Syntax Analyzer**: Parses the tokens to ensure they conform to the grammar of the Teeny Tiny C language and generates an abstract syntax tree.

## Lexical Analyzer

The Lexical Analyzer reads the source code and breaks it down into a series of tokens. Each token represents a fundamental element of the language, such as a keyword, identifier, symbol, or literal.

## Syntax Analyzer

The Syntax Analyzer takes the stream of tokens produced by the Lexical Analyzer and constructs an abstract syntax tree (AST) by ensuring that the tokens conform to the defined grammar of Teeny Tiny C. It checks for syntactical correctness and reports errors if the source code deviates from the expected grammar.

## Grammar

The BNF grammar of the Teeny Tiny C language used in this project is as follows:

```bash
<PROGRAM> → <FUNCTIONS> EOI
<FUNCTIONS> → <FUNCTION>
<FUNCTIONS> → <FUNCTION> <FUNCTIONS>
<FUNCTION> → bool IDENT ( <PARAMLIST> ) <COMPSTMT>
<FUNCTION> → float IDENT ( <PARAMLIST> ) <COMPSTMT>
<FUNCTION> → int IDENT ( <PARAMLIST> ) <COMPSTMT>
<FUNCTION> → void IDENT ( <PARAMLIST> ) <COMPSTMT>
<PARAMLIST> → ε
<PARAMLIST> → <PARAMETERS>
<PARAMETERS> → <PARAMETER>
<PARAMETERS> → <PARAMETER> , <PARAMETERS>
<PARAMETER> → bool IDENT
<PARAMETER> → float IDENT
<PARAMETER> → int IDENT
<COMPSTMT> → { <SEQOFSTMT> }
<SEQOFSTMT> → <STATEMENT>
<SEQOFSTMT> → <STATEMENT> <SEQOFSTMT>
<STATEMENT> → <DECLARATION> ;
<STATEMENT> → do <BLOCK> while ( <EXPRESSION> ) ;
<STATEMENT> → <EXPRESSION> ;
<STATEMENT> → for ( <EXPRESSION> ; <EXPRESSION> ; <EXPRESSION> ) <BLOCK>
<STATEMENT> → if ( <EXPRESSION> ) <BLOCK>
<STATEMENT> → if ( <EXPRESSION> ) <BLOCK> else <BLOCK>
<STATEMENT> → printf ( <IDENTLIST> ) ;
<STATEMENT> → return <EXPRESSION> ;
<STATEMENT> → scanf ( <IDENTLIST> ) ;
<STATEMENT> → while ( <EXPRESSION> ) <BLOCK>
<DECLARATION> → bool <IDENTLIST>
<DECLARATION> → int <IDENTLIST>
<DECLARATION> → float <IDENTLIST>
<IDENTLIST> → IDENT
<IDENTLIST> → IDENT , <IDENTLIST>
<BLOCK> → <COMPSTMT>
<BLOCK> → <STATEMENT>
<EXPRESSION> → IDENT = <EXPRESSION>
<EXPRESSION> → <OR>
<OR> → <OR> || <AND>
<OR> → <AND>
<AND> → <AND> && <EQUALITY>
<AND> → <EQUALITY>
<EQUALITY> → <EQUALITY> == <RELATIONAL>
<EQUALITY> → <EQUALITY> != <RELATIONAL>
<EQUALITY> → <RELATIONAL>
<RELATIONAL> → <RELATIONAL> < <TERM>
<RELATIONAL> → <RELATIONAL> <= <TERM>
<RELATIONAL> → <RELATIONAL> > <TERM>
<RELATIONAL> → <RELATIONAL> >= <TERM>
<RELATIONAL> → <TERM>
<TERM> → <TERM> + <FACTOR>
<TERM> → <TERM> - <FACTOR>
<TERM> → <FACTOR>
<FACTOR> → <FACTOR> * <UNARY>
<FACTOR> → <FACTOR> / <UNARY>
<FACTOR> → <FACTOR> % <UNARY>
<FACTOR> → <UNARY>
<UNARY> → ! <PRIMARY>
<UNARY> → <PRIMARY>
<PRIMARY> → ( <EXPRESSION> )
<PRIMARY> → IDENT
<PRIMARY> → NUMLIT
<PRIMARY> → true
<PRIMARY> → false
```

## Usage

To use the Teeny Tiny C Compiler, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code using a C++ compiler. For example:

```bash
g++ -o compiler main.cpp LexicalAnalyzer.cpp SyntaxAnalyzer.cpp
```
3. Run the compiler with a Teeny Tiny C source file.
