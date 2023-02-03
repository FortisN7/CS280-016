#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
    string fileName, line, flag, word;
    ifstream fin;
    int wordCounter = 0;
    int type1Counter = 0;
    int type2Counter = 0;
    
    if (argc < 2) {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 1;
    }

    if (argc < 3) {
        flag = "";
    }
    else {
        flag = string(argv[2]);
    }
    if (flag != "" && flag != "-all" && flag != "-type1" && flag != "-type2") {
        cerr << "UNRECOGNIZED FLAG " << flag << endl;
        return 1;
    }

    fileName = string(argv[1]);
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        return 1;
    }

    while (fin.good()) {
        getline(fin, line);
        istringstream iss(line);
        while (iss >> word) {
            if (word[0] == '$' && word.length() > 1 && isalpha(word[1]) && isalpha(word[word.length()-1])) {    
                type1Counter++;
            }
            if (word[0] == '@' && word.length() > 1 && isalpha(word[1]) && isalpha(word[word.length()-1])) {                
                type2Counter++;
            }
            wordCounter++;
        }
    }

    if (wordCounter == 0) {
        cout << "File is empty." << endl;
        return 1;
    }
    if (flag == "-type1") {
        cout << "Number of Type 1 names: " << type1Counter << endl;
    }
    else if (flag == "-type2") {
        cout << "Number of Type 2 names: " << type2Counter << endl;
    }
    else if (flag == "-all") {
        cout << "Total number of words: " << wordCounter << endl;
        cout << "Number of Type 1 names: " << type1Counter << endl;
        cout << "Number of Type 2 names: " << type2Counter << endl;
    }
    else {
        cout << "Total number of words: " << wordCounter << endl;
        cout << "Total number of Type 1 and Type 2 names: " << type1Counter+type2Counter << endl;
    }

    fin.close();
    return 0;
}