//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Edited portions of the code, eg. ItemType = T, and implementations
//  differ.
/** Implementation file for the class LinkedList.
 @file LinkedList.cpp */
#include "LinkedList.h"  // Header file
#include <cassert>
#include <string>
#include <cstdlib>

template<class T>
LinkedList<T>::LinkedList() : itemCount(0)
{
}  // end default constructor

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList)
    : itemCount(aList.itemCount)
{
    // Points to nodes in original chain
    Node<T>* origChainPtr = aList.headPtr;

    if (origChainPtr)
        headPtr = nullptr;  // Original list is empty
    else
    {
        // Copy first node
        headPtr = new Node<T>(origChainPtr->getItem());

        // Copy remaining nodes
        // Points to last node in new chain
        Node<T>* newChainPtr = headPtr;

        // Advance original-chain pointer
        origChainPtr = origChainPtr->getNext();
        
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            T nextItem = origChainPtr->getItem();
            
            // Create a new node containing the next item 
            Node<T>* newNodePtr = new Node<T>(nextItem);  
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr); 
            
            // Advance pointer to new last node        
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while
        
        // Flag end of chain
        newChainPtr->setNext(nullptr);
    } // end if
} // end copy constructor

template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
} // end destructor

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return itemCount == 0;
} // end isEmpty

template<class T>
int LinkedList<T>::getLength() const
{
    return itemCount;
} // end getLength

template<class T>
bool LinkedList<T>::insert(int newPos, const T& newEntry)
{
    bool ableToInsert = (newPos >= 1) && (newPos <= itemCount + 1);

    if (!ableToInsert)
        return false;

    // Create a new node containing the new entry 
    Node<T>* newNodePtr = new Node<T>(newEntry);

    // Insert value at newPos
    if(!headPtr)
    {
        headPtr = tailPtr = newNodePtr;
        ++itemCount;
        return true;
    }

    // Start from tailPtr and go back.

    Node<T> *ptr = getNodeAt(newPos - 1);
    // Add new node at (pos - 1)->next position and swap parents
    // and children of the node.
    ptr->setNext(newNodePtr);
    ptr->getNext()->setPrev(ptr);

    itemCount++; // Increase count of entries
    
    return ableToInsert;
} // end insert

template<class T>
bool LinkedList<T>::insert(int newPos, T&& newEntry)
{
    return true;
}

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
        } // end if
        
        // Return node to system
        curPtr->setNext(nullptr);
        delete curPtr;
        curPtr = nullptr;
        
        itemCount--;  // Decrease count of entries
    } // end if
    
    return ableToRemove;
} // end remove

template<class T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
        remove(1);
} // end clear

template<class T>
const T& LinkedList<T>::getEntry(int pos) const
throw(PrecondViolatedExcep)
{
    // Enforce precondition
    bool ableToGet = (pos >= 1) && (pos <= itemCount);
    if (!ableToGet)
    {
        string message = "getEntry() called with an empty list or "; 
        message  = message + "invalid pos.";
        throw(PrecondViolatedExcep(message)); 
    } // end if
    Node<T>* nodePtr = getNodeAt(pos);
    return nodePtr->getItem();
} // end getEntry

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
        throw PrecondViolatedExcep(message);
    }  // end if
}  // end setEntry

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int pos) const
{
    // Debugging check of precondition
    assert( (pos >= 1) && (pos <= itemCount) );
    
    // Count from the beginning of the chain
    Node<T>* curPtr = headPtr;

    if(pos <= getLength() / 2)
    {
        curPtr = getNodeRecursive(pos, headPtr, &Node<T>::getNext);
    }
    else
    {
        curPtr = getNodeRecursive(getLength() - pos,
                                  tailPtr, &Node<T>::getPrev);
    }

    return curPtr;
} // end getNodeAt

/*
template<class T, typename F>
Node<T>*
LinkedList<T>::getNodeRecursive(int pos,
                                Node<T>* curPtr,
                                F f = F()) const
{
    return pos > 0 ? getNodeRecursive(pos - 1, curPtr->getNext()) : curPtr;
}
*/

// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use (int or string now,
// add more types if necessary)
template class LinkedList<int>;
template class LinkedList<std::string>;


