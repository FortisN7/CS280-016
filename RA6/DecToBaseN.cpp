#include <string>
#include <iostream>

using namespace std;

string DecToBaseN(int num, int base) {
    if ((base >= 2) && (base <= 10)) {
        // base 2-10
        int remainder = num % base;
        if (num/base == 0) {
            return to_string(remainder);
        }
        else {
            return DecToBaseN(num/base, base) + to_string(remainder); 
        }
    }
    else if (base == 16) {
        // base 16
        int remainder = num % base;
        if (num/base == 0) {
            return to_string(remainder);
        }
        else {
            switch (remainder) {
                case 15:
                    return DecToBaseN(num/base, base) + "F";
                    break;
                case 14:
                    return DecToBaseN(num/base, base) + "E";
                    break;
                case 13:
                    return DecToBaseN(num/base, base) + "D";
                    break;
                case 12:
                    return DecToBaseN(num/base, base) + "C";
                    break;
                case 11:
                    return DecToBaseN(num/base, base) + "B";
                    break;
                case 10:
                    return DecToBaseN(num/base, base) + "A";
                    break;
                default:
                    return DecToBaseN(num/base, base) + to_string(remainder);
                    break;
            } 
        }
    }
    else {
        // invalid base
        cout << "Invalid Base: " << base << endl;
        return "";
    }
}