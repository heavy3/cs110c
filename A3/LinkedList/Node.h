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

    Node<T>* getPrev() const;
    Node<T>* getNext() const;


}; // end Node

#endif
