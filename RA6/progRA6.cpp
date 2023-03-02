#include <iostream>
#include <string>
#include "RA6_Nicholas_Fortis.cpp"

using namespace std;

string DecToBaseN(int num, int base);

int main()
{
	int dec, base ;
	
	cout << "Enter a decimal number:"<< endl;
	cin >> dec;
	
	cout << "Enter the base of conversion:"<< endl;
	cin >> base;
	
	string str = DecToBaseN(dec, base);
	
	cout << "result of converting the decimal number " << dec << " to base " << base << ": " << "\"" 
		<< str << "\"" << endl;
}
