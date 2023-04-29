#include <string>
#include <iostream>
#include "val.h"

using namespace std;

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
        ans = oper1 * oper2;
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
        ans = oper1 == oper2;
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
        double ans = pow(oper1, oper2);
        return Value(ans);
    }
    catch (...) {
        return Value();
    }
}

//string concatenation operation of this with op
Value Value::Catenate(const Value& oper) const {
    string oper1;
    string oper2;
    string ans;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
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

//string less than operator of this with op
Value Value::SLthan(const Value& oper) const {
    string oper1;
    string oper2;
    bool ans;
    //First operand is a string and second operand is a string
    if (IsString() && oper.IsString()) {
        oper1 = GetString();
        oper2 = oper.GetString();
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