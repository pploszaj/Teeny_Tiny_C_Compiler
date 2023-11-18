#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream sourceCodeFile;
    LexicalAnalyzer *la;
    SyntaxAnalyzer *parser;

    sourceCodeFile.open(argv[1], ifstream::in);
    if  (sourceCodeFile.is_open())
    {
        la = new LexicalAnalyzer(&sourceCodeFile);
        parser = new SyntaxAnalyzer(la);
        parser->Program();
    }
    else
        cout << "ERROR - cannot open input file." << endl;

    return 0;
}
