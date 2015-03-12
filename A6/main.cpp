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
#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;

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

/* Our operation binds */
unordered_map<char, decltype(&add<double>)> operation {
    {'+', add}, {'-', sub}, {'*', mul}, {'/', divide}
};

/* Helper functions */
bool isDouble(const string& s)
{
    return s.find(".") != string::npos;
}

bool invalid()
{
    cerr << ">> invalid syntax\n";
    return true;
}

/* Input and expression evaluation */
bool evaluate()
{
    string infix;
    getline(cin, infix);

    if(cin.eof()) // If CTRL+D was given
        return false; // Quit out

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

    Stack<double> st; // Stack to store our values

    for(auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if(*i == ' ') continue;

        if(!exists(prio, *i)) // If it's not in the priority set
        {
            // Then it's a number, so parse it
            string n;
            while(i != postfix.end() && exists(num, *i))
                n.push_back(*i++);
            st.push(stod(n)); // Convert it to double and push on stack
        }
        else
        {
            double rhs, lhs;

            if(st.size() < 2) // If the stack has less than 2 operands
                return invalid(); // Invalid syntax

            // Otherwise, pop the two operands and push the operation
            rhs = st.pop();
            lhs = st.pop();
            st.push(operation[*i](lhs, rhs));
        }
    }

    // We got out of the string, so we're done, print value and end
    cout << ">> " << st.pop() << endl;
    return true;
}

int main(int argc, char *argv[])
{
    /* Intro */
    cout << "KCalculator 1.0b (written by kevr)\n";
    cout << "Enter infix expressions below to be evaluated\n"
         << "Press CTRL+D on a new line to quit\n";

    /* While evaluate returns true, we try again */
    while(evaluate());
    return 0;
}




