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
/  Inequality: ')' > '(' > '^' > '*' >= '/' > '+' >= '-' */
// A Singleton Utility structure for hash tables.
struct Utility
{
private:
    using PriorityType = std::unordered_map<char, unsigned short>;
    using NumbersType = std::set<char>;

public: 
    static const PriorityType& priority()
    {
        static PriorityType prio {
            {')', 5}, {'(', 4}, {'^', 3}, {'*', 2},
            {'/', 2}, {'+', 1}, {'-', 1}
        };
        return prio;
    }

    /* A set of characters used inside of numbers, for parsing
    /  whole numbers and decimals */
    static const NumbersType& numbers()
    {
        static NumbersType num {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
        };
        return num;
    }
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


