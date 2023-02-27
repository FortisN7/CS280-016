#include "lex.h"

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
            return out << "IDENTIFIER: " << lexeme << " at Line " << line << endl;
            break;
        case NIDENT:
            return out << "NIDENT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SIDENT:
            return out << "SIDENT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        // Constants
        case ICONST:
            return out << "ICONST: (" << lexeme << ") at Line " << line << endl;
            break;
        case RCONST:
            return out << "RCONST: (" << lexeme << ") at Line " << line << endl;
            break;
        case SCONST:
            return out << "SCONST: \'" << lexeme << "\' at Line " << line << endl;
            break;
        // Operators
        case PLUS:
            return out << "PLUS: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case MINUS:
            return out << "MINUS: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case MULT:
            return out << "MULT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case DIV:
            return out << "DIV: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case EXPONENT:
            return out << "EXPONENT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case ASSOP:
            return out << "ASSOP: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case NEQ:
            return out << "NEQ: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case NGTHAN:
            return out << "NGTHAN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case NLTHAN:
            return out << "NLTHAN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case CAT:
            return out << "CAT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SREPEAT:
            return out << "SREPEAT: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SEQ:
            return out << "SEQ: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SGTHAN:
            return out << "SGTHAN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SLTHAN:
            return out << "SLTHAN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        // Keyword tokens
        case COMMA:
            return out << "COMMA: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case LPAREN:
            return out << "LPAREN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case RPAREN:
            return out << "RPAREN: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case LBRACES:
            return out << "LBRACES: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case RBRACES:
            return out << "RBRACES: \"" << lexeme << "\" at Line " << line << endl;
            break;
        case SEMICOL:
            return out << "SEMICOL: \"" << lexeme << "\" at Line " << line << endl;
            break;
        // ERR
        case ERR:
            return out << "Error: : \"" << lexeme << "\" at Line " << line << endl;
            break;
        // DONE
        case DONE:
            return out << "DONE: \"" << lexeme << "\" at Line " << line << endl;
            break;
    }
    return out << endl;
}