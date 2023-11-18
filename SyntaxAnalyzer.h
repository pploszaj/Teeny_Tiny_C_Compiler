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


public:
    SyntaxAnalyzer(LexicalAnalyzer*);
    void Program();
};

#endif