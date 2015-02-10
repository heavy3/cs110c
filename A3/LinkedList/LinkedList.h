//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Edited by Kevin Morris

/** ADT list: Link-based implementation.
     Listing 9-2.
     @file LinkedList.h */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"
#include <iostream>

template<class T>
class LinkedList : public ListInterface<T>
{
private:
    Node<T>* headPtr {nullptr}; // Pointer to first node in the chain;
    Node<T>* tailPtr {nullptr}; // (contains the first entry in the list)
    int itemCount; // Current count of list items 
    
    // Locates a specified node in this linked list.
    // @pre  pos is the number of the desired node;
    //         pos >= 1 and pos <= itemCount.
    // @post  The node is found and a pointer to it is returned.
    // @param pos  The number of the node to locate.
    // @return  A pointer to the node at the given pos.
    Node<T>* getNodeAt(int pos) const;

    /* This function takes an anonymous typed function pointer to
     * use for traversing the Node list in the proper direction */
    template<typename F>
    Node<T>* getNodeRecursive(int pos, Node<T>* curPtr, F f = F()) const
    {
        std::cout << "Node: " << curPtr->getItem() << std::endl;
        return pos > 0 ? getNodeRecursive(pos - 1, (curPtr->*f)(), f) : curPtr;
    }

public:
    LinkedList();
    LinkedList(const LinkedList<T>& aList);
    virtual ~LinkedList();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPos, const T& newEntry);
    bool insert(int newPos, T&& newEntry); // Move/Forward insertion
    bool remove(int pos);
    void clear();
    
    /** @throw PrecondViolatedExcep if pos < 1 or 
    pos > getLength(). */
    const T& getEntry(int pos) const throw(PrecondViolatedExcep);
    const T& operator[](int pos) const throw(PrecondViolatedExcep);

    /** @throw PrecondViolatedExcep if pos < 1 or 
    pos > getLength(). */
    void setEntry(int pos, const T& newEntry) throw(PrecondViolatedExcep);

}; // end LinkedList

#endif


