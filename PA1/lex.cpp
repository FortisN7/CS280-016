#include "lex.h"

Token token;

LexItem getNextToken(istream& in, int& linenum) {


    return LexItem(token, lexeme, linenum);
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    

    return LexItem(token, lexeme, linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok) {
    
    
    return out << endl;
}