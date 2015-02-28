#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include <stdexcept>
#include <iostream>
template<typename T>
class Stack
{
private:

    struct Node
    {
        T data;
        Node* next {nullptr};

        Node(T newData) : data(std::move(newData)) {}
    };

    Node* head {nullptr}; // Null out head pointer
    std::size_t size {0}; // Start off at 0, since we have no elements

public:

    void push(T data)
    {
        auto p = head;
        std::cout << head << " >> ";
        head = new Node(std::move(data));
        std::cout << head << std::endl;
        head->next = p;

        std::cout << head << " -> " << head->next << std::endl;
        ++size;
    }

    const T& peek() const
    {
        return head->data;
    }

    T pop()
    {
        if(empty())
            throw std::domain_error("pop() called from empty stack");

        auto p = head;
        head = head->next;
        T data = std::move(p->data);
        delete p;

        --size;
        return std::move(data);
    }

    const std::size_t length() const
    {
        return size;
    }

    const bool empty() const
    {
        return size == 0;
    }

};

#endif /* STACK_HPP */

