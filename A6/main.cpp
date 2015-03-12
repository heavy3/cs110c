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

void evaluate()
{
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    cout << "Evaluating " << infix << "...\n";
    string postfix;
    try {
        postfix = toPostfix(infix);
    } catch(domain_error& de)
    {
        cout << "Invalid syntax; You must use valid algebra\n";
        return;
    }

    cout << "PF: " << postfix << endl;

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

            try {
                rhs = st.pop();
                lhs = st.pop();
            } catch(...)
            {
                cout << "Invalid syntax; You must use valid algebra\n";
                return;
            }

            st.push(operation[*i](lhs, rhs));
        }
    }

    cout << infix << " = " << st.pop() << endl;

}

int main(int argc, char *argv[])
{
    evaluate();
    return 0;
}




