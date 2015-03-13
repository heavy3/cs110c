/**
Author: Kevin Morris
File: convert.hpp
License: GPL2
A set of helper functions and structures for converting
mathematical infix expressions to their postfix counterparts
Copyright (C) 2015 Kevin Morris
**/
#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "stack.hpp"
#include <string>
#include <set>
#include <unordered_map>

/* Operator priority table.
/  Inequality: ')' > '(' > '*' >= '/' > '+' >= '-' */
const std::unordered_map<char, unsigned short> prio {
    {')', 5}, {'(', 4}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1},
    {'^', 3},
};

/* A set of characters used inside of numbers, for parsing
/  whole numbers and decimals */
const std::set<char> num {
    'e', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
};

/* This function checks to see if t exists in container c
/  T must be the type used in C<T> for this function to instantiate */
template<class C, class T>
bool exists(const C& c, const T& t)
{
    return c.find(t) != c.end();
}

/* Prototypes for postfix conversion helpers and function */
std::string create(char op, std::string n);
std::string strip(std::string orig);
std::string toPostfix(std::string infix);

void push(Stack<char>& st, std::string& pf, char ch);
void  pop(Stack<char>& st, std::string& pf, char ch);

#endif /* CONVERT_HPP */

