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

template<typename T>
class Stack
{
private:

    struct Node
    {
        T value;
        std::unique_ptr<Node> next {nullptr};

        Node(const T& newValue) : value(newValue) {}
        Node(T&& newValue) : value(std::move(newValue)) {}

        Node(const T& newValue, std::unique_ptr<Node>&& child)
            : value(newValue)
            , next(std::move(child)) // Move unique ptr
        {
        }

        Node(T&& newValue, std::unique_ptr<Node>&& child)
            : value(std::move(newValue))
            , next(std::move(child)) // Move unique ptr
        {
        }
    };

    std::unique_ptr<Node> head {nullptr};

public:

    void push(const T& value)
    {
        if(!head)
            head = std::make_unique<Node>(value);

        auto newNode = std::make_unique<Node>(value, std::move(head));
        head = std::move(newNode);
    }

    void push(T&& value)
    {
        if(!head)
            head = std::make_unique<Node>(std::move(value));

        auto newNode = std::make_unique<Node>(std::forward<T>(value),
                                              std::move(head));
        head = std::move(newNode);
    }

    T pop()
    {
        if(!head)
            throw std::domain_error("Stack<T> empty when attempting to pop");

        T value { std::move(head->value) };
        
        auto old = std::move(head);
        head = std::move(old->next);

        return value;
    }

    const T& peek() const
    {
        if(!head)
            throw std::domain_error("Stack<T> empty when peeking");

        return head->value;
    }

    const bool empty() const
    {
        return head != nullptr;
    }

};

#endif /* STACK_HPP */

