/**
Author: Kevin Morris
File: convert.cpp
License: GPL2
A set of helper functions and structures for converting things.
Copyright (C) 2015 Kevin Morris
**/
#include "convert.hpp"
#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;


// Operations
unordered_map<char, void(*)(Stack<char>&, string&, char)> ops {
    {'(', push}, {')', pop}, {'*', push},
    {'/', push}, {'+', push}, {'-', push}
};

template<typename Begin, typename End>
string getOperand(Begin& b, End e)
{
    string temp;
    while(b != e)
    {
        if(numbers.find(*b) == numbers.end())
            break;
        temp.push_back(*b++);
    }

    return temp;
}

string toPostfix(string infix)
{
    Stack<char> st; // Operation stack
    string pf; // postfix
#ifdef TEST_OPLAST
    bool opLast = false;
#endif

    // Iterate through infix string
    for(auto i = infix.begin(); i != infix.end(); ++i)
    {
        // If character is a space... continue loop
        if(*i == ' ') continue;

        if(ops.find(*i) == ops.end())
        {
#ifdef TEST_OPLAST
            if(pf.size() && !opLast)
                throw std::domain_error("Invalid syntax");
#endif

            pf.append(getOperand(i, infix.end()));
            --i;
            pf.push_back(' ');
#ifdef TEST_OPLAST
            opLast = false;
#endif
        }
        else
        {
#ifdef TEST_OPLAST
            if(opLast)
                throw std::domain_error("Invalid syntax");
#endif

            ops[*i](st, pf, *i);
#ifdef TEST_OPLAST
            opLast = true;
#endif
        }

    }

    if(!st.empty())
    {
        pop(st, pf, '0');
    }

    return pf;
}

void push(Stack<char>& stack, string& pf, char ch)
{
    if(stack.empty())
    {
        stack.push(ch);
        return;
    }

    // Empty out the stack up to '(' or a higher priority operator
    while(!stack.empty() && prio.at(stack.peek()) >= prio.at(ch))
    {
        auto temp = stack.pop();
        if(temp == '(')
            break;

        pf.push_back(std::move(temp));
        pf.push_back(' ');
    }

    stack.push(ch); // Push the current character on the stack
}

void pop(Stack<char>& stack, string& pf, char ch)
{
    while(!stack.empty() && stack.peek() != '(')
    {
        pf.push_back(stack.pop());
        pf.push_back(' ');
    }
}



