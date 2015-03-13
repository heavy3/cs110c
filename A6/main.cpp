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

// 128-bit sized floating point, "It's a triple!"
using triple = long double;

/* Helper functions */
bool isDouble(const string& s)
{
    return s.find(".") != string::npos;
}

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

/* Input and expression evaluation
bool evaluate()
{
    string infix;
    cout << ">> ";
    getline(cin, infix);

    if(cin.eof()) // If CTRL+D was given
    {
        cout << endl;
        return false; // Quit out
    }

    if(!infix.size()) // If the user pressed enter
        return invalid();

    Try to get a postfix conversion, if an exception throws, something
    went wrong in the toPostfix conversion; so it's syntactically errored
    string postfix;
    try {
        postfix = toPostfix(move(infix));
    } catch(domain_error& de) {
        return invalid();
    }

    Stack<triple> st; // Stack to store our values

    for(auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if(*i == ' ') // Skip spaces in postfix
            continue;

        if(!exists(prio, *i)) // If it's not in the priority set
        {
            // Then it's a number, so parse it
            string n;
            while(i != postfix.end() && exists(num, *i))
                n.push_back(*i++);

            triple toPush {0};

            if(n[0] == 'e' && n.size() == 1)
                toPush = e;
            else if(n[0] == 'e')
                toPush = e * stold(n.substr(1));
            else if(n[n.size() - 1] == 'e')
                toPush = e * stold(n.substr(0, n.size() - 1));
            else
                toPush = stold(n);

            st.push(move(toPush)); // Convert it to double and push on stack
        }
        else
        {
            triple rhs, lhs;

            if(st.size() < 2) // If the stack has less than 2 operands
                return invalid(); // Invalid syntax

            // Otherwise, pop the two operands and push the operation
            rhs = st.pop();
            lhs = st.pop();
            st.push(operation[*i](lhs, rhs));
        }
    }

    // We got out of the string, so we're done, print value and end
    auto prec = cout.precision();
    cout.precision(14);
    cout << st.pop() << endl;
    cout.precision(prec);
    return true;
}
*/

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
    /*
    Expression e("3+2+-");
    cout << e << endl;

    return 0;
    */
    program();

    if(argc > 1)
    {
        string a { move(argv[1]) };
        return a == "-h" || a == "--help" ? help(argv[0]) : usage(argv[0]);
    }

    welcome();
    /* While evaluate returns true, we try again */
    //while(evaluate());
    
    auto prec = cout.precision();
    cout.precision(14);
    Expression<long double> expr;
    while(true)
    {
        string infix;
        cout << ">> ";
        getline(cin, infix);
        if(cin.eof())
        {
            cout << "Bye\n";
            break;
        }

        if(!expr.consume(move(infix)))
        {
            invalid();
            continue;
        }

        try {
            cout << expr.evaluate() << endl;
        } catch(domain_error&) {
            invalid();
        }
    }
    cout.precision(prec);

    return 0;
}




