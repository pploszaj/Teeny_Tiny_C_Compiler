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
//    cout << "IN PROGRAM FUNCTION" << endl;
    Functions();
    cout << "RIGHT BEFORE MATCH EOI" << endl;
    match(EOI);
    cout << "The program is syntactically correct" << endl;
}

void SyntaxAnalyzer::Functions() {
//    cout << "IN FUNCTIONS FUNCTION" << endl;
    while(nextTokenCode == BOOLSYM || nextTokenCode == FLOATSYM || nextTokenCode == INTSYM || nextTokenCode == VOIDSYM) {
        Function();
    }
}

void SyntaxAnalyzer::Function() {
//    cout << "IN FUNCTION FUNCTION" << endl;
    if (nextTokenCode == BOOLSYM) {
        match(BOOLSYM);
    } else if (nextTokenCode == FLOATSYM){
        match(FLOATSYM);
    } else if (nextTokenCode == INTSYM) {
        match(INTSYM);
    } else if (nextTokenCode == VOIDSYM) {
        match(VOIDSYM);
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
//    cout << "IN PARAMLIST FUNCTION" << endl;
    if (nextTokenCode == BOOLSYM || nextTokenCode == FLOATSYM || nextTokenCode == INTSYM){
        Parameters();
    }
}

void SyntaxAnalyzer::Parameters() {
//    cout << "IN PARAMETERS FUNCTION" << endl;
    Parameter();
    while(nextTokenCode == COMMA) {
        match(COMMA);
        Parameter();
    }
}

void SyntaxAnalyzer::Parameter() {
//    cout << "IN PARAMETER FUNCTION" << endl;
    if (nextTokenCode == BOOLSYM) {
        match(BOOLSYM);
    } else if (nextTokenCode == FLOATSYM) {
        match(FLOATSYM);
    } else if (nextTokenCode == INTSYM) {
        match(INTSYM);
    } else {
        syntaxError("Expected parameter type");
    }
    match(IDENT);
}

void SyntaxAnalyzer::CompStmt() {
//    cout << "IN COMPSTMT FUNCTION" << endl;
    match(LBRACE);
    SeqOfStmt();
    match(RBRACE);
}

void SyntaxAnalyzer::SeqOfStmt() {
//    cout << "IN SEQOFSTMT FUNCTION" << endl;
    while(nextTokenCode != RBRACE){
        Statement();
    }
}

void SyntaxAnalyzer::Statement() {
//    cout << "IN STATEMENT FUNCTION" << endl;
    switch (nextTokenCode) {
        case BOOLSYM:
        case INTSYM:
        case FLOATSYM:
            Declaration();
            match(SEMICOLON);
            break;

        case DOSYM:
            match(DOSYM);
            Block();
            match(WHILESYM);
            match(LPAREN);
            Expression();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case FORSYM:
            match(FORSYM);
            match(LPAREN);
            Expression();
            match(SEMICOLON);
            Expression();
            match(SEMICOLON);
            Expression();
            match(RPAREN);
            Block();
            break;
        case IFSYM:
            match(IFSYM);
            match(LPAREN);
            Expression();
            match(RPAREN);
            Block();
            if(nextTokenCode == ELSESYM){
                match(ELSESYM);
                Block();
            }
            break;
        case PRINTFSYM:
            match(PRINTFSYM);
            match(LPAREN);
            IdentList();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case RETURNSYM:
            match(RETURNSYM);
            Expression();
            match(SEMICOLON);
            break;
        case SCANFSYM:
            match(SCANFSYM);
            match(LPAREN);
            IdentList();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case WHILESYM:
            match(WHILESYM);
            match(LPAREN);
            Expression();
            match(RPAREN);
            Block();
            break;
        case IDENT:
            Expression();
            break;
        case OR:
            match(OR);
            Expression();
            break;
        default:
            syntaxError("Unexpected token in Statement");
            break;
    }
}
void SyntaxAnalyzer::Declaration() {
//    cout << "IN DECLARATION FUNCTION" << endl;
    if(nextTokenCode == BOOLSYM || nextTokenCode == INTSYM || nextTokenCode == FLOATSYM){
        match(nextTokenCode);
        IdentList();
    } else {
        syntaxError("Unexpected token in Declaration");
    }
}

void SyntaxAnalyzer::Block() {
//    cout << "IN BLOCK FUNCTION" << endl;
    if(nextTokenCode == LBRACE){
        CompStmt();
    } else {
        Statement();
    }
}

void SyntaxAnalyzer::IdentList() {
//    cout << "IN IDENTLIST FUNCTION" << endl;
    match(IDENT);
    if(nextTokenCode == COMMA){
        match(COMMA);
        IdentList();
    }
}

void SyntaxAnalyzer::Expression(){
//    cout << "IN EXPRESSION FUNCTION" << endl;
    if(nextTokenCode == IDENT){
        match(IDENT);
        match(ASSIGN);
        Expression();
    } else {
        Or();
    }
};

void SyntaxAnalyzer::Or(){
//    cout << "IN OR FUNCTION" << endl;
    And();
    while(nextTokenCode == OR){
        match(OR);
        And();
    }
}

void SyntaxAnalyzer::And(){
//    cout << "IN AND FUNCTION" << endl;
    Equality();
    while(nextTokenCode == AND){
        match(AND);
        Equality();
    }
}

void SyntaxAnalyzer::Equality() {
//    cout << "IN EQUALITY FUNCTION" << endl;
    Relational();
    while(nextTokenCode == EQL || nextTokenCode == NEQ){
        match(nextTokenCode);
        Relational();
    }
}

void SyntaxAnalyzer::Relational() {
//    cout << "IN RELATION FUNCTION" << endl;
    Term();
    while(nextTokenCode == GTR || nextTokenCode == LSS || nextTokenCode == GEQ || nextTokenCode == LEQ){
        match(nextTokenCode);
        Term();
    }
}

void SyntaxAnalyzer::Term() {
//    cout << "IN TERM FUNCTION" << endl;
    Factor();
    while (nextTokenCode == PLUS || nextTokenCode == MINUS){
        match(nextTokenCode);
        Factor();
    }
}

void SyntaxAnalyzer::Factor() {
//    cout << "IN FACTOR FUNCTION" << endl;
    Unary();
    while(nextTokenCode == TIMES || nextTokenCode == SLASH || nextTokenCode == MOD){
        match(nextTokenCode);
        Unary();
    }
}

void SyntaxAnalyzer::Unary() {
//    cout << "IN UNARY FUNCTION" << endl;
    if(nextTokenCode == NOT){
        match(NOT);
        Primary();
    } else {
        Primary();
    }
}

void SyntaxAnalyzer::Primary() {
//    cout << "IN PRIMARY FUNCTION" << endl;
    switch (nextTokenCode) {
        case LPAREN:
            match(LPAREN);
            Expression();
            match(RPAREN);
            break;
        case IDENT:
            match(IDENT);
            break;
        case NUMLIT:
            match(NUMLIT);
            break;
        case TRUESYM:
            match(TRUESYM);
            break;
        case FALSESYM:
            match(FALSESYM);
            break;
        default:
            syntaxError("Unexpected token in Primary");
            break;
    }

}

void SyntaxAnalyzer::match(TokenCodes expectedTokenCode) {
    if (nextTokenCode == expectedTokenCode) {
        nextToken = la->getNextToken();
        nextTokenCode = nextToken->getTokenCode();
    } else {
        cerr << "NextTokenCode: " << nextTokenCode << endl;
        cerr << "ExpectedTokenCode: " << expectedTokenCode << endl;
        syntaxError("Expected token not found");
    }
}

void SyntaxAnalyzer::syntaxError(const std::string &message) {
    int errorPosition = la->getCurrentTokenPosition();
    cout << string(errorPosition, ' ') << '^' << endl;
    cout << "Syntax Error: " << message << endl;
    exit(0);
}