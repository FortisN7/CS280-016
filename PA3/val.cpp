/*You are required to provide the implementation of the Value class in a separate file, called “val.cpp”, which includes the implementations of the all the member functions and
overloaded operator functions specified in the Value class definition.*/

#include <string>
#include <iostream>
#include "val.h"

using namespace std;

//might have to move where we declare oper1 and oper2 as doubles if that interferes with setting as int

// numeric overloaded add op to this
Value Value::operator+(const Value& op) const {
    double oper1;
    double oper2;
    double ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 + oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 + oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}
    
// numeric overloaded subtract op from this
Value Value::operator-(const Value& op) const {
    double oper1;
    double oper2;
    double ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 - oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 - oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 - oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 - oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 - oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 - oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 - oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}


// numeric overloaded multiply this by op
Value Value::operator*(const Value& op) const {
    double oper1;
    double oper2;
    double ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 * oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 * oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 * oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 * oper2;
        return Value(ans);
    }
    //First operand is int and second operand is a real
    else if (IsInt() && op.IsReal()) {
        oper1 = GetInt();
        oper2 = op.GetReal();
        //operation
        ans = oper1 * oper2;
        return Value(ans);
    }
    //First operand is int and second operand is a real
    else if (IsReal() && op.IsInt()) {
        oper1 = GetReal();
        oper2 = op.GetInt();
        //operation
        ans = oper1 * oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 * oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 * oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 * oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

 // numeric overloaded divide this by op
Value Value::operator/(const Value& op) const {
    double oper1;
    double oper2;
    double ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        if (oper2 == 0) {
            cout << "Run-Time Error-Illegal Division by Zero" << endl;
            return Value();
        }
        ans = oper1 / oper2; 
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}


//numeric overloaded equality operator of this with op
Value Value::operator==(const Value& op) const {
    double oper1;
    double oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 == oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 == oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

//numeric overloaded greater than operator of this with op
Value Value::operator>(const Value& op) const {
    double oper1;
    double oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 > oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 > oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

//numeric overloaded less than operator of this with op
Value Value::operator<(const Value& op) const {
    double oper1;
    double oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {
            oper1 = stod(GetString());
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && op.IsString()) {
        try {
            oper1 = GetInt();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && op.IsInt()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetInt();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && op.IsInt()) {
        oper1 = GetInt();
        oper2 = op.GetInt();
        //operation
        ans = oper1 < oper2;
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && op.IsString()) {
        try {
            oper1 = GetReal();
            oper2 = stod(op.GetString());
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && op.IsReal()) {
        try {
            oper1 = stod(GetString());
            oper2 = op.GetReal();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && op.IsReal()) {
        oper1 = GetReal();
        oper2 = op.GetReal();
        //operation
        ans = oper1 < oper2;
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

//Numeric exponentiation operation this raised to the power of op 
Value Value::operator^(const Value& oper) const {
    try {
        double oper1 = GetReal();
        double oper2 = oper.GetReal();
        //operation
        double ans = pow(oper1, oper2);
        return Value(ans);
    }
    catch (...) {
        return Value();
    }
}

//string concatenation operation of this with op
Value Value::Catenate(const Value& oper) const {
    //never added ints to, didn't make sense to
    
    string oper1;
    string oper2;
    string ans;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
        //operation
        ans = oper1 + oper2;
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && oper.IsInt()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && oper.IsInt()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && oper.IsReal()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && oper.IsReal()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 + oper2; 
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

//string repetition operation of this with op
Value Value::Repeat(const Value& oper) const {
    //this might not work lmao

    if (IsString() && oper.IsReal()) {
        try {
            string oper1 = GetString();
            double oper2 = oper.GetReal();
            //operation
            
            string ans;
            for (int i = 0; i < oper2-1; i++) {
                ans += oper1;
            }
            return Value(ans);
        }
        catch (...) {
            cout << "Invalid syntax for Repeat" << endl;
            return Value();
        }
    }
    //might need to add oper.IsInt()
    else {
        cout << "Invalid syntax for Repeat" << endl;
        return Value();
    }

}

//string equality (-eq) operator of this with op
Value Value::SEqual(const Value& oper) const {
    string oper1;
    string oper2;
    bool ans;
    //cout << this->GetType() << " " << oper.GetType() << endl;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
        //operation
        ans = oper1 == oper2;
        return Value(ans);
    }
    //First operand is int and second operand is a string
    else if (IsInt() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is int
    else if (IsString() && oper.IsInt()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsInt() && oper.IsInt()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && oper.IsReal()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && oper.IsReal()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 == oper2; 
        return Value(ans);
    }
    //ERR
    else {
        
        return Value();
    }
}

//string greater than (-gt) operator of this with op
Value Value::SGthan(const Value& oper) const {
    string oper1;
    string oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
        //operation
        ans = oper1 > oper2;
        return Value(ans);
    }
    //First operand is Int and second operand is a string
    else if (IsInt() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is Int
    else if (IsString() && oper.IsInt()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is Int and second operand is Int
    else if (IsInt() && oper.IsInt()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && oper.IsReal()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && oper.IsReal()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 > oper2; 
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}

//string less than operator of this with op
Value Value::SLthan(const Value& oper) const {
    string oper1;
    string oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
        //operation
        ans = oper1 < oper2;
        return Value(ans);
    }
    //First operand is Int and second operand is a string
    else if (IsInt() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is Int
    else if (IsString() && oper.IsInt()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is Int and second operand is Int
    else if (IsInt() && oper.IsInt()) {
        try {
            ostringstream outStr1;
            outStr1 << GetInt();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetInt();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from Int to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is a string
    else if (IsReal() && oper.IsString()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            oper2 = oper.GetString();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is a string and second operand is real
    else if (IsString() && oper.IsReal()) {
        try {
            oper1 = GetString();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //First operand is real and second operand is real
    else if (IsReal() && oper.IsReal()) {
        try {
            ostringstream outStr1;
            outStr1 << GetReal();
            oper1 = outStr1.str();
            ostringstream outStr2;
            outStr2 << oper.GetReal();
            oper2 = outStr2.str();
        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from double to string." << endl;
            return Value();
        }
        //operation
        ans = oper1 < oper2; 
        return Value(ans);
    }
    //ERR
    else {
        return Value();
    }
}