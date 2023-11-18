#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *l)
{
    la = l;

}

void SyntaxAnalyzer::Program()
{

}