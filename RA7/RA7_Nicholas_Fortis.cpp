#include <iostream>
#include <stack>
#include <regex>
#include <map>
#include <sstream>

using namespace std;

void PostfixEval(string instr) {
    regex number("[0-9]+");
    regex variable("[$]?[a-z]");
    map<char, int> variables;
    stack<int> nums;
    stringstream in(instr);
    string item;
    
    while (in >> item) {
        if(regex_match(item, number)) /*is number*/ {
            nums.push(stoi(item));
        }
        else if(regex_match(item, variable)) {
            if (item[0] == '$') /*starts with a '$'*/ {
                nums.push(variables[item[1]]);
            }
            else {
                variables[item[0]] = nums.top();
                nums.pop();
            }
        }
        else {
            int num1 = nums.top();
            nums.pop();
            int num2 = nums.top();
            nums.pop();
            switch(item[0]) {
                case '+':
                    nums.push(num1 + num2);
                    break;
                case '-':
                    nums.push(num1 - num2);
                    break;
                case '*':
                    nums.push(num1 * num2);
                    break;
                case '/':
                    nums.push(num1 / num2);
                    break;
                default:
                    cerr << "Error: Incomplete input postfix expression." << endl;
            }
        }
        
        cout << "The result of evaluating the postfix expression \"" << instr << "\" is the value: " << nums.top() << endl;
    }
    
}

int main(int argc, char *argv[]) {
    return 0;
}