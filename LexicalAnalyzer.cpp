#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

//constructor
LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
    currentChar = '\n';
    currentCharIndex = 0;
    sourceCodeFile = scf;
    line = "\n";
    reservedWords["bool"] = BOOLSYM;
    reservedWords["do"] = DOSYM;
    reservedWords["else"] = ELSESYM;
    reservedWords["false"] = FALSESYM;
    reservedWords["float"] = FLOATSYM;
    reservedWords["for"] = FORSYM;
    reservedWords["if"] = IFSYM;
    reservedWords["int"] = INTSYM;
    reservedWords["printf"] = PRINTFSYM;
    reservedWords["return"] = RETURNSYM;
    reservedWords["scanf"] = SCANFSYM;
    reservedWords["true"] = TRUESYM;
    reservedWords["void"] = VOIDSYM;
    reservedWords["while"] = WHILESYM;
}

//checks if reached the end of the source code file
bool LexicalAnalyzer::isEOI()
{
    return (sourceCodeFile->eof() && (currentCharIndex == (line.length() - 1)));
}

int LexicalAnalyzer::getCurrentTokenPosition()
{
    return currentTokenPosition;
}

void LexicalAnalyzer::readNextLine()
{
    getline(*sourceCodeFile, line);
    line = line + "\n";
    cout << line;
}

void LexicalAnalyzer::getNextChar()
{
    if (currentCharIndex == (line.length() - 1))
    {
        readNextLine();
        currentCharIndex = -1;
    }

    currentCharIndex++;
    currentChar = line.at(currentCharIndex);
}

bool LexicalAnalyzer::isWhiteSpace() {
    return (currentChar == ' ' || currentChar == '\t' || currentChar == '\n');
}

void LexicalAnalyzer::skipWhiteSpace() {
    while(!isEOI() && isWhiteSpace()){
        getNextChar();
    }
}

Token* LexicalAnalyzer::getArithmeticOrParenToken() {
    currentTokenPosition = currentCharIndex;
    switch (currentChar) {
        case '+':
            getNextChar();
            return new Token(PLUS, "+");
        case '-':
            getNextChar();
            return new Token(MINUS, "-");
        case '*':
            getNextChar();
            return new Token(TIMES, "*");
        case '/':
            getNextChar();
            return new Token(SLASH, "/");
        case '%':
            getNextChar();
            return new Token(MOD, "%");
        case '(':
            getNextChar();
            return new Token(LPAREN, "(");
        case ')':
            getNextChar();
            return new Token(RPAREN, ")");
        case '{':
            getNextChar();
            return new Token(LBRACE, "{");
        case '}':
            getNextChar();
            return new Token(RBRACE, "}");
        case ',':
            getNextChar();
            return new Token(COMMA, ",");
        case ';':
            getNextChar();
            return new Token(SEMICOLON, ";");
        case '!':
            getNextChar();
            return new Token(NOT, "!");
        }
        return nullptr;
}

bool LexicalAnalyzer::isLetter() {
    return ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'));
}

bool LexicalAnalyzer::isDigit() {
    return (currentChar >= '0' && currentChar <= '9');
}

Token* LexicalAnalyzer::getMultiCharSymbol() {
    char initialChar = currentChar;
    currentTokenPosition = currentCharIndex;
    getNextChar();
    switch (initialChar) {
        case '|':
            if(currentChar == '|'){
                getNextChar();
                return new Token(OR, "||");
            }
            return nullptr;
        case '&':
            if(currentChar == '&'){
                getNextChar();
                return new Token(AND, "&&");
            }
            return nullptr;
        case '=':
            if(currentChar == '='){
                getNextChar();
                return new Token(EQL, "==");
            } else {
                return new Token(ASSIGN, "=");
            }
        case '!':
            if(currentChar == '='){
                getNextChar();
                return new Token(NEQ, "!=");
            }
            return nullptr;
        case '<':
            if(currentChar == '='){
                getNextChar();
                return new Token(LEQ, "<=");
            }
            else {
                return new Token(LSS, "<");
            }
        case '>':
            if(currentChar == '='){
                getNextChar();
                return new Token(GEQ, ">=");
            }
            else {
                return new Token(GTR, ">");
            }
    }

    --currentCharIndex;
    currentChar = line.at(currentCharIndex);
    return nullptr;
}

Token* LexicalAnalyzer::getReservedWord() {
    string lexeme = "";
    currentTokenPosition = currentCharIndex;

    while(!isEOI() && isLetter()){
        lexeme += currentChar;
        getNextChar();
    }

    if(reservedWords.find(lexeme) != reservedWords.end()) {
        return new Token(reservedWords[lexeme], lexeme);
    }

    return nullptr;
}

Token* LexicalAnalyzer::getIdentifier() {
    string lexeme = "";

    currentTokenPosition = currentCharIndex;

    while(isLetter() || isDigit()) {
        lexeme += currentChar;
        getNextChar();
    }

    if(!lexeme.empty()){
        for(auto & c: lexeme) c = tolower(c);
        if(lexeme == "bool"){
            return new Token(BOOLSYM, lexeme);
        }
        if(lexeme == "do"){
            return new Token(DOSYM, lexeme);
        }
        if(lexeme == "else"){
            return new Token(ELSESYM, lexeme);
        }
        if(lexeme == "false"){
            return new Token(FALSESYM, lexeme);
        }
        if(lexeme == "float"){
            return new Token(FLOATSYM, lexeme);
        }
        if(lexeme == "for"){
            return new Token(FORSYM, lexeme);
        }
        if(lexeme == "if"){
            return new Token(IFSYM, lexeme);
        }
        if(lexeme == "int"){
            return new Token(INTSYM, lexeme);
        }
        if(lexeme == "printf"){
            return new Token(PRINTFSYM, lexeme);
        }
        if(lexeme == "return"){
            return new Token(RETURNSYM, lexeme);
        }
        if(lexeme == "scanf"){
            return new Token(SCANFSYM, lexeme);
        }
        if(lexeme == "true"){
            return new Token(TRUESYM, lexeme);
        }
        if(lexeme == "void"){
            return new Token(VOIDSYM, lexeme);
        }
        if(lexeme == "while"){
            return new Token(WHILESYM, lexeme);
        }
        else {
            return new Token(IDENT, lexeme);
        }
    }
    return nullptr;
}

Token* LexicalAnalyzer::getNumericLiteral() {
    string lexeme = "";
    currentTokenPosition = currentCharIndex;
    bool sawPeriod = false;

    while(isDigit() || (currentChar == '.' && !sawPeriod)) {
        if(currentChar == '.'){
            sawPeriod = true;
        }
        lexeme += currentChar;
        getNextChar();
    }

    if(!lexeme.empty()){
        return new Token(NUMLIT, lexeme);
    }

    return nullptr;
}

Token* LexicalAnalyzer::getNextToken()
{
    Token *t;

    skipWhiteSpace();

    if(isEOI()) {
        t = new Token(EOI, "EOI");
        return t;
    }

    t = getNumericLiteral();
    if(t != nullptr){
        return t;
    }

    t = getIdentifier();
    if(t != nullptr) {
        return t;
    }

    t = getMultiCharSymbol();
    if(t != nullptr){
        return t;
    }

    t = getArithmeticOrParenToken();
    if(t != nullptr){
        return t;
    }

    t = getReservedWord();
    if(t != nullptr) {
        return t;
    }

    if(currentChar == '='){
        return new Token(ASSIGN, "=");
    }

    string lexeme(1, currentChar);
    getNextChar();
    return new Token(NAL, lexeme);
}
