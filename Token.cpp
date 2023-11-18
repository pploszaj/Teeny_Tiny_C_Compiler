#include <iostream>
#include <string>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

Token::Token()
{
    setTokenCode(NAL);
    setLexemeString("");
}

Token::Token(TokenCodes tc, string ls)
{
    setTokenCode(tc);
    setLexemeString(ls);
}

string Token::getLexemeString()
{
    return lexemeString;
}

void Token::setLexemeString(string ls)
{
    lexemeString = ls;
}

TokenCodes Token::getTokenCode()
{
    return tokenCode;
}

void Token::setTokenCode(TokenCodes tc)
{
    tokenCode = tc;
}

ostream& operator<<(ostream& os, const Token& t)
{
    string tcs[] =
            {
                    "PLUS", "MINUS", "TIMES", "SLASH", "MOD", "LPAREN", "RPAREN", "LBRACE",
                    "RBRACE", "COMMA", "SEMICOLON", "OR", "AND", "ASSIGN", "EQL", "NOT", "NEQ",
                    "LSS", "LEQ", "GTR", "GEQ", "BOOLSYM", "DOSYM", "ELSESYM", "FALSESYM",
                    "FLOATSYM", "FORSYM", "IFSYM", "INTSYM", "PRINTFSYM", "RETURNSYM",
                    "SCANFSYM", "TRUESYM", "VOIDSYM", "WHILESYM", "IDENT", "NUMLIT", "EOI",
                    "NAL"
            };

    os << "Next token is: " << tcs[t.tokenCode];
    os << ", lexeme string is \"" << t.lexemeString << "\"";

    return os;
}