/**
Author: Kevin Morris
File: list.hpp
A generic list implementation
Copyright (C) 2014 Kevin Morris
**/
#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class List
{
private:
    typedef unsigned int uint;

    class Node
    {
    private:
        T *data_;
        Node *next_;

    public:
        Node(const T& value) : next_(NULL)
        {
            data_ = new T(value);
        }

        ~Node()
        {
            if(data_)
                delete data_;
        }

        Node *& next()
        {
            return next_;
        }

        const T& data() const
        {
            return *data_;
        }

    };

    Node *head;
    Node *tail;

    unsigned int size_;

public:

    // Set head to NULL and _size to 0
    List() : head(NULL), size_(0) {}

    ~List()
    {
        // Delete all elements of the list
        if(head)
        {
            Node *p = head;
            while(p)
            {
                Node *tmp = p;
                p = p->next();
                delete tmp;
            }
        }
    }

    bool empty() const
    {
        return size_ == 0;
    }

    const uint size() const
    {
        return size_;
    }

    List& append(const T& value)
    {
        if(!head)
        {
            head = tail = new Node(value);
        }
        else
        {
            tail->next() = new Node(value);
            tail = tail->next();
        }

        ++size_;
        return *this;
    }

    List& operator+=(const T& value)
    {
        return append(value);
    }

    const T& operator[](uint index)
    {
        if(size_ == 0 || index >= size_)
            throw std::out_of_range("index was >= List.size()");

        Node *p = head;
        for(int i = 0; i < index; ++i)
            p = p->next();
        return p->data();
    }

    bool erase(unsigned int pos)
    {
        return false;
    }
private:
    // Node swap

};

#endif /* LIST_HPP */



