#include "lex.h"

LexItem id_or_kw(const string& lexeme, int linenum) {
    Token token;

    if (lexeme[0] == '@') {
        //SIDENT;
    } 
    else if (lexeme[0] == '$') {
        //NIDENT;
    }
    else {
        //IDENT;
    }

    map<string, Token> maps = {
        {"WRITELN", WRITELN}, {"IF", IF}, {"ELSE", ELSE}
    };
    map<string, Token>::iterator it;
    for(it = maps.begin(); it != maps.end(); it++) {
        //if lexeme is found in the map, return the LexItem object
        return LexItem()
    }
    return LexItem(token, lexeme, linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok) {
    int line;
    line = tok.GetLinenum();
    Token toks = tok.GetToken();
    string lexeme = tok.GetLexeme();

    switch(toks) {
        // Keywords
        case WRITELN:
            out << "WRITELN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case IF:
            out << "IF: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case ELSE:
            out << "ELSE: \"" << lexeme << "\" at Line " << line << endl;
            break;
        // Identifiers
        case IDENT:
            break;
        case NIDENT:
            break;
        case SIDENT:
            break;
        // Constants
        case ICONST:
            break;
        
        // Operators

        // ERR

    })
}