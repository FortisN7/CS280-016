#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    string fileName, line; 
    string longestCommentedLine = "";
    string longestNonCommentedLine = "";
    ifstream fin;
    int linesCounter = 0;
    int commentedLinesCounter = 0;

    cout << "Enter the name of a file to read from:" << endl;
    cin >> fileName;
    cout << endl;
    fin.open(fileName.c_str());
    if(!fin) {
        cerr << "File cannot be opened " << fileName << endl;
        exit(1);
    }

    while(fin.good()) {
        getline(fin, line);
        linesCounter++;
        if(line.substr(0,2) == "##" || line.substr(0,2) == "//") {
            commentedLinesCounter++;
            if(longestCommentedLine.length() < line.length()) {
                longestCommentedLine = line;
            }
        }
        else {
            if(longestNonCommentedLine.length() < line.length()) {
                longestNonCommentedLine = line;
            }
        }
    }

    cout << "Total Number of Lines: " << linesCounter-1 << endl;
    cout << "Number of commented lines: " << commentedLinesCounter << endl;
    cout << "Maximum Length of commented lines: " << longestCommentedLine.length() << endl;
    cout << "Maximum Length of non-commented lines: " << longestNonCommentedLine.length() << endl;
    cout << "Commented line of maximum length: " << "\"" << longestCommentedLine << "\"" << endl;
    cout << "Non-commented line of maximum length: " << "\"" << longestNonCommentedLine << "\"" << endl;
    
    fin.close();
    return 0;
}