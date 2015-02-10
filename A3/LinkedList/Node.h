//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
/** @file Node.h 
    Listing 4-1 */
#ifndef _NODE_H
#define _NODE_H

template<class T>
class Node
{
private:
    T item; // A data item
    Node<T>* prev {nullptr}; // Parent node
    Node<T>* next {nullptr}; // Pointer to next node

public:
    Node();
    Node(const T& anItem);
    Node(const T& anItem, Node<T>* nextNodePtr);

    void setItem(const T& anItem);
    void setPrev(Node<T>* prevNodePtr);
    void setNext(Node<T>* nextNodePtr);

    const T& getItem() const;
    Node<T>* getPrev() const;
    Node<T>* getNext() const;

}; // end Node

#endif


