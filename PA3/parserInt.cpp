/* Implementation of Recursive-Descent Parser
 * parserInt.cpp
 * Programming Assignment 3
 * Spring 2023
*/

//renamed parser.cpp given in canvas

#include "parserInt.h"

map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; //Container of temporary locations of Value objects for results of expressions, variables values and constants 
queue <Value> * ValQue; //declare a pointer variable to a queue of Value objects

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}

//Why is this here... irrelevant
//bool IdentList(istream& in, int& line);


//Program is: Prog ::= StmtList
bool Prog(istream& in, int& line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);
	
	
	if(tok.GetToken() == DONE && tok.GetLinenum() <= 1){
		ParseError(line, "Empty File");
		return true;
	}
	Parser::PushBackToken(tok);
	f1 = StmtList(in, line); 
			
	if(!f1) 
	{
		ParseError(line, "Missing Program");
		return false;
	}
	else 
		return true;
}//End of Prog

//StmtList ::= Stmt; { Stmt; }
bool StmtList(istream& in, int& line){
	bool status;
		
	LexItem tok;
	
	status = Stmt(in, line);
	while(status )
	{
		tok = Parser::GetNextToken(in, line);
		if(tok == DONE)
		{
            cout << "(" << "DONE" << ")" << endl;
			Parser::PushBackToken(tok);
			return true;
		}
		else if(tok == RBRACES)
		{
			Parser::PushBackToken(tok);
			return true;
		}
		
		if(tok != SEMICOL)
		{
			ParseError(line, "Missing semicolon at end of Statement.");
			return false;
		}
		
		status = Stmt(in, line);
		
	}
			
	tok = Parser::GetNextToken(in, line);
	if(tok == ELSE )
	{
		ParseError(line, "Missing right brace.");
		return false;
	}
	else if(tok == RBRACES)
	{
		Parser::PushBackToken(tok);
		return true;
	}
	
	else 
	{
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}
	
}//End of StmtList function

//Stmt ::= AssignStme | WriteLnStmt | IfStmt  
bool Stmt(istream& in, int& line){
	bool status=false;
	
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {
	case SIDENT: case NIDENT: 
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		if(!status)
		{
			ParseError(line, "Incorrect Assignment Statement.");
			return status;
		}
		break;
	case WRITELN:
		
		status = WritelnStmt(in, line);
		
		if(!status)
		{
			ParseError(line, "Incorrect Writeln Statement.");
			return status;
		}
		break;
	case IF:  
		status = IfStmt(in, line);
		
		if(!status)
		{
			ParseError(line, "Incorrect If-Statement.");
			return status;
		}
		break;
	case ELSE:
		Parser::PushBackToken(t);
		return false;
		break;
	case IDENT:
		ParseError(line, "Invalid variable name");
	
		Parser::PushBackToken(t);
		return false;
		break;
	default:
		Parser::PushBackToken(t);
		return true;
	}
	return status;
}//End of Stmt function


//WritelnStmt:= WRITELN (ExpreList) 
bool WritelnStmt(istream& in, int& line) {
	LexItem t;
	ValQue = new queue<Value>;
		
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression list after Print");
		while(!(*ValQue).empty())
		{
			ValQue->pop();		
		}
		delete ValQue;
		return false;
	}
	
	//Evaluate: writeln by printing out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	return true;
}//End of WritelnStmt

//IfStmt:= IF (Expr) '{' StmtList '}' [ Else '{' StmtList '}' ] 
bool IfStmt(istream& in, int& line) {
	bool ex = false, status ; 
	LexItem t;
	Value retVal;
	
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis of If condition");
		return false;
	}
	
	ex = Expr(in, line, retVal);
	if( !ex ) {
		ParseError(line, "Missing if statement Logic Expression");
		return false;
	}
	if (!retVal.IsBool()) {
		ParseError(line, "Illegal logic operation in if.");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis of If condition");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != LBRACES)
	{
		ParseError(line, "If Statement Syntax Error: Missing left brace");
		return false;
	}
	Value saveState = retVal;
	
	if(saveState.GetBool()){
		status = StmtList(in, line);
		if(!status)
		{
			ParseError(line, "Missing Statement for If-Stmt If-Part");
			return false;
		}
		t = Parser::GetNextToken(in, line);
	}
	while((t.GetToken() != ELSE || t.GetToken()!=RBRACES || t.GetToken()!= DONE) && !saveState.GetBool()){
		t = Parser::GetNextToken(in, line);
		if(t.GetToken() == ELSE || t.GetToken()==RBRACES || t.GetToken()== DONE){
			break;
		}
	}
	t = Parser::GetNextToken(in, line);
	if( t != RBRACES)
	{
		ParseError(line, "If Statement Syntax Error: Missing right brace.");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	
	if( t == ELSE ) {
		t = Parser::GetNextToken(in, line);
		if(t != LBRACES)
		{
			ParseError(line, "If Statement Syntax Error: Missing left brace");
			return false;
		}
		if (saveState.GetBool()) {
			while(t.GetToken() != RBRACES || t.GetToken() !=DONE){
				t = Parser::GetNextToken(in, line);
				if (t.GetToken() == RBRACES) {
					break;
				}
			}
		}
		else {
			status = StmtList(in, line);
			if(!status)
			{
				ParseError(line, "Missing Statement for If-Stmt Else-Part");
				return false;
			}
			else {
				t = Parser::GetNextToken(in, line);
			}
		}
		if( t != RBRACES)
		{
			Parser::PushBackToken(t);
			ParseError(line, "If Statement Syntax Error: Missing right brace.");
			return false;
		}
		//Parser::PushBackToken(t);
	}
	else
	{
		Parser::PushBackToken(t);
		return true;
	}
	return true;
}//End of IfStmt function

//Var ::= NIDENT | SIDENT
bool Var(istream& in, int& line, LexItem & idtok)
{
	string identstr;
	
	idtok = Parser::GetNextToken(in, line);
	
	if (idtok == NIDENT || idtok == SIDENT){
		identstr = idtok.GetLexeme();
		
		if (!(defVar.find(identstr)->second))
		{
			defVar[identstr] = true;
			SymTable[identstr] = idtok.GetToken();
			TempsResults[identstr] = Value();
		}	
		return true;
	}
	else if (idtok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << idtok.GetLexeme() << ")" << endl;
		return false;
	}
	
	return false;
}//End of Var

//AssignStmt:= Var = Expr
bool AssignStmt(istream& in, int& line) {
	bool varstatus = false, status = false;
	LexItem t;
	Value retVal;
	string identString = t.GetLexeme();
	Token type = SymTable[identString];
	//idk what to put in there i think t makes sense
	varstatus = Var( in, line, t);
	
	if (varstatus){
		t = Parser::GetNextToken(in, line);
		
		if (t == ASSOP){
			status = Expr(in, line, retVal);
			
			if(!status) {
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}
			if((type == ICONST || type == RCONST || type == NIDENT) && retVal.IsString()){
				ParseError(line, "Illegal Assignment Operation");
				return false;
			}
			else if (retVal.IsBool()) {
				TempsResults[identString] = retVal;
			}
			else if (retVal.IsInt()) {
				TempsResults[identString] = retVal;
			}
			else if (retVal.IsReal()) {
				TempsResults[identString] = retVal;
			}
			else if(retVal.IsReal()){
				TempsResults[identString] = (int)retVal.GetReal();
			}
			else if(retVal.IsInt()){
				TempsResults[identString] = Value(static_cast< double >(retVal.GetInt()));
			}
			else if(retVal.IsString()){
				TempsResults[identString] = retVal;
			}
			else {
				ParseError(line, "Value type does not match.");
				return false;
			}
		}
		else if(t.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << t.GetLexeme() << ")" << endl;
			return false;
		}
		else {
			ParseError(line, "Missing Assignment Operator");
			return false;
		}
	}
	else {
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}
	return status;	
}//End of AssignStmt

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	Value retVal;
	
	status = Expr(in, line, retVal);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	ValQue->push(retVal);
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		status = ExprList(in, line);
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//End of ExprList

//Expr ::= EqualExpr ::= RelExpr [(-EQ|==) RelExpr ]
bool Expr(istream& in, int& line, Value& retVal) {
	LexItem tok;
	Value val1, val2;
	bool t1 = RelExpr(in, line, val1);
	if( !t1 ) {
		return false;
	}
	retVal = val1;
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if ( tok == NEQ || tok == SEQ ) 
	{
		t1 = RelExpr(in, line, val2);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == NEQ){
			retVal = retVal == val2;
		}
		else if (tok == SEQ) {
			retVal = retVal.SEqual(val2);
		}

		if(retVal.IsErr()){
			ParseError(line, "Illegal operation in Expr.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Expr/EqualExpr

//RelExpr ::= AddExpr [ ( -LT | -GT | < | > )  AddExpr ]
bool RelExpr(istream& in, int& line, Value& retVal) {
	LexItem tok;
	Value val1, val2;
	bool t1 = AddExpr(in, line, val1);
		
	if( !t1 ) {
		return false;
	}
	retVal = val1;
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if ( tok == NGTHAN || tok == NLTHAN || tok == SGTHAN || tok == SLTHAN ) 
	{
		t1 = AddExpr(in, line, val2);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if(tok == NLTHAN) {
			retVal = retVal < val2;
		}
		else if(tok == NGTHAN) {
			retVal = retVal > val2;
		}
		else if (tok == SGTHAN) {
			retVal = retVal.SGthan(val2);
		}
		else if (tok == SLTHAN) {
			retVal = retVal.SLthan(val2);
		}
		if(retVal.IsErr()){
			ParseError(line, "Illegal operation in RelExpr.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	
	Parser::PushBackToken(tok);
	return true;
}//End of RelExpr

//AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream& in, int& line, Value& retVal) {
	Value val1, val2;
	bool t1 = MultExpr(in, line, val1);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	retVal = val1;
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while (tok == PLUS || tok == MINUS || tok == CAT) 
	{
		t1 = MultExpr(in, line, val2);
		if ( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == PLUS) {
			retVal = retVal + val2;
		}
		else if (tok == MINUS) {
			retVal = retVal - val2;
		}
		else if (tok == CAT) {
			retVal = retVal.Catenate(val2);
		}
		if(retVal.IsErr()){
			ParseError(line, "Illegal operation in AddExpr.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of AddExpr

//MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream& in, int& line, Value& retVal) {
	Value val1, val2;
	bool t1 = ExponExpr(in, line, val1);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	retVal = val1;
	tok	= Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
	}
	while ( tok == MULT || tok == DIV  || tok == SREPEAT)
	{
		t1 = ExponExpr(in, line, val2);
		
		if ( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		if (tok == MULT) {
			retVal = retVal * val2;
		}
		else if (tok == DIV) {
			retVal = retVal/val2;
		}
		else if (tok == SREPEAT) {
			retVal = retVal.Repeat(val2);
		}
		if(retVal.IsErr()){
			ParseError(line, "Illegal operation in MultExpr.");
			return false;
		}
		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of MultExpr

//ExponExpr ::= UnaryExpr { ^ UnaryExpr }
//enforcing right associativity using right recursiveness
bool ExponExpr(istream& in, int& line, Value& retVal)
{
	bool status;
	Value val1, val2;
	status = UnaryExpr(in, line, val1);
	if( !status ) {
		return false;
	}
	retVal = val1;
	LexItem tok = Parser::GetNextToken(in, line);
	if (tok == EXPONENT)
	{
		status = ExponExpr(in, line, val2);
		if( !status ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
        //not sure if val1 or val2
		retVal = retVal^val2;
		if(retVal.IsErr()){
			ParseError(line, "Illegal operation in ExponExpr.");
			return false;
		}
		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	else if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
	}
	Parser::PushBackToken(tok);
	return true;
}//End of ExponExpr

//UnaryExpr ::= ( - | + ) PrimaryExpr | PrimaryExpr
bool UnaryExpr(istream& in, int& line, Value& retVal)
{
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;
	if(t == MINUS ) {
		sign = -1;
	}
	else if(t == PLUS) {
		sign = 1;
	}
	else
		Parser::PushBackToken(t);
		
	status = PrimaryExpr(in, line, sign, retVal);
	return status;
}//End of UnaryExpr


//PrimaryExpr ::= IDENT | SIDENT | NIDENT | ICONST | RCONST | SCONST | (Expr)
bool PrimaryExpr(istream& in, int& line, int sign, Value & retVal) {
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok == IDENT){
		string lexeme = tok.GetLexeme();
		if(!(defVar.find(lexeme)->second)){
			ParseError(line, "Using Undefined Variable");
			return false;	
		}
		retVal = TempsResults[lexeme];
		if (TempsResults[lexeme].IsReal() || TempsResults[lexeme].IsInt()) {
			if (sign == -1) {
				if (TempsResults[lexeme].GetReal() > 0 || TempsResults[lexeme].GetInt() > 0) {
					retVal = Value(TempsResults[lexeme] * -1);
				}
				else{
					retVal = Value(); 
				}
			}
			else if (sign == 1) {
				if (TempsResults[lexeme].GetReal() < 0 || TempsResults[lexeme].GetInt() < 0) {
					retVal = Value(TempsResults[lexeme] * -1);
				}
				else {
					retVal = Value();
				}
			}
		}
		if (retVal.IsErr()) {
			ParseError(line, "Illegal Sign Operator at PrimaryExpr for IDENT");
			return false;	
		}		
		return true;
	}
	if (tok == NIDENT) {
		string lexeme = tok.GetLexeme();
		if (!(defVar.find(lexeme)->second)) {
			ParseError(line, "Using Undefined Variable");
			return false;	
		}
		retVal = TempsResults[lexeme];
		if (sign == -1) {
			if(TempsResults[lexeme].GetReal() > 0 || TempsResults[lexeme].GetInt() > 0) {
				retVal = Value(TempsResults[lexeme] * -1);
			}
			else {
				retVal = Value(); 
			}
		}
		else if (sign == 1) {
			if (TempsResults[lexeme].GetReal() < 0 || TempsResults[lexeme].GetInt() < 0) {
				retVal = Value(TempsResults[lexeme] * -1);
			}
			else {
				retVal = Value();
			}
		}
		if (retVal.IsErr()) {
			ParseError(line, "Illegal Sign Operator at PrimaryExpr for NIDENT");
			return false;	
		}		
		return true;
	}
	else if (tok == SIDENT) {
		retVal = Value(TempsResults[tok.GetLexeme()]);
		return true;
	}
	else if(tok == SCONST) {
		if (sign != 0) {
			ParseError(line, "Illegal Operand Type for Sign Operator");
			return false; 
		}
		retVal = Value(tok.GetLexeme());
		return true;
	}
	else if (tok == ICONST) {
		if (sign == 0) {
			if (tok.GetLexeme().back() == '.') {
				retVal = Value(stod(tok.GetLexeme()));
			}
			retVal = Value(stod(tok.GetLexeme()));
		}
		else if (sign == 1) {
			retVal = Value(abs(stod(tok.GetLexeme())));
		}
		else if (sign == -1) {
			retVal = Value(-1 * abs(stod(tok.GetLexeme())));
		}
		return true;
	}
	else if (tok == RCONST) {
		if (sign == 0) {
			if (tok.GetLexeme().back() == '.') {
				retVal = Value(stoi(tok.GetLexeme()));
			}
			else {
				retVal = Value(stod(tok.GetLexeme()));
			}
		}
		else if (sign == 1) {
			retVal = Value(abs(stod(tok.GetLexeme())));
		}
		else if (sign == -1) {
			retVal = Value(-1 * abs(stod(tok.GetLexeme())));
		}
		return true;
	}
	else if (tok == LPAREN) {
		bool ex = Expr(in, line, retVal);
		if (!ex) {
			ParseError(line, "Missing expression after Left Parenthesis");
			return false;
		}
		if (Parser::GetNextToken(in, line) == RPAREN) {
			return ex;
        }
		else {
			Parser::PushBackToken(tok);
			ParseError(line, "Missing right Parenthesis after expression");
			return false;
		}
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	return false;
}
