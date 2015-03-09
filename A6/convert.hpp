/**
Author: Kevin Morris
File: convert.hpp
License: GPL2
A set of helper functions and structures for converting things.
Copyright (C) 2015 Kevin Morris
**/
#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "stack.hpp"
#include <string>
#include <set>
#include <unordered_map>

// Priorities
const std::unordered_map<char, int> prio {
    {')', 4}, {'(', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}
};

const std::set<char> numbers {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'
};

std::string toPostfix(std::string infix);

void push(Stack<char>& stack, std::string& pf, char ch);
void pop(Stack<char>& stack, std::string& pf, char ch);

#endif /* CONVERT_HPP */

