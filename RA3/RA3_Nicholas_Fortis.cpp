#include <iostream>
#include <fstream>
#include <istringstream>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]){
    string fileName, line, flag;
    ifstream fin;
    int wordCounter = 0;
    int type1Counter = 0;
    int type2Counter = 0;
    
    if (argc < 2) {
        cout << endl; //might not need
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        return 1;
    }

    if (argc < 3) {
        flag = "-all";
    }
    else {
        flag = string(argv[2]);
    }
    if (flag != "-all" || flag != "-type1" || flag != "-type2") {
        cerr << "UNRECOGNIZED FLAG" << flag << endl;
        return 1;
    }

    fileName = string(argv[1]);
    fin.open(fileName.c_str());
    if (!fin) {
        cout << endl; //might not need
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        return 1;
    }

    while (fin.good()) {
        getline(fin, line);
        istringstream iss (line);
        while (iss >> word) {
            
            
            wordCounter++;
        }
    }

    if (wordCounter == 0) {
        cout << "File is empty." << endl;
    }
    if (flag == "-type1"){
        cout << "Total number of words: " << wordCounter << endl;
        cout << "Number of Type 1 names: " << type1Counter << endl;
    }
    else if (flag == "-type2"){
        cout << "Total number of words: " << wordCounter << endl;
        cout << "Number of Type 2 names: " << type2Counter << endl;
    }
    else {
        cout << "Total number of words: " << wordCounter << endl;
        cout << "Number of Type 1 names: " << type1Counter << endl;
        cout << "Number of Type 2 names: " << type2Counter << endl;
    }

    fin.close();
    return 0;
}