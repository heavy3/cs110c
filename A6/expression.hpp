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

/* A series of templated math operation functions, for binding to
operation tables; we'll instantiate these as doubles */
template<typename T>
T add(T a, T b) { return a + b; }

template<typename T>
T sub(T a, T b) { return a - b; }

template<typename T>
T mul(T a, T b) { return a * b; }

template<typename T>
T divide(T a, T b) { return a / b; }

template<typename T>
T power(T a, T b) { return pow(a, b); }

/* Templated singleton instance for the Operation Table, to be used
within the BaseExpression class to reuse a binding of one types operations */
template<typename T>
std::unordered_map<char, decltype(&add<T>)>& getOperations()
{
    static std::unordered_map<char, decltype(&add<T>)> ops {
        {'+', add}, {'-', sub}, {'*', mul}, {'/', divide}, {'^', power}
    };
    return ops;
}

/* Default T to MAX_TYPE/long double */
template<typename T = MAX_TYPE>
class BaseExpression
{
private:
    std::unordered_map<char, decltype(&add<T>)>& operation {
        getOperations<T>()
    };

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

    template<typename Functor>
    const T& evaluate(Functor f)
    {
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

                // Convert it to double and push on stack
                st.push(f(n));
            }
            else
            {
                T rhs, lhs;

                if(st.size() < 2) // If the stack has less than 2 operands
                {
                    throw std::domain_error("Invalid number of operands");
                }

                // Otherwise, pop the two operands and push the operation
                rhs = st.pop();
                lhs = st.pop();
                st.push(BaseExpression::operation[*i](lhs, rhs));
            }
        }
        value = st.pop();
        return value;
    }

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

    const T& evaluate()
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

    const double& evaluate()
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
    
    const unsigned long& evaluate()
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
    
    const long& evaluate()
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
    
    const long long& evaluate()
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

    const int& evaluate()
    {
        return BaseExpression::evaluate([](const std::string& a) {
            return std::stoi(a);
        });
    }
};

#endif /* EXPRESSION_HPP */



