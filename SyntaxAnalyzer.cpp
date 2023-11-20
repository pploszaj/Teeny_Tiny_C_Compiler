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
    cout << "The program is syntactically correct" << endl;
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

void SyntaxAnalyzer::CompStmt() {
    match(LBRACE);
    SeqOfStmt();
    match(RBRACE);
}

void SyntaxAnalyzer::SeqOfStmt() {
    while(nextTokenCode != RBRACE){
        Statement();
    }
}

void SyntaxAnalyzer::Statement() {
    switch (nextTokenCode) {
        case BOOL:
        case INT:
        case FLOAT:
            Declaration();
            match(SEMICOLON);
            break;

        case DO:
            match(DOSYM);
            Block();
            match(WHILE);
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
    if(nextTokenCode == BOOLSYM || nextTokenCode == INTSYM || nextTokenCode == FLOATSYM){
        match(nextTokenCode);
        IdentList();
    } else {
        syntaxError("Unexpected token in Declaration");
    }
}

void SyntaxAnalyzer::Block() {
    if(nextTokenCode == LBRACE){
        CompStmt();
    } else {
        Statement();
    }
}

void SyntaxAnalyzer::IdentList() {
    match(IDENT);
    if(nextTokenCode == COMMA){
        match(COMMA);
        IdentList();
    }
}

void SyntaxAnalyzer::Expression(){
    if(nextTokenCode == IDENT){
        match(IDENT);
        match(ASSIGN);
        Expression();
    } else {
        Or();
    }
};

void SyntaxAnalyzer::Or(){
    And();
    while(nextTokenCode == OR){
        match(OR);
        And();
    }
}

void SyntaxAnalyzer::And(){
    Equality();
    while(nextTokenCode == AND){
        match(AND);
        Equality();
    }
}

void SyntaxAnalyzer::Equality() {
    Relational();
    while(nextTokenCode == EQL || nextTokenCode == NEQ){
        match(nextTokenCode);
        Relational();
    }
}

void SyntaxAnalyzer::Relational() {
    Term();
    while(nextTokenCode == GTR || nextTokenCode == LSS || nextTokenCode == GEQ || nextTokenCode == LEQ){
        match(nextTokenCode);
        Term();
    }
}

void SyntaxAnalyzer::Term() {
    Factor();
    while (nextTokenCode == PLUS || nextTokenCode == MINUS){
        match(nextTokenCode);
        Factor();
    }
}

void SyntaxAnalyzer::Factor() {
    Unary();
    while(nextTokenCode == TIMES || nextTokenCode == SLASH || nextTokenCode == MOD){
        match(nextTokenCode);
        Unary();
    }
}

void SyntaxAnalyzer::Unary() {
    if(nextTokenCode == NOT){
        match(NOT);
        Primary();
    } else {
        Primary();
    }
}

void SyntaxAnalyzer::Primary() {
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
        syntaxError("Expected token not found");
    }
}

void SyntaxAnalyzer::syntaxError(const std::string &message) {
    int errorPosition = la->getCurrentTokenPosition();
    cout << string(errorPosition, ' ') << '^' << endl;
    cout << "Syntax Error: " << message << endl;
    exit(0);
}