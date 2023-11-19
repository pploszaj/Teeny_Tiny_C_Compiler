#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <unordered_map>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
private:
    char currentChar;
    int currentCharIndex;
    int currentTokenPosition;
    ifstream *sourceCodeFile; //A pointer to the ifstream representing the source code file.
    string line; //Contains the current line of source code being analyzed.
    unordered_map<string,TokenCodes> reservedWords;

public:
    bool isEOI(); //Checks if the end of the input file has been reached.
    void readNextLine(); //Reads the next line from the source code file.
    void getNextChar(); // Gets the next character from the line or reads the next line if needed.
    bool isWhiteSpace(); //checks if current character is whitespace
    void skipWhiteSpace(); //skips over any whitespace
    Token* getArithmeticOrParenToken();
    bool isLetter();
    bool isDigit();
    Token* getMultiCharSymbol();
    Token* getReservedWord();
    Token* getIdentifier();
    Token* getNumericLiteral();

//this is where I used to have public
    //constructor that initializes the LexicalAnalyzer object with a file stream pointer
    LexicalAnalyzer(ifstream*);
    //identify and return the next token from the source code
    Token* getNextToken();
    int getCurrentTokenPosition();
};

#endif