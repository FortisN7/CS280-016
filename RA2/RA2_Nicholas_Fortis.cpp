#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string filename;
    string line;
    int lineCounter;
    ifstream fin;
    cout << "Enter the name of a file to read from: \n" << endl;
    cin >> filename;
    fin.open(filename.c_str());
    if(!fin) {
        cerr << "File cannot be opened " << filename << endl;
        exit(1);
    }

    while(fin.good()) {
        getline(fin, line);
        cout << line.length() << "," << line[0] << endl;
        lineCounter++;
    }
    cout << "Total Number of Lines: " << lineCounter-1 << endl;
    fin.close();
    return 0;
}