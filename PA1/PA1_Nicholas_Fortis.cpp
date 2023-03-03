#include "lex.h"
#include <fstream>
#include <map>

int main(int argc, char *argv[]) {
    int lineCounter = 0;
    int tokensCounter = 0;
    int identCounter = 0;
    int numCounter = 0;
    int stringCounter = 0;
    LexItem tok;
    ifstream fin;
    string fileName = string(argv[1]);
    // Unordered map?? maybe just go through the same loop again and just print this time
    map<Token, string> identMap;
    map<Token, float> nconstMap;
    map<Token, string> sconstMap;


    if (argc < 2) {
        cerr << "NO SPECIFIED INPUT FILE." << endl;
        return 1;
    }

    // fix to allow for flags
    // if argc is over two that means there are flags but how do I check for more filenames?
    if (argc > 2) {
        cerr << "ONLY ONE FILE NAME IS ALLOWED." << endl;
        return 1;
    }

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        return 1;
    }

    fin.seekg(0, ios::end);  
    if (fin.tellg() == 0) {    
        cerr << "Lines: " << lineCounter << endl;
        cerr << "Empty File." << endl;
        return 1;
    }



    while ((tok = getNextToken(fin, lineCounter)) != DONE && tok != ERR) {
        lineCounter++;
        // handle flags mode
        // keep required information
        //...
        
    }
    
    if (tok == ERR) {
        operator<<(cout, tok);
    }
    else if (tok == DONE) {

    }

    return 0;
}