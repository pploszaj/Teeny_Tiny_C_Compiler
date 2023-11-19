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
    void syntaxError(const string& message);
    void match(TokenCodes expectedTokenCode);

public:
    SyntaxAnalyzer(LexicalAnalyzer*);
    void Program();
};

#endif