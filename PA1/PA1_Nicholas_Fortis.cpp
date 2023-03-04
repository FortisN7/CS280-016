#include "lex.h"
#include <fstream>
#include <map>

int main(int argc, char *argv[]) {
    int lineCounter = 0;
    int identCount = 0;
    int nconstCount = 0;
    int sconstCount = 0;
    int tokensCounter = 0;
    LexItem tok;
    ifstream fin;
    string fileName;
    map<string, Token> identMap;
    map<float, Token> nconstMap;
    map<string, Token> sconstMap;
    bool vFlag = false;
    bool nconstFlag = false;
    bool sconstFlag = false;
    bool identFlag = false;
    int fileNameCounter = 0;

    if (argc == 1) {
        cerr << "NO SPECIFIED INPUT FILE." << endl;
        return 1;
    }
    else {
        for (int i = 1; i < argc; i++) {
            string argument = argv[i];
            if (argument[0] == '-') {
                if (argument == "-v") {
                    vFlag = true;
                }
                else if (argument == "-nconst") {
                    nconstFlag = true;
                }
                else if (argument == "-sconst") {
                    sconstFlag = true;
                }
                else if (argument == "-ident") {
                    identFlag = true;
                }
                else {
                    cerr << "UNRECOGNIZED FLAG {" << argument << "}" << endl;
                    return 1;
                }
            }
            else {
                fileName = string(argv[1]);
                fileNameCounter++;
                if (fileNameCounter > 1) {
                    cerr << "ONLY ONE FILE NAME IS ALLOWED." << endl;
                    return 1;
                }
            }
        }
    }

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        return 1;
    }

    fin.seekg(0, ios::end);
    if(fin.tellg() < 1){
        //empty
        cerr << "Lines: " << lineCounter << endl;
        cerr << "Empty File." << endl;
        return 1;
    }
    else {
        //not empty
        fin.clear(); // clear all flags(eof)
        fin.seekg(0, ios::beg); // reset to front
    } 

    while ((tok = getNextToken(fin, lineCounter)) != DONE && tok != ERR) {
        tokensCounter++;
        if (tok.GetToken() == IDENT || tok.GetToken() == NIDENT || tok.GetToken() == SIDENT) {
            identMap.insert({tok.GetLexeme(), tok.GetToken()});
        }
        else if (tok.GetToken() == ICONST || tok.GetToken() == RCONST) {
            nconstMap.insert({stof(tok.GetLexeme()), tok.GetToken()});
        }
        else if (tok.GetToken() == SCONST) {
            sconstMap.insert({tok.GetLexeme(), tok.GetToken()});
        }
        
        if (vFlag) {
            operator<<(cout, tok);
        }  
    }
    
    identCount = identMap.size();
    nconstCount = nconstMap.size();
    sconstCount = sconstMap.size();

    if (tok == ERR) {
        operator<<(cout, tok);
        return 1;
    }
    else if (tok == DONE) {
        cout << endl;
        cout << "Lines: " << lineCounter << endl;
        cout << "Total Tokens: " << tokensCounter << endl;
        cout << "Identifiers: " << identCount << endl;
        cout << "Numbers: " << nconstCount << endl;
        cout << "Strings: " << sconstCount << endl;

        int itCount = 0;
        if (identFlag) {
            cout << "IDENTIFIERS:" << endl;
            for (map<string, Token>::iterator it = identMap.begin(); it != identMap.end(); it++) {
                itCount++;
                if (itCount == identCount) {
                    cout << it->first;
                }
                else {
                    cout << it->first << ", ";
                }
            }
            cout << endl;
        }
        if (nconstFlag) {
            cout << "NUMBERS:" << endl;
            for (map<float, Token>::iterator it = nconstMap.begin(); it != nconstMap.end(); it++) {
                cout << it->first << endl;
            }
        }
        if (sconstFlag) {
            cout << "STRINGS:" << endl;
            for (map<string, Token>::iterator it = sconstMap.begin(); it != sconstMap.end(); it++) {
                cout << "'" << it->first << "'" << endl;
            }
        }
    }

    return 0;
}