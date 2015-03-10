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

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

unordered_map<char, decltype(&add)> operation {
    {'+', add}, {'-', sub}, {'*', mul}, {'/', divide}
};

void evaluate()
{
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    cout << "Evaluating " << infix << "...\n";
    string postfix = toPostfix(move(infix));

    cout << "Postfix: " << postfix << endl;

    Stack<int> st;

    for(auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if(*i == ' ') continue;

        if(prio.find(*i) == prio.end())
        {
            string num;
            while(i != postfix.end() && numbers.find(*i) != numbers.end())
                num.push_back(*i++);
            st.push(stoi(num));
        }
        else
        {
            auto rhs = st.pop();
            auto lhs = st.empty() ? 0 : st.pop();

            st.push(operation[*i](lhs, rhs));
        }
    }

    cout << st.pop() << endl;

}

int main(int argc, char *argv[])
{
    evaluate();
    /*
    // Push L, A onto the st ack
    stack.push('L');
    stack.push('A');

    // Should print 0, A, 0, L
    cout << stack.empty() << endl;
    cout << stack.pop() << endl;
    cout << stack.empty() << endl;
    cout << stack.pop() << endl;

    // Should print 1, throw error
    cout << stack.empty() << endl;
    cout << stack.pop() << endl;
    
    // Should never happen
    cout << stack.empty() << endl;
    cout << stack.pop() << endl;
    */

    return 0;
}




