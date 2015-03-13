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
#include <cmath>
#include <set>
#include <unordered_map>
#include <sstream>
#include <iostream>
using namespace std;

const char* const programName { "kcalc" };
const char* const programVer  { "1.0.0b" };

// Constants
const long double e   = 2.718281828459;
const long double pi  = 3.14159265359;
const long double phi = 1.6180339887;

/* A series of templated math operation functions, for binding to
operation tables; we'll instantiate these as doubles */
template<typename T>
T add(T a, T b) { return a + b; }

template<typename T>
T sub(T a, T b) { return a - b; }

template<typename T>
T mul(T a, T b) { return a * b; }

template<typename T>
T divide(T a, T b) { return a / b; }

template<typename T>
T power(T a, T b) { return pow(a, b); }

/* Our operation binds */
unordered_map<char, decltype(&add<long double>)> operation {
    {'+', add}, {'-', sub}, {'*', mul}, {'/', divide}, {'^', power}
};

/* Helper functions */
bool isDouble(const string& s)
{
    return s.find(".") != string::npos;
}

bool invalid()
{
    cerr << "!> invalid syntax\n";
    return true;
}

/* Standard library C++11 to_string functions forces a loss
/  of precision when converting double/long double to string */
template<typename T>
string to_string_prec(const T& value, const int n = 14)
{
    ostringstream out;
    out.precision(n);
    out << value;
    return out.str();
}

/* Input and expression evaluation */
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

    /* Try to get a postfix conversion, if an exception throws, something
    went wrong in the toPostfix conversion; so it's syntactically errored */
    string postfix;
    try {
        postfix = toPostfix(move(infix));
    } catch(domain_error& de) {
        return invalid();
    }

    Stack<long double> st; // Stack to store our values

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

            long double toPush {0};

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
            long double rhs, lhs;

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

void program()
{
    cout << programName << ' ' << programVer << " (written by kevr)\n";
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
    /* While evaluate returns true, we try again */
    while(evaluate());
    return 0;
}




