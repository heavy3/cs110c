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

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }

unordered_map<char, decltype(&add)> operation {
    {'+', add}, {'-', sub}, {'*', mul}, {'/', divide}
};

static std::set<char> numbers {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
};

bool isDouble(const string& s)
{
    return s.find(".") != string::npos;
}

bool evaluate()
{
    string infix;
    getline(cin, infix);

    if(cin.eof()) // if CTRL+D was given
        return false; // Quit out

    string postfix;
    try {
        postfix = toPostfix(move(infix));
    } catch(domain_error& de) {
        cerr << ">> invalid syntax\n";
        return true;
    }

    Stack<double> st;

    for(auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if(*i == ' ') continue;

        if(prio.find(*i) == prio.end())
        {
            string num;
            while(i != postfix.end() && numbers.find(*i) != numbers.end())
                num.push_back(*i++);
            st.push(stod(num));
        }
        else
        {
            // At this point, we assume that we're given a proper
            // postfix string, since the conversion does the checks
            double rhs, lhs;

            if(st.size() < 2)
            {
                cerr << ">> invalid syntax\n";
                return true;
            }

            rhs = st.pop();
            lhs = st.pop();
            st.push(operation[*i](lhs, rhs));
        }
    }

    cout << ">> " << st.pop() << endl;
    return true;
}

int main(int argc, char *argv[])
{
    cout << "KCalculator 1.0b (written by kevr)\n";
    cout << "Enter infix expressions below to be evaluated\n"
         << "Press CTRL+D on a new line to quit\n";
    while(evaluate());
    return 0;
}




