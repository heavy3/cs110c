//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedList.
    @file LinkedList.cpp */

#include "LinkedList.h"  // Header file
#include <cassert>
#include <string>
#include <cstdlib>

template<class T>
LinkedList<T>::LinkedList() : itemCount(0)
{
    itemCount = 0;
}  // end default constructor

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList)
    : itemCount(aList.itemCount)
{
    // Points to node in original chain
    Node<T>* origChainPtr = aList.headPtr; 
    if (origChainPtr == nullptr)
    {
        // Copy first node
        headPtr = new Node<T>();
        headPtr->setItem(origChainPtr->getItem());
        
        // Copy remaining nodes
        // Points to last node in new chain
        Node<T>* newChainPtr = headPtr;
        // Advance original-chain pointer
        origChainPtr = origChainPtr->getNext();
        while (origChainPtr != nullptr)
        {
            // Create a new node containing the next item 
            Node<T>* newNodePtr = new Node<T>(origChainPtr->getItem());  
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr); 
            
            // Advance pointer to new last node          
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while

        newChainPtr->setNext(nullptr);  // Flag end of chain
        tailPtr = newChainPtr; // Set tailPtr to the end of chain
    }  // end if
}  // end copy constructor

template<class T>
LinkedList<T>::~LinkedList()
{
    /* Traverse list and delete every allocation */
    auto p = headPtr;
    while(p)
    {
        auto t = p;
        p = p->getNext();
        delete t;
    }
    // clear();
}  // end destructor

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class T>
int LinkedList<T>::getLength() const
{
    return itemCount;
}  // end getLength

template<class T>
bool LinkedList<T>::insert(int newPos, const T& newEntry)
{
    bool ableToInsert = (newPos >= 1) && (newPos <= itemCount + 1);

    // headPTr and tailPtr are null at this point, special case to jump
    if(isEmpty())
    {
        headPtr = tailPtr = new Node<T>(newEntry);
        ++itemCount;
        return true;
    }

    if (ableToInsert)
    {

        // Create a new node containing the new entry 
        Node<T>* newNodePtr = new Node<T>(newEntry);  

        // A sloppy fix to pos = 1 insertion
        if(newPos == 1)
        {
            newNodePtr->setNext(headPtr);
            headPtr->setPrev(newNodePtr);
            headPtr = newNodePtr;
            ++itemCount;
            return ableToInsert;
        }

        // Create a current pointer to a node depending on
        // the binary split decision. The traversal will start
        // at the closer end of the list
        Node<T>* cur = getNodeAt(newPos - 1);

        if(cur->getNext())
        {
            newNodePtr->setNext(cur->getNext());
            cur->getNext()->setPrev(newNodePtr);
        }

        cur->setNext(newNodePtr);
        newNodePtr->setPrev(cur);

        ++itemCount;  // Increase count of entries

        if(tailPtr->getNext())
            tailPtr = tailPtr->getNext();

    }  // end if
    
    return ableToInsert;
}  // end insert

template<class T>
bool LinkedList<T>::remove(int pos)
{
    bool ableToRemove = (pos >= 1) && (pos <= itemCount);
    if (ableToRemove)
    {
        Node<T>* curPtr = nullptr;
        if (pos == 1)
        {
            // Remove the first node in the chain
            curPtr = headPtr; // Save pointer to node
            headPtr = headPtr->getNext();
            if(headPtr)
                headPtr->setPrev(nullptr);
        }
        else
        {
            // Find node that is before the one to delete
            Node<T>* prevPtr = getNodeAt(pos - 1);
            // Point to node to delete
            curPtr = prevPtr->getNext();
            
            // Disconnect indicated node from chain by connecting the
            // prior node with the one after
            prevPtr->setNext(curPtr->getNext());
            if(curPtr->getNext())
            {
                curPtr->getNext()->setPrev(prevPtr);
            }
            else
            {
                prevPtr->setNext(nullptr);
                tailPtr = prevPtr;
            }
        }  // end if
        
        // Return node to system - [is this step necessary?]
        curPtr->setNext(nullptr);
        delete curPtr;
        curPtr = nullptr;
        
        itemCount--;  // Decrease count of entries
    }  // end if
    
    return ableToRemove;
}  // end remove

template<class T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
        remove(1);
}  // end clear

template<class T>
const T& LinkedList<T>::getEntry(int pos) const
throw(PrecondViolatedExcep)
{
    // Enforce precondition
    bool ableToGet = (pos >= 1) && (pos <= itemCount);
    if (ableToGet)
    {
        Node<T>* nodePtr = getNodeAt(pos);
        assert(nodePtr != nullptr);
        return nodePtr->getItem();
    }
    else
    {
        string message = "getEntry() called with an empty list or "; 
        message  = message + "invalid pos.";
        throw(PrecondViolatedExcep(message)); 
    }  // end if
}  // end getEntry

template<class T>
const T& LinkedList<T>::operator[](int pos) const
throw(PrecondViolatedExcep)
{
    return getEntry(pos);
}

template<class T>
void LinkedList<T>::setEntry(int pos, const T& newEntry)
throw(PrecondViolatedExcep)
{
    // Enforce precondition
    bool ableToSet = (pos >= 1) && (pos <= itemCount);
    if (ableToSet)
    {
        Node<T>* nodePtr = getNodeAt(pos);
        nodePtr->setItem(newEntry);
    }
    else
    {
        string message = "setEntry() called with an invalid pos."; 
        throw(PrecondViolatedExcep(message)); 
    }  // end if
}  // end setEntry

/* Traverses the list and swaps pointers to reverse the list
until the current pointer reaches a null state (End of the list) */
template<class T>
void LinkedList<T>::reverse()
{
    if(!headPtr)
        return;

    auto c = headPtr; // Current pointer
    Node<T>* temp = nullptr;
    // for i = 
    while(c)
    {
        temp = c->getPrev();
        c->setPrev(c->getNext());
        c->setNext(temp);
        c = c->getPrev();
    }

    tailPtr = headPtr;
    headPtr = temp->getPrev();
}

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int pos) const
{
    // Debugging check of precondition
    assert( (pos >= 1) && (pos <= itemCount) );

    if(pos == 1)
        return headPtr;

    if(pos <= itemCount / 2)
        return getNodeAt(pos, headPtr, &Node<T>::getNext);
    return getNodeAt(itemCount - pos + 1, tailPtr, &Node<T>::getPrev);
}  // end getNodeAt

// This function recursively calls a given node and function pointer
// until pos is reduced to <= 1, then returns the current pointer
template<class T> template<class F>
Node<T>* LinkedList<T>::getNodeAt(int pos, Node<T>* ptr, F f) const
{
    return pos > 1 ? getNodeAt(pos - 1, (ptr->*f)(), f) : ptr;
}

template<class T>
bool LinkedList<T>::insertNode(int pos, Node<T>* newNode, Node<T>* subNode)
{
    if(pos < 1 || pos > itemCount + 1)
        return false;

    return true;
}

/* End Private Node helper functions */

/* Private sibling helper functions */
template<class T>
Node<T>* LinkedList<T>::grandparent(Node<T>* target)
{
    return target->getPrev() ? target->getPrev()->getPrev() : nullptr;
}

template<class T>
Node<T>* LinkedList<T>::grandchild(Node<T>* target)
{
    return target->getNext() ? target->getNext()->getNext() : nullptr;
}

template<class T>
Node<T>* LinkedList<T>::parent(Node<T>* target)
{
    return target->getPrev();
}

template<class T>
Node<T>* LinkedList<T>::child(Node<T>* target)
{
    return target->getNext();
}


/* End sibling helper functions */

// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use (int or string now,
// add more types if necessary)
template class LinkedList<int>;
template class LinkedList<std::string>;



