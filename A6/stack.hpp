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

    // Our private node that will be used to track stack entries
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

    // Our head pointer, and stack entry count sz
    std::unique_ptr<Node> head {nullptr};
    std::size_t sz {0};

public:

    /* + push(value: T): void
    /  @value: A valid lvalue or rvalue object or built-in
    /  Push value of type T onto the stack, increase size by one */
    void push(T value) noexcept
    {
        head = std::make_unique<Node>(std::move(value), std::move(head));
        ++sz;
    }

    /* + pop(void): T
    /  @return value popped off of the stack
    /  Pop a value off of the stack and return it to the user
    /  Decrement size to reflect the change in the stack
    /  Throw if the stack is empty and a pop was attempted
    /  This function does not copy values back to the user */
    T pop()
    {
        if(empty())
            throw std::domain_error("Stack<T> empty when attempting to pop");

        // "Move" head->value into value, since we don't need it anymore
        T value { std::move(head->value) };
        // Move head to head->next, losing head's reference and destroying it
        head = std::move(head->next);
        --sz;
        return value;
    }

    /* + peek(void): const T
    /  @return Constant version of the value at the top of the stack
    /  "Peek" at the top value in the stack */
    const T& peek() const
    {
        if(empty())
            throw std::domain_error("Stack<T> empty when peeking");

        return head->value;
    }

    /* + empty(void): const bool
    /  @return The "empty" state of the string */
    const bool empty() const
    {
        // If head is false, we have no values; thus, empty.
        return !head;
    }

    /* + size(void): const std::size_t
    /  @return The size of the container; how many elements exist
    /  std::size_t can be replaced as unsigned int */
    const std::size_t size() const
    {
        return sz;
    }

    /* + traverse(void): void
     * Traverse the stack and print everything out */
    void traverse()
    {
        std::cout << "Stack: ";

        // Get raw head node pointer
        auto *p = head.get();
        while(p) // while p is not null
        {
            std::cout << p->value << ' ';
            p = p->next.get(); // set p to p->next raw pointer
        }

        std::cout << std::endl;
    }

};

#endif /* STACK_HPP */

