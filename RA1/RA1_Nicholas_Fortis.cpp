/*Name: Nicholas Fortis
Assignment: RA1 - Welcome Message
Description: We take input from the user and output a hello message
Section: CS280-016*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;
    cout << "Welcome to CS 280 in Spring 2023 Semester" << endl;
    cout << "Please enter your first name" << endl;
    cin >> firstName;
    cout << "Please enter your last name" << endl;
    cin >> lastName;
    cout << "Welcome " + firstName + " " + lastName + " to CS 280";
    return 0;
}