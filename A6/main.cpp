/**
Author: Kevin Morris
File: main.cpp
License: GPL2
Main file for a simple algebra calculator implemented in C++11
for Assignment 6: Calculator in CS110C at CCSF
Copyright (C) 2015 Kevin Morris
**/
#include "stack.hpp"
#include "convert.hpp"
#include "expression.hpp"
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>
#include <iostream>
using namespace std;

const char* const programName { "kcalc" };
const char* const programVer  { "1.0.0b" };

bool hasConstant(const string& s, const string& c)
{
    return s.find(c) != string::npos;
}

vector<string> searchConstant(const string& s)
{
    vector<string> found, cs { "e", "pi", "phi" };
    for(auto& c : cs)
    {
        if(hasConstant(s, c))
            found.emplace_back(c);
    }
    return found;
}

bool invalid()
{
    cerr << "!> invalid syntax\n";
    return true;
}

/* Standard library C++11 to_string functions forces a loss
/  of precision when converting double/triple to string */
template<typename T>
string to_string_prec(const T& value, const int n = 14)
{
    ostringstream out;
    out.precision(n);
    out << value;
    return out.str();
}

void program()
{
    cout << programName << ' ' << programVer << " (written by kevr)\n"
         << "compiled on " << __DATE__ << " at "  __TIME__ << "\n";
}

void welcome()
{
    /* Intro */
    cout << "Enter infix expressions below to be evaluated\n"
         << "Press CTRL+D on a new line to quit\n";
}

bool usage(const char* const name)
{
    cout << "usage: " << name << " [-h|--help]\n";
    return true;
}

bool help(const char* const name)
{
    usage(name);
    cout << "Options\n"
         << "\t-h, --help | Print out help prompt\n";
    
    cout << "\nOperators (in order of prescendence)\n"
         << "\tParenthesis    | (1 + 2)\n"
         << "\tPower          | 2^2\n"
         << "\tMultiplication | 1 * 2\n"
         << "\tDivision       | 1 / 2\n"
         << "\tAddition       | 1 + 2\n"
         << "\tSubtraction    | 1 - 2\n";

    cout << "\nUnary Operators\n"
         << "\tNegative       | -1\n"
         << "\tPositive       | +1\n";

    cout << "\nSpecial Constants\n"
         << "\te              | Euler's Constant\n";

    cout << "\nExample Expressions\n"
         << "\t-e + (5.3 - 2) / 0.3 + 163\n"
         << "\t5^2 + 4.2^3\n"
         << "\t16/(-3) + 64.3 * (22 - 1)\n";

    cout << "\nAuthors\n"
         << "\tKevin Morris   | kevr@nixcode.us\n";

    cout << endl;
    return false;
}

int main(int argc, char *argv[])
{
    program();

    if(argc > 1)
    {
        string a { move(argv[1]) };
        return a == "-h" || a == "--help" ? help(argv[0]) : usage(argv[0]);
    }

    welcome();
    
    // Set precision
    auto prec = cout.precision();
    cout.precision(14);

    // Create expression object
    Expression<long double> expr;

    while(!cin.eof())
    {
        string ix;
        cout << ">> ";
        getline(cin, ix);

        if(cin.eof())
            cout << "Bye\n";
        else if(!ix.size() || !expr.consume(move(ix)) || !expr.evaluate())
            invalid();
        else
            cout << expr.result() << endl;
    }

    cout.precision(prec);

    return 0;
}




