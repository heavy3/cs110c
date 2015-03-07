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
#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const Stack<T>& stack)
{
    /* Iterate through stack and print out values */
    return os;
}

// Priorities
const unordered_map<char, int> prio = {
    {'(', 6}, {')', 5}, {'*', 4}, {'/', 3}, {'+', 2}, {'-', 1}
};

void push(Stack<char>& stack, string& pf, char ch)
{
    if(stack.empty())
    {
        stack.push(ch);
        return;
    }

    while(!stack.empty() && prio.at(ch) >= prio.at(stack.peek()))
        pf.push_back(stack.pop());
    stack.push(ch);
}

void pop(Stack<char>& stack, string& pf, char ch)
{
    while(!stack.empty() && stack.peek() != '(')
        pf.push_back(stack.pop());
}

// Operations
unordered_map<char, void(*)(Stack<char>&, string&, char)> ops {
    {'(', push}, {')', pop}
};

// Valid decimal number characters
set<char> numbers { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

string toPostfix(string infix)
{
    Stack<char> stack;
    string postfix;

    for(auto it = infix.begin(); it != infix.end(); ++it)
    {
        if(*it == ' ' || *it == '\t')
            continue;

        if(ops.find(*it) == ops.end())
        {
            string number;
            while(numbers.find(*it) != numbers.end())
                number.push_back(*it++);
            postfix += number;
        }
        else
        {
            ops[*it](stack, postfix, *it);
        }

        postfix.push_back(' ');
    }

    while(!stack.empty())
        postfix.push_back(stack.pop());

    return postfix;
}

int main(int argc, char *argv[])
{
    Stack<string> stack;

    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    auto postfix = toPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    return 0;
}

