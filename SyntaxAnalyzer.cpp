#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *l)
{
    la = l;
    nextToken = la->getNextToken();
    nextTokenCode = nextToken->getTokenCode();
}

void SyntaxAnalyzer::Program()
{
    Functions();
    match(EOI);
}

void SyntaxAnalyzer::Functions() {
    while(nextTokenCode == BOOL || nextTokenCode == FLOAT || nextTokenCode == INT || nextTokenCode == VOID) {
        Function();
    }
}

void SyntaxAnalyzer::Function() {
    if (nextTokenCode == BOOL) {
        match(BOOL);
    } else if (nextTokenCode == FLOAT){
        match(FLOAT);
    } else if (nextTokenCode == INT) {
        match(INT);
    } else if (nextTokenCode == VOID) {
        match(VOID);
    } else {
        syntaxError("Expected function type");
    }

    match(IDENT);
    match(LPAREN);
    ParamList();
    match(RPAREN);
    CompStmt();
}

void SyntaxAnalyzer::ParamList() {
    if (nextTokenCode == BOOL || nextTokenCode == FLOAT || nextTokenCode == INT){
        Parameters();
    }
}

void SyntaxAnalyzer::Parameters() {
    Parameter();
    while(nextTokenCode == COMMA) {
        match(COMMA);
        Parameter();
    }
}

void SyntaxAnalyzer::Parameter() {
    if (nextTokenCode == BOOL) {
        match(BOOL);
    } else if (nextTokenCode == FLOAT) {
        match(FLOAT);
    } else if (nextTokenCode == INT) {
        match(INT);
    } else {
        syntaxError("Expected parameter type");
    }
    match(IDENT);
}

void SyntaxAnalyzer::match(TokenCodes expectedTokenCode) {
    if (nextTokenCode == expectedTokenCode) {
        nextToken = la->getNextToken();
        nextTokenCode = nextToken->getTokenCode();
    } else {
        syntaxError("Expected token not found");
    }
}

void SyntaxAnalyzer::syntaxError(const std::string &message) {
    cerr << "Syntax Error: " << message << endl;
    exit(1);
}