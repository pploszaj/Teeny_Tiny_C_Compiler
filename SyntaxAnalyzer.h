#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class SyntaxAnalyzer
{
private:
    LexicalAnalyzer *la;
    Token *nextToken;
    TokenCodes nextTokenCode;
    void Functions();
    void Function();
    void ParamList();
    void CompStmt();
    void Parameters();
    void Parameter();
    void SeqOfStmt();
    void Statement();
    void Declaration();
    void IdentList();
    void Expression();
    void Or();
    void And();
    void Equality();
    void Relational();
    void Term();
    void Factor();
    static void syntaxError(const string& message);
    void match(TokenCodes expectedTokenCode);

public:
    SyntaxAnalyzer(LexicalAnalyzer*);
    void Program();
};

#endif