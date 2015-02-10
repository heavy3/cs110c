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
            
    newChainPtr->setNext(nullptr);  // Flag end of chain
    }  // end if
}  // end copy constructor

template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
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
    if(itemCount == 0)
    {
        headPtr = tailPtr = new Node<T>(newEntry);
        ++itemCount;
        return true;
    }

    if (ableToInsert)
    {
        // Create a new node containing the new entry 
        Node<T>* newNodePtr = new Node<T>(newEntry);  

        // This implementation ignores newPos, and always put the new
        // item at the beginning of the list.
        // Your assignment is to correctly insert the item into newPos
        std::cout << "NewPos: " << newPos << std::endl;

        auto node = getNodeAt(newPos - 1);
        std::cout << "Inserting at: " << node->getItem() << std::endl;
        newNodePtr->setNext(node);
        if(node->getPrev())
        {
            node->getPrev()->setNext(newNodePtr);
            newNodePtr->setPrev(node->getPrev());
        }
        node->setPrev(newNodePtr);

        ++itemCount;  // Increase count of entries
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
        }  // end if
        
        // Return node to system
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

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int pos) const
{
    // Debugging check of precondition
    assert( (pos >= 1) && (pos <= itemCount) );

    if(pos == 1)
        return headPtr;

    // Count from the beginning of the chain
    if(pos <= getLength() / 2)
        return getNodeAt(pos, headPtr, &Node<T>::getNext);

    return getNodeAt(getLength() - pos, tailPtr, &Node<T>::getPrev);
}  // end getNodeAt


// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use (int or string now,
// add more types if necessary)
template class LinkedList<int>;
template class LinkedList<std::string>;



