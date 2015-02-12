//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT list: Link-based implementation.
     Listing 9-2.
     @file LinkedList.h */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
#include <cassert>
#include <iostream>

template<class T>
class LinkedList : public ListInterface<T>
{
private:
    Node<T>* headPtr {nullptr}; // Pointer to first node in the chain
    Node<T>* tailPtr {nullptr}; // Pointer to last node in the chain
    int itemCount; // Current count of list items 
    
public:
    LinkedList();
    LinkedList(const LinkedList<T>& aList);
    virtual ~LinkedList();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPos, const T& newEntry);
    bool remove(int pos);
    void clear();
    
    /** @throw PrecondViolatedExcep if pos < 1 or 
    pos > getLength(). */
    const T& getEntry(int pos) const throw(PrecondViolatedExcep);

    const T& operator[](int pos) const throw(PrecondViolatedExcep);

    /** @throw PrecondViolatedExcep if pos < 1 or 
    pos > getLength(). */
    void setEntry(int pos, const T& newEntry) throw(PrecondViolatedExcep);

    void reverse();

private:
    // Locates a specified node in this linked list.
    // @pre  pos is the number of the desired node;
    //         pos >= 1 and pos <= itemCount.
    // @post  The node is found and a pointer to it is returned.
    // @param pos  The number of the node to locate.
    // @return  A pointer to the node at the given pos.
    Node<T>* getNodeAt(int pos) const;

    /* Recursive node search function
    @pos    The position of the desired node;
            This value is reduced by 1 per recursion call.
    @ptr    The initial pointer: headPtr or tailPtr.
    @f      The corresponding functor (or function pointer) for @ptr.
    This function is called indirectly by getNodeAt(pos), with the
    proper ptr and function pointer depending on pos <= size / 2 or not */
    template<class F>
    Node<T>* getNodeAt(int pos, Node<T>* ptr, F f = F()) const;

    bool insertNode(int pos, Node<T>* newNode, Node<T>* subNode);


    Node<T>* grandparent(Node<T>* target);
    Node<T>* grandchild(Node<T>* target);
    Node<T>* parent(Node<T>* target);
    Node<T>* child(Node<T>* target);

}; // end LinkedList

#endif 
