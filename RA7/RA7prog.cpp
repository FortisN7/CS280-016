#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <iterator>
#include <map>


using namespace std;
void PostfixEval(string instr);

int main ( ) 
{
	//ifstream file;
	string instr;
	cout<<"Please enter a postfix expression for evalution, using only single lowercase characters as variables:" << endl;
	getline(cin, instr);
	//cout << instr << endl;
	PostfixEval(instr);
	//cout << endl;
	//cout<<"Thank you." << endl;
	
	
	return 0;	
}