/* Implementation of Recursive-Descent Parser
 * parser.cpp
 * Programming Assignment 2
 * Spring 2023
*/

#include "parser.h"

map<string, bool> defVar;
map<string, Token> SymTable;

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

//Prog ::= StmtList
bool Prog(istream& in, int& line) {
	bool status = false;
	
	//cout << "in Prog and before calling StmtList" << endl;
	status = StmtList(in, line);
	if(!status) {
		ParseError(line, "Missing StmtList");
		return false;
	}
	cout << "(DONE)" << endl;
	return true;
}//End of Prog

//StmtList ::= Stmt ;{ Stmt; }
bool StmtList(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = Stmt(in, line);
	if(!status) {
		ParseError(line, "Missing Stmt");
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok == SEMICOL) {
		//cout << "before calling StmtList" << endl;
		status = StmtList(in, line);
		//cout << "after calling StmtList" << endl;
		tok = Parser::GetNextToken(in, line);
		if(tok == DONE) {

		}
		else {
			Parser::PushBackToken(tok);
		}
	}
	else if(tok == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		return false;
	}
	else {
		Parser::PushBackToken(tok);
		return true;
	}
	return status;

}//End of StmtList

//Stmt ::= AssignStmt | WriteLnStmt | IfStmt
bool Stmt(istream& in, int& line) {
	bool status = false;
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == WRITELN) {
		status = WritelnStmt(in, line);
	}
	else if (tok == IF) {
		status = IfStmt(in, line);
	}
	else if (tok == NIDENT || tok == SIDENT) {
		Parser::PushBackToken(tok);
		status = AssignStmt(in, line);
	}
	else {
		ParseError(line, "Missing AssignStmt, WriteLnStmt, or IfStmt");
		return false;
	}

	return status;

}//End of Stmt

//WritelnStmt:= writeln (ExprList) 
bool WritelnStmt(istream& in, int& line) {
	LexItem tok;
	//cout << "in Writeln Stmt" << endl;
	
	tok = Parser::GetNextToken(in, line);
	if(tok != LPAREN) {
		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if(!ex) {
		ParseError(line, "Missing expression list after Print");
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok != RPAREN) {
		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	//Evaluate: print out the list of expressions values

	return true;
}//End of WritelnStmt

//IfStmt ::= if (Expr) ‘{‘ StmtList ‘}’ [ else ‘{‘ StmtList ‘}’ ]
bool IfStmt(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	tok = Parser::GetNextToken(in, line);
	if(tok != LPAREN) {
		ParseError(line, "Missing Left Parethesis of If Statement");
		return false;
	}

	status = Expr(in, line);
	if(!status) {
		ParseError(line, "Missing expression IfStmt");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok != RPAREN) {
		ParseError(line, "Missing Right Parethesis of IfStmt");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok != LBRACES) {
		ParseError(line, "Missing Left Brace of IfStmt");
		return false;
	}

	status = StmtList(in, line);
	if(!status) {
		ParseError(line, "Missing StmtList in IfStmt");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok != RBRACES) {
		ParseError(line, "Missing Right Brace of IfStmt");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == ELSE) {
		tok = Parser::GetNextToken(in, line);
		if(tok != LBRACES) {
			ParseError(line, "Missing Left Brace of ElseStmt in IfStmt");
			return false;
		}

		status = StmtList(in, line);
		if(!status) {
			ParseError(line, "Missing StmtList in ElseStmt in IfStmt");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if(tok != RBRACES) {
			ParseError(line, "Missing Right Brace of ElseStmt in IfStmt");
			return false;
		}
	}
	else {
		Parser::PushBackToken(tok);
	}

	return true;
}//End of IfStmt

//AssignStmt ::= Var = Expr
bool AssignStmt(istream& in, int& line) {
	LexItem tok;
	bool status = false;
	
	status = Var(in, line);
	if(!status) {
		ParseError(line, "Missing Var in AssignStmt");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok != ASSOP) {
		ParseError(line, "Missing ASSOP in AssignStmt");
		return false;
	}

	status = Expr(in, line);
	if(!status) {
		ParseError(line, "Missing Expr in AssignStmt");
		return false;
	}

	return true;
}//End of AssignStmt

//Var ::= NIDENT | SIDENT
bool Var(istream& in, int& line) {
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok == NIDENT) {
		defVar[tok.GetLexeme()] = true;
		return defVar[tok.GetLexeme()];
	}
	else if(tok == SIDENT) {
		defVar[tok.GetLexeme()] = true;
		return defVar[tok.GetLexeme()];
	}
	else {
		ParseError(line, "Unknown variable type in Var");
		return false;
	}

}//End of Var

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	//cout << "in ExprList and before calling Expr" << endl;
	status = Expr(in, line);
	if(!status) {
		ParseError(line, "Missing Expression");
		return false;
	}
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if(tok == COMMA) {
		//cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		//cout << "after calling ExprList" << endl;
	}
	else if(tok == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else {
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//End of ExprList

//Expr ::= RelExpr [(-eq|==) RelExpr ]
bool Expr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = RelExpr(in, line);
	if(!status) {
		ParseError(line, "Missing RelExpr in Expr");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == NEQ || tok == SEQ) {
		status = RelExpr(in, line);
		if(!status) {
			ParseError(line, "Missing Second RelExpr in Expr");
			return false;
		}	
	}
	else {
		Parser::PushBackToken(tok);
	}

	return true;
}//End of Expr

//RelExpr ::= AddExpr [ ( -lt | -gt | < | > ) AddExpr ]
bool RelExpr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = AddExpr(in, line);
	if(!status) {
		ParseError(line, "Missing AddExpr in RelExpr");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == SLTHAN || tok == SGTHAN || tok == NLTHAN || tok == NGTHAN) {
		status = AddExpr(in, line);
		if(!status) {
			ParseError(line, "Missing Second AddExpr in RelExpr");
			return false;
		}	
	}
	else {
		Parser::PushBackToken(tok);
	}

	return true;
}//End of RelExpr

//AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = MultExpr(in, line);
	if(!status) {
		ParseError(line, "Missing MultExpr in AddExpr");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == PLUS || tok == MINUS || tok == CAT) {
		status = MultExpr(in, line);
		if(!status) {
			ParseError(line, "Missing Second MultExpr in AddExpr");
			return false;
		}
	}
	else {
		Parser::PushBackToken(tok);
	}
	return true;
}//End of AddExpr

//MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = ExponExpr(in, line);
	if(!status) {
		ParseError(line, "Missing ExponExpr in MultExpr");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == MULT || tok == DIV || tok == EXPONENT) {
		status = ExponExpr(in, line);
		if(!status) {
			ParseError(line, "Missing Second ExponExpr in MultExpr");
			return false;
		}
	}
	else {
		Parser::PushBackToken(tok);
	}
	return true;
}//End of MultExpr

//ExponExpr ::= UnaryExpr { ^ UnaryExpr }
bool ExponExpr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	status = UnaryExpr(in, line);
	if(!status) {
		ParseError(line, "Missing UnaryExpr in ExponExpr");
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if(tok == SREPEAT) {
		status = UnaryExpr(in, line);
		if(!status) {
			ParseError(line, "Missing Second UnaryExpr in ExponExpr");
			return false;
		}
	}
	else {
		Parser::PushBackToken(tok);
	}
	return true;
}//End of ExponExpr

//UnaryExpr ::= [( - | + )] PrimaryExpr
bool UnaryExpr(istream& in, int& line) {
	bool status = false;
	LexItem tok;

	tok = Parser::GetNextToken(in, line);
	if(tok == MINUS) {
		status = PrimaryExpr(in, line, MINUS);
		if(!status) {
			ParseError(line, "Invalid PrimaryExpr");
			return false;
		}
	}
	else if (tok == PLUS) {
		status = PrimaryExpr(in, line, PLUS);
		if(!status) {
			ParseError(line, "Invalid PrimaryExpr");
			return false;
		}
	}
	else {
		Parser::PushBackToken(tok);
		status = PrimaryExpr(in, line, PLUS);
		if(!status) {
			ParseError(line, "Invalid PrimaryExpr");
			return false;
		}
	}

	return true;
}//End of UnaryExpr

//PrimaryExpr ::= IDENT | SIDENT | NIDENT | ICONST | RCONST | SCONST | (Expr)
bool PrimaryExpr(istream& in, int& line, int sign) { //TODO (look over yk)
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok == LPAREN) {
		if(Expr(in, line)) {
			tok = Parser::GetNextToken(in, line);
			if(tok != RPAREN) {
				ParseError(line, "Missing ')' in (Expr)");
				return false;
			}
		}
	}

	if((tok == SIDENT || tok == NIDENT) && !defVar[tok.GetLexeme()]) {
		ParseError(line, "Using undefined error");
	}

	if(tok != IDENT && tok != SIDENT && tok != NIDENT && tok != ICONST && tok != RCONST && tok != SCONST && !Expr(in, line)) {
		return false;
	}
	return true;
}//End of PrimaryExpr