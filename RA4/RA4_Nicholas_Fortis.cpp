#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

bool isSpecialName(string word) {
    if (word[0] == '$' && word.length() > 1 && isalpha(word[1]) && isalpha(word[word.length()-1])) {

        return true;
    }
    else {
        return false;
    }
}

bool isInteger(string word) {
    if ((word[0] == '+' && isdigit(word[1]) == true) || (word[0] == '-' && isdigit(word[1]) == true) || (isdigit(word[0]) == true)) {
        for (int i = 1; i < word.length(); i++) {
            if (isdigit(word[i]) != true) {
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool isReal(string word) {
    int decimalCounter = 0;

    if ((word[0] == '+' && isdigit(word[1]) == true) || (word[0] == '-' && isdigit(word[1]) == true) || (isdigit(word[0]) == true)) {
        for (int i = 1; i < word.length(); i++) {
            if (word[i] == '.') {
                decimalCounter++;
            }
            if ((isdigit(word[i]) != true  && word[i] != '.') || decimalCounter > 1) {
                return false;
            }
        }
    }

    if (decimalCounter == 1 && isdigit(word[word.length()-1])) {
        return true;
    }
    else {
        return false;
    }

    return false;
}

int main(int argc, char *argv[]) {
    string fileName, line, word;
    ifstream fin;
    int wordCounter = 0;
    int lineCounter = 0;
    int integerCounter = 0;
    int realCounter = 0;
    int specialNamesCounter = 0;
    map<string, int> specialNamesMap;
    map<int, int> integerMap;
    map<float, int> realMap;
    
    if (argc < 2) {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
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
        lineCounter++;
        istringstream iss(line);
        while (iss >> word) {
            if (isSpecialName(word)) {
                specialNamesCounter++;
                if (specialNamesMap.find(word) == specialNamesMap.end()) {
                    specialNamesMap[word] = 1;
                }
                else {
                    specialNamesMap[word]++;
                }
            }
            if (isInteger(word)) {
                integerCounter++;
                if (word[0] == '+') {
                    word = word.substr(1,word.length());
                }
                int intWord;
                stringstream ss;
                ss << word;
                ss >> intWord;
                if (integerMap.find(intWord) == integerMap.end()) {
                    integerMap[intWord] = 1;
                }
                else {
                    integerMap[intWord]++;
                }
            }
            if (isReal(word)) {
                realCounter++;
                if (word[0] == '+') {
                    word = word.substr(1,word.length());
                }
                if (isdigit(word[word.length()-2]) == true && word[word.length()-1] == '0') {
                    word = word.substr(0, word.length()-1);
                }
                float floatWord = stof(word);
                if (realMap.find(floatWord) == realMap.end()) {
                    realMap[floatWord] = 1;
                }
                else {
                    realMap[floatWord]++;
                }
            }

            wordCounter++;
        }
    }

    if (wordCounter == 0 && lineCounter == 1) {
        cout << "File is empty." << endl;
        return 1;
    }
    else {
        cout << "Number of integers in the file: " << integerCounter << endl;
        cout << "Number of reals in the file: " << realCounter << endl;
        cout << "Number of special names in the file: " << specialNamesCounter << endl;
        if (integerMap.empty() == false || specialNamesMap.empty() == false || realMap.empty() == false) {
            cout << endl;
        }

        if (integerMap.empty() == false) {
            cout << "List of integer values and their number of occurrences:" << endl;
            for (map<int, int>::iterator it = integerMap.begin(); it != integerMap.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            }
            if (specialNamesMap.empty() == false || realMap.empty() == false) {
                cout << endl;
            }
        }
        if (realMap.empty() == false) {
            cout << "List of real values and their number of occurrences:" << endl;
            for (map<float, int>::iterator it = realMap.begin(); it != realMap.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            }
            if (specialNamesMap.empty() == false) {
                cout << endl;
            }
        }
        if (specialNamesMap.empty() == false) {
            cout << "List of special names and their number of occurrences:" << endl;
            for (map<string, int>::iterator it = specialNamesMap.begin(); it != specialNamesMap.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            }
        }
    }

    fin.close();
    return 0;
}