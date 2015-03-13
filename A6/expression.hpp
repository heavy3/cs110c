/**
Author: Kevin Morris
File: expression.hpp
License: GPL2
An object representing a mathematical expression.
Copyright (C) 2015 Kevin Morris
**/
#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "convert.hpp"
#include <cmath>
#include <utility>
#include <string>
#include <unordered_map>

// Default T we'll use for Expressions
using MAX_TYPE = long double;

const MAX_TYPE e   = 2.718281828459;
const MAX_TYPE pi  = 3.14159265359;
const MAX_TYPE phi = 1.6180339887;

const std::unordered_map<std::string, MAX_TYPE> constant {
    {"e", e}, {"pi", pi}, {"phi", phi}
};

/* An abstracted hashtable from character to operation functions;
This table supports ops['+'], '-', '*', '/', and '^' */
template<typename T>
class Operations
{
private:
    /* Our operation functions */
    static T add(T a, T b) { return a + b; }
    static T sub(T a, T b) { return a - b; }
    static T mul(T a, T b) { return a * b; }
    static T div(T a, T b) { return a / b; }
    static T pow(T a, T b) { return ::pow(a, b); }

    /* Redefinitions of some types we're using in this class */
    using FunctionType = decltype(&add);
    using TableType = std::unordered_map<char, FunctionType>;

    /* Singleton function to keep references of a single operation
     * object for each type instantiated with this class */
    static TableType& getTable()
    {
        static TableType table {
            {'+', add}, {'-', sub}, {'*', mul}, {'/', div}, {'^', pow}
        };
        return table;
    }

    /* Internal operation table */
    TableType& ops { getTable() };

public:
    // Our function getter
    FunctionType operator[](const char key)
    {
        return ops[key];
    }
};

/* Default T to MAX_TYPE/long double */
template<typename T = MAX_TYPE>
class BaseExpression
{
private:
    Operations<T> ops;

private:
    std::string postfix; // Conversion string
    T value;
    Stack<T> st;

public:
    BaseExpression() = default; 

    BaseExpression(std::string&& ix)
    {
        if(!consume(ix))
        {
            throw std::domain_error("Expression(" + ix + ") was invalid");
        }
    }

    bool consume(std::string ix)
    {
        try {
            postfix = toPostfix(std::move(ix));
        } catch(std::domain_error&) {
            return false;
        }
        return true;
    }

    // The Functor given to this function is responsible for converting
    // a string to a number. i.e. num = convert(string)
    template<typename Functor>
    const bool evaluate(Functor f)
    {
        st.clear(); // Clear the stack of possible old errors
        for(auto i = postfix.begin(); i != postfix.end(); ++i)
        {
            if(*i == ' ') // Skip spaces in postfix
                continue;

            if(!exists(prio, *i)) // If it's not in the priority set
            {
                // Then it's a number, so parse it
                std::string n;
                while(i != postfix.end() && exists(num, *i))
                    n.push_back(*i++);

                st.push(f(n)); // Call conversion functor
            }
            else
            {
                T rhs, lhs;

                if(st.size() < 2) // If the stack has less than 2 operands
                    return false;

                // Otherwise, pop the two operands and push the operation
                rhs = st.pop();
                lhs = st.pop();
                // Call operation from our operation table
                st.push(BaseExpression::ops[*i](lhs, rhs));
            }
        }
        value = st.pop(); // Store evaluation result

        return true;
    }

    const T& result() const
    {
        return value;
    }

    /* Helper function for cout, prints postfix expression */
    friend std::ostream& operator<<(std::ostream& os, const BaseExpression& e)
    {
        os << e.postfix;
        return os;
    }
};

/* Default expression of any type; if not specialized, uses
'string' to 'long double' conversion function in the STL */
template<typename T>
class Expression : public BaseExpression<T>
{
public:
    using BaseExpression<T>::BaseExpression;

    const bool evaluate()
    {
        return BaseExpression<T>::evaluate([](const std::string& a) {
            return std::stold(a); // Long double, default (biggest size+prec)
        });
    }
};

/* A set of template specializations to utilize specific functions
for different numerical types in C++; an increase to performance and utility */
template<>
class Expression<double> : public BaseExpression<double>
{
public:
    using BaseExpression::BaseExpression;

    const bool evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stod(a);
        });
    }
};

template<>
class Expression<unsigned long> : public BaseExpression<unsigned long>
{
public:
    using BaseExpression::BaseExpression;
    
    const bool evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stoul(a);
        });
    }

};

template<>
class Expression<long> : public BaseExpression<long>
{
public:
    using BaseExpression::BaseExpression;
    
    const bool evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stol(a);
        });
    }

};

template<>
class Expression<long long> : public BaseExpression<long long>
{
public:
    using BaseExpression::BaseExpression;
    
    const bool evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stoll(a);
        });
    }
};

template<>
class Expression<int> : public BaseExpression<int>
{
public:
    using BaseExpression::BaseExpression;

    const bool evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stoi(a);
        });
    }
};

#endif /* EXPRESSION_HPP */



