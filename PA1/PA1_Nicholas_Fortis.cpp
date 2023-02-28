#include "lex.cpp"

int main(int argc, char *argv[]) {
    int lineNumber = 0;
    LexItem tok;
    ifstream file ;
    .....
    while((tok = getNextToken(file, lineNumber)) != DONE && tok != ERR ) {
        // handle flags mode
        // keep required information
        //...
    }

    return 0;
}