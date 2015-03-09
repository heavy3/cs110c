/**
Author: Kevin Morris
A Queue data structure as practice for CS110C
Copyright (C) 2015 Kevin Morris
**/
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <utility>
#include <stdexcept>

template<typename ItemType>
class Queue
{
private:
    struct Node
    {
        ItemType value;
        Node* prev {nullptr};
        Node* next {nullptr};

        Node(ItemType data, Node* parent = nullptr, Node* child = nullptr)
            : value(std::move(data))
            , prev(parent)
            , next(child)
        {
            // Initialize node
        }
    };

    Node* head {nullptr};
    Node* tail {nullptr};

    // Count of nodes
    unsigned int size {0};

public:

    ~Queue() noexcept;

    bool isEmpty() const;
    void enqueue(ItemType newEntry);
    void dequeue();
    const ItemType& peekFront() const;

};

template<typename ItemType>
Queue<ItemType>::~Queue() noexcept
{
}

template<typename ItemType>
bool Queue<ItemType>::isEmpty() const
{
    return size == 0;
}

template<typename ItemType>
void Queue<ItemType>::enqueue(ItemType newEntry)
{
    if(!head)
    {
        head = tail = new Node(std::move(newEntry));
    }
    else
    {
        tail = new Node(std::move(newEntry), tail);
        tail->prev->next = tail;
    }

    ++size;
}

template<typename ItemType>
void Queue<ItemType>::dequeue()
{
    auto tmp = head;
    head = head->next;
    delete tmp;
    --size;
}

template<typename ItemType>
const ItemType& Queue<ItemType>::peekFront() const
{
    if(isEmpty())
        throw std::domain_error("peekFront() called when queue empty");

    return head->value;
}

#endif

