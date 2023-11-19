cmake_minimum_required(VERSION 3.26)
project(SyntaxAnalyzer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SyntaxAnalyzer
        Assignment2.cpp
        LexicalAnalyzer.cpp
        LexicalAnalyzer.h
        SyntaxAnalyzer.cpp
        SyntaxAnalyzer.h
        test1.c
        test2.c
        Token.cpp
        Token.h
        TokenCodes.h)
