#include <string>
#include <iostream>
#include "val.h"

using namespace std;

// numeric overloaded multiply this by op
Value Value::operator*(const Value& op) const {
    double oper;
    //First operand is a string and second operand is a string
    if (IsString() && op.IsString()) {
        try {

        }
        catch (invalid_argument & arg) {
            cout << "Invalid conversion from string to double." << endl;
            return Value();
        }
        int times = oper;
        string str = GetString(), newstr = "";
        //operation
        return Value();
    }
    //First operand is real and second operand is a string
    else if () {

    }
    //First operand is a string and second operand is real
    else if () {

    }
    //First operand is real and second operand is real
    else {

    }
}

//numeric overloaded equality operator of this with op
Value Value::operator==(const Value& op) const {
    try {

    }
    catch () {
        
    }
}

//Numeric exponentiation operation this raised to the power of op 
Value Value::operator^(const Value& oper) const {
    try {

    }
    catch () {
        
    }
}

//string concatenation operation of this with op
Value Value::Catenate(const Value& oper) const {
    try {

    }
    catch () {
        
    }
}

//string less than operator of this with op
Value Value::SLthan(const Value& oper) const {
    try {

    }
    catch () {
        
    }
}