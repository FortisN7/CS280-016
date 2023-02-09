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

}
bool isReal(string word) {

}

int main(int argc, char *argv[]) {
    string fileName, line, word;
    ifstream fin;
    int wordCounter = 0;
    int integerCounter = 0;
    int realCounter = 0;
    int specialNamesCounter = 0;
    map<string, int> specialNamesMap;
    map<string, int> integerMap;
    map<string, int> realMap;
    
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
        istringstream iss(line);
        while (iss >> word) {
            if (isSpecialName(word)) {
                specialNamesCounter++;
                if (specialNamesMap.find(word) == specialNamesMap.end()) {
                    specialNamesMap[word]+=1;
                }
                else {
                    specialNamesMap[word] = 1;
                }
            }
            if (isInteger(word)) {
                integerCounter++;
                if (integerMap.find(word) == integerMap.end()) {
                    integerMap[word]+=1;
                }
                else {
                    integerMap[word] = 1;
                }
            }
            if (isReal(word)) {
                realCounter++;
                if (realMap.find(word) == realMap.end()) {
                    realMap[word]+=1;
                }
                else {
                    realMap[word] = 1;
                }
            }

            wordCounter++;
        }
    }

    if (wordCounter == 0) {
        cout << "File is empty." << endl;
        return 1;
    }
    else {
        cout << "Number of integers in the file: " << integerCounter << endl;
        cout << "Number of reals in the file: " << realCounter << endl;
        cout << "Number of special names in the file: " << specialNamesCounter << endl;
        cout << endl;
        map<string, int>::iterator it;
        cout << "List of integer values and their number of occurrences: " << endl;
        for (it = integerMap.begin(); it != integerMap.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
        
        cout << "List of real values and their number of occurrences: " << endl;
        for (it = realMap.begin(); it != realMap.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
        
        cout << "List of special names and their number of occurrences: " << endl;
        for (it = specialNamesMap.begin(); it != specialNamesMap.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
    }

    fin.close();
    return 0;
}