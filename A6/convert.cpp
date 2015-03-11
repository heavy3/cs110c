/**
Author: Kevin Morris
File: convert.cpp
License: GPL2
A set of helper functions and structures for converting things.
Copyright (C) 2015 Kevin Morris
**/
#include "convert.hpp"
#include <iostream>
using namespace std;


// Operations
unordered_map<char, void(*)(Stack<char>&, string&, char)> ops {
    {'(', push}, {')', pop}, {'*', push},
    {'/', push}, {'+', push}, {'-', push}
};

static std::set<char> num {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
}, unary {'-', '+'};

template<class C, class T>
bool exists(const C& c, const T& t)
{
    return c.find(t) != c.end();
}

template<class Begin, class End, class Iter>
bool isUnary(Begin s, End e, Iter i)
{
    if(!exists(unary, *i))
        return false;

    return i == s ? true : *--i == '(';
}

template<class Iter, class End>
Iter find(Iter i, End e)
{
    while(++i != e)
    {
        if(exists(num, *i))
            break;
    }
    return i;
}

template<class Iter, class End>
pair<string, Iter> getNumber(Iter i, End e)
{
    string n;
    while(i != e && exists(num, *i))
        n.push_back(*i++);
    return {move(n), i - 1};
}

string create(char op, string n)
{
    return "(0" + string(1, op) + n + ")";
}

string strip(string orig)
{
    string temp;
    for(auto e : orig)
        if(e != ' ')
            temp.push_back(e);
    return temp;
}

string toPostfix(string ix)
{
    ix = strip(ix);
    string pf; // Postfix string
    Stack<char> st; // Operator stack

    cout << "Evaluating: " << ix << "...\n";
    for(auto i = ix.begin(); i != ix.end(); ++i)
    {
        if(exists(num, *i))
        {
            auto n = getNumber(i, ix.end());
            auto id = distance(i, n.second);

            pf.append(move(n.first));
            pf.push_back(' ');
            i = i + id;
        }
        else if(exists(ops, *i))
        {
            if(isUnary(ix.begin(), ix.end(), i))
            {
                auto np = find(i, ix.end());
                auto n = getNumber(np, ix.end());
                auto id = distance(ix.begin(), i);

                ix.replace(id, distance(i, np) + 1, create(*i, n.first));
                i = ix.begin() + id;

                cout << ix << endl;

            }
            else
            {
                ops[*i](st, pf, *i);
            }
        }
        else
        {
            throw domain_error("Invalid syntax");
        }
    }

    while(!st.empty())
    {
        pf.push_back(st.pop());
        pf.push_back(' ');
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



