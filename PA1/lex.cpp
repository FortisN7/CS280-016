#include "lex.h"
#include <ctype.h>
#include <algorithm>

Token token;

LexItem getNextToken(istream& in, int& linenum) {
    enum TokState {START, ININT, INREAL, INID, INSTRING} lexstate = START;
    string lexeme;
    char ch;
    string line;
    char peek;
    char peek2;
    while(in.get(ch)) {
        lexeme = ch;
        switch(lexstate) {
        case START:
            if (ch == '#') {               
                getline(in, line);
                break;
            }
            else if (ch == ' ') {
                break;
            }
            else if (ch == '@' || ch == '$' || isalpha(ch) || ch == '_') {
                lexstate = INID;
            }
            //else if (isalpha(ch) || ch == '_') {
                
            //}
            else if (isdigit(ch)) {
                lexstate = ININT;
            }
            else if (ch == '\'') {
                lexstate = INSTRING;
            }
            else if (ch == '+') {
                return LexItem(PLUS, lexeme, linenum);
            }
            else if (ch == '-') {
                peek = in.get();
                peek2 = in.peek();
                if (isalpha(peek) && isalpha(peek2)) {
                    lexeme = (tolower(ch) + tolower(peek) + tolower(peek2));
                    if (lexeme == "-eq") {
                        return LexItem(SEQ, lexeme, linenum);
                    }
                    else if (lexeme == "-lt") {
                        return LexItem(SLTHAN, lexeme, linenum);
                    }
                    else if (lexeme == "-gt") {
                        return LexItem(SGTHAN, lexeme, linenum);
                    }
                    else {
                        return LexItem(ERR, lexeme, linenum);
                    }
                }
                else {
                    in.putback(peek);
                    return LexItem(MINUS, lexeme, linenum);
                }
            }
            else if (ch == '*') {
                peek = in.peek();
                if (peek == '*') {
                    lexeme = (ch + peek); // "**"
                    return LexItem(SREPEAT, lexeme, linenum);
                }
                return LexItem(MULT, lexeme, linenum);
            }
            else if (ch == '/') {
                return LexItem(DIV, lexeme, linenum);
            }
            else if (ch == '^') {
                return LexItem(EXPONENT, lexeme, linenum);
            }
            else if (ch == '=') {
                peek = in.peek();
                if (peek == '=') {
                    lexeme = (ch + peek); // "=="
                    return LexItem(NEQ, lexeme, linenum);
                }
                return LexItem(ASSOP, lexeme, linenum);
            }
            else if (ch == '(') {
                return LexItem(LPAREN, lexeme, linenum);
            }
            else if (ch == ')') {
                return LexItem(RPAREN, lexeme, linenum);
            }
            else if (ch == '{') {
                return LexItem(LBRACES, lexeme, linenum);
            }
            else if (ch == '}') {
                return LexItem(RBRACES, lexeme, linenum);
            }
            else if (ch == '>') {
                return LexItem(NGTHAN, lexeme, linenum);
            }
            else if (ch == '.') {
                return LexItem(CAT, lexeme, linenum);
            }
            else if (ch == ',') {
                return LexItem(COMMA, lexeme, linenum);
            }
            else if (ch == ';') {
                return LexItem(SEMICOL, lexeme, linenum);
            }
            //break;
            return LexItem(ERR, lexeme, linenum);
        case ININT:
            while(in.get(ch)) {
                if (isdigit(ch)) {
                    lexeme += ch;
                }
                else if (ch == '.') {
                    lexeme += ch;
                    lexstate = INREAL;
                    break;
                }
                else {
                    in.putback(ch);
                    return LexItem(ICONST, lexeme, linenum);
                }
            }
            break;
        case INREAL:
            while(in.get(ch)) {
                if (isdigit(ch)) {
                    lexeme += ch;
                }
                else if (ch == '.') {
                    lexeme += ch;                
                    return LexItem(ERR, lexeme, linenum);
                }
                else {
                    lexstate = START;
                    return LexItem(RCONST, lexeme, linenum);
                }
            }
            break;
        case INID:
            while(in.get(ch)) {               
                if (isalpha(ch) || ) { //add more conditions
                    
                }
                else {
                    return id_or_kw(lexeme, linenum);
                }
            }
            break;     
        case INSTRING:
            while(in.get(ch)) {
                lexeme += ch;
                if (ch == '\'') {
                    return LexItem(SCONST, lexeme, linenum);
                }
                else if (ch == '\n') { // Might have to add || ch == '\"'
                    return LexItem(ERR, lexeme, linenum);
                }
            }
            break;
        // Insert here if more states are needed
        }
    }
    return LexItem(DONE, lexeme, linenum);
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    Token token;

    if (lexeme[0] == '@') {
        token = SIDENT;
    } 
    else if (lexeme[0] == '$') {
        token = NIDENT;
    }
    else {
        token = IDENT;
    }

    transform(lexeme.begin(), lexeme.end(), lexeme.begin(), ::toupper);
    cout << lexeme;

    map<string, Token> maps = {
        {"WRITELN", WRITELN}, {"IF", IF}, {"ELSE", ELSE}
    };
    map<string, Token>::iterator it;
    for(it = maps.begin(); it != maps.end(); it++) {
        if (maps.count(lexeme) > 0)
            return LexItem(maps[lexeme], lexeme, linenum);
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
            return out << "WRITELN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case IF:
            return out << "IF: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case ELSE:
            return out << "ELSE: \"" << lexeme << "\" at Line " << line << endl;
            break;
        // Identifiers
        case IDENT:
            return out << "IDENT(" << lexeme << ")" << endl;
            break;
        case NIDENT:
            return out << "NIDENT(" << lexeme << ")" << endl;            
            break;
        case SIDENT:
            return out << "SIDENT(" << lexeme << ")" << endl;            
            break;
        // Constants
        case ICONST:
            return out << "ICONST(" << lexeme << ")" << endl;            
            break;
        case RCONST:
            return out << "RCOSNT(" << lexeme << ")" << endl;            
            break;
        case SCONST:
            return out << "SCONST(" << lexeme << ")" << endl;            
            break;
        // Operators
        case PLUS:
            return out << "PLUS" << endl;
            break;
        case MINUS:
            return out << "MINUS" << endl;
            break;
        case MULT:
            return out << "MULT" << endl;
            break;
        case DIV:
            return out << "DIV" << endl;
            break;
        case EXPONENT:
            return out << "EXPONENT" << endl;
            break;
        case ASSOP:
            return out << "ASSOP" << endl;
            break;
        case NEQ:
            return out << "NEQ" << endl;
            break;
        case NGTHAN:
            return out << "NGTHAN" << endl;
            break;
        case NLTHAN:
            return out << "NLTHAN" << endl;
            break;
        case CAT:
            return out << "CAT" << endl;
            break;
        case SREPEAT:
            return out << "SREPEAT" << endl;
            break;
        case SEQ:
            return out << "SEQ" << endl;
            break;
        case SGTHAN:
            return out << "SGTHAN" << endl;
            break;
        case SLTHAN:
            return out << "SLTHAN" << endl;
            break;
        // Keyword tokens
        case COMMA:
            return out << "COMMA" << endl;
            break;
        case LPAREN:
            return out << "LPAREN" << endl;
            break;
        case RPAREN:
            return out << "RPAREN" << endl;
            break;
        case LBRACES:
            return out << "LBRACES" << endl;
            break;
        case RBRACES:
            return out << "RBRACES" << endl;
            break;
        case SEMICOL:
            return out << "SEMICOL" << endl;
            break;
        // ERR
        case ERR:
            //Error in line 2 (27.57.)
            return out << "Error in line " << line << " (" << lexeme << ")" << endl;
            break;
        // DONE
        case DONE:
            return out << "DONE" << endl;
            break;
    }
    return out << endl;
}