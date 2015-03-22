/**
Author: Kevin Morris
File: queue.hpp
License: GPL2
A queue data structure for Assignment 7: CS110C
Copyright (C) 2015 Kevin Morris
**/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <string>
#include <stdexcept>

/* A Circular Queue data structure. Relies on having + 1 size internally
to fix a empty/full issue with a circular structure of size n */
template<typename T, const std::size_t MAX_QUEUE = 7>
class Queue
{
private:
    T data[MAX_QUEUE + 1];

    std::size_t front = 0;
    std::size_t back  = 0;

    const std::size_t increment(const std::size_t n) const
    {
        return (n + 1) % (MAX_QUEUE + 1);
    }

public:
    Queue() = default;

    const bool empty() const
    {
        return front == back;
    }

    const bool full() const
    {
        return front == increment(back);
    }

    bool enqueue(T value)
    {
        if(full())
            return false;

        data[back] = std::move(value);
        back = increment(back);
        return true;
    }

    T dequeue()
    {
        if(empty())
            throw std::domain_error("Queue<T> dequeued while empty");
        T temp { std::move(data[front]) };
        front = increment(front);
        return temp;
    }

    const T& peek() const
    {
        if(empty())
            throw std::domain_error("Queue<T> peeked while empty");
        return data[front];
    }

};

#endif /* QUEUE_HPP */

