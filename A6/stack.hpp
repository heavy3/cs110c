/**
Author: Kevin Morris
File: stack.hpp
License: GPL2
A stack data structure implementation, compiled using C++11 standardees.
Copyright (C) 2015 Kevin Morris
**/
#ifndef STACK_HPP
#define STACK_HPP

#include <utility> // For std::move/std::forward utilities
#include <memory> // For smart pointers

namespace std
{
    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>(new T(forward<Args>(args)...));
    }
};

#include <iostream>

template<typename T>
class Stack
{
private:

    struct Node
    {
        T value;
        std::unique_ptr<Node> next {nullptr};

        Node(T v) : value(std::move(v)) {}
        Node(T v, std::unique_ptr<Node> child)
            : value(std::move(v))
            , next(std::move(child)) // Move unique ptr
        { /* Initialization constructor */ }
    };

    std::unique_ptr<Node> head {nullptr};

public:

    void push(T value)
    {
        head = std::make_unique<Node>(std::move(value), std::move(head));
    }

    // Move a value from the head of the stack and delete that node
    T pop()
    {
        if(empty())
            throw std::domain_error("Stack<T> empty when attempting to pop");

        T value { std::move(head->value) };
        head = std::move(head->next);

        return value;
    }

    const T& peek() const
    {
        if(empty())
            throw std::domain_error("Stack<T> empty when peeking");

        return head->value;
    }

    const bool empty() const
    {
        return !head;
    }

    void traverse()
    {
        auto *p = head.get();
        std::cout << "Stack: ";
        while(p)
        {
            std::cout << p->value << ' ';
            p = p->next.get();
        }
        std::cout << std::endl;
    }

};

#endif /* STACK_HPP */

