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
        match(IDENT);
        match(LPAREN);
        ParamList();
        match(RPAREN);
        CompStmt();
    }
}