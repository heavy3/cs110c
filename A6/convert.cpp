/**
Author: Kevin Morris
File: convert.cpp
License: GPL2
A set of helper functions and structures for converting
mathematical infix expressions to their postfix counterparts
Copyright (C) 2015 Kevin Morris
**/
#include "convert.hpp"
#include <iostream>
using namespace std;

/* Operation hashtable. Map operator => function */
unordered_map<char, void(*)(Stack<char>&, string&, char)> ops {
    {'(', push}, {')', pop}, {'*', push},
    {'/', push}, {'+', push}, {'-', push}
};

/* A set of unary operators to check */
static const set<char> unary {'-', '+'};

/* This function checks to see if a given character at pos i
/  is a unary operator, depending on the character to the left of
/  i being a ')' or not; base case is that i is a unary operator
/  and it's at the start of the string */
template<class Begin, class End, class Iter>
static bool isUnary(Begin s, End e, Iter i)
{
    if(!exists(unary, *i))
        return false;

    return i == s ? true : *--i == '(';
}

/* This function finds the first character in the number set
/  from the position given + 1 and returns the iterator at that
/  position as a position marker */
template<class Iter, class End>
static Iter find(Iter i, End e)
{
    while(++i != e)
    {
        if(exists(num, *i))
            return i;
    }
    return i;
}

/* This function takes an iterator i, starting at character
/  in the number set, and iterates the entire number.
/  It then returns a pair of the string and its position - 1
/  to the caller for iterative convenience. */
template<class Iter, class End>
static pair<string, Iter> getNumber(Iter i, End e)
{
    string n;
    while(i != e && exists(num, *i))
        n.push_back(*i++);
    return {n, i - 1};
}

/* This function constructs a unary fix.
/  i.e. -3 will be turned into (0-3) and returned */
string create(char op, string n)
{
    return "(0" + string(1, op) + n + ")";
}

/* Strips all spaces from a string and returns the new string */
string strip(string orig)
{
    string temp;
    for(auto e : orig)
        if(e != ' ')
            temp.push_back(e);
    return temp;
}

/* This function takes an infix math expression as its argument
/  and uses an algorithm by Pearson, slightly modified by me to
/  convert an infix string containing whole numbers, decimals,
/  and operators into a postfix expression to be evaluated later */
string toPostfix(string ix)
{
    // Note: infix string can take '3 5 + 2' and this will strip it to
    // '35+2' which will be 37. We should pick up this syntax error
    ix = strip(ix); // Strip spaces off the infix string
    string pf; // Postfix string
    Stack<char> st; // Operator stack

    // Loop through the string with iterator i
    for(auto i = ix.begin(); i != ix.end(); ++i)
    {
        if(exists(num, *i)) // If this char is in the number set
        {
            auto n = getNumber(i, ix.end());
            auto id = distance(i, n.second); // Distance between i and n - 1

            i = i + id; // Increase iterator position to account for number
            pf.append(move(n.first)); // Append the parsed string into postfix
            pf.push_back(' '); // Add a space
        }
        else if(exists(ops, *i)) // If this char is in the operator set
        {
            // If it's a unary operator
            if(isUnary(ix.begin(), ix.end(), i))
            {
                // Find the pos of the first number
                auto np = find(i, ix.end());
                // Get it
                auto n = getNumber(np, ix.end());
                auto id = distance(ix.begin(), i); // Store current position

                // Replace portion of the string from operator
                // to end of number
                ix.replace(id, distance(i, n.second + 1),
                           create(*i, n.first));

                // Set i to our old position - 1, so '(' catches on next loop
                i = ix.begin() + id - 1;
            }
            else // If binary
            {
                // Call from operation hashtable for normal operation
                ops[*i](st, pf, *i);
            }
        }
        else // Something went wrong, invalid syntax
        {
            throw domain_error("Invalid syntax");
        }
    } // End of string

    /* Pop the rest of the stack onto the postfix string */
    while(!st.empty())
    {
        pf.push_back(st.pop());
        pf.push_back(' ');
    }

    return pf;
}

/* operator push portion of Pearson's infix => postfix algorithm */
void push(Stack<char>& st, string& pf, char ch)
{
    if(st.empty() || ch == '(') // Base case
    {
        st.push(move(ch));
        return;
    }

    // Lambda used to check priority in the loop
    auto checkPrio = [&]() {
        return prio.at(st.peek()) >= prio.at(ch);
    };

    // Empty out the st up to '(' or a higher priority operator
    while(!st.empty() && checkPrio() && st.peek() != '(')
    {
        pf.push_back(st.pop());
        pf.push_back(' ');
    }
    st.push(ch); // Push the current character on the st
}

/* operator pop portion of Pearson's infix => postfix algorithm */
void pop(Stack<char>& st, string& pf, char ch)
{
    // Might be the bug
    while(!st.empty())
    {
        auto temp = st.pop();
        if(temp == '(')
            break;

        pf.push_back(move(temp));
        pf.push_back(' ');
    }
}



