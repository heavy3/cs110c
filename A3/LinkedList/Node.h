//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
/* Source edited by Kevin Morris */

/** @file Node.h 
     Listing 4-1 */
#ifndef _NODE
#define _NODE

template<class T>
class Node
{
private:
    T item; // A data item
    Node<T>* next {nullptr}; // Pointer to next node
    Node<T>* prev {nullptr};

public:
    Node();
    Node(const T& anItem);
    Node(const T& anItem, Node<T>* nextNodePtr);
    void setItem(const T& anItem);
    void setPrev(Node<T>* prevNodePtr);
    void setNext(Node<T>* nextNodePtr);
    const T& getItem() const;

    // A getter function for the parent node
    Node<T>* getPrev() const;

    // An iteration function, returns the reference of parent node
    const Node<T>* operator--() const;

    Node<T>* getNext() const;

    // An iteration function, returns the reference of next node
    const Node<T>* operator++() const;

}; // end Node

#endif
