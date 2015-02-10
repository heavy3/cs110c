//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Node.cpp 
    Listing 4-2 */
#include "Node.h"
#include <cstddef>
#include <string>

template<class T>
Node<T>::Node() : next(nullptr)
{
} // end default constructor

template<class T>
Node<T>::Node(const T& anItem) : item(anItem), next(nullptr)
{
} // end constructor

template<class T>
Node<T>::Node(const T& anItem, Node<T>* nextNodePtr) :
                item(anItem), next(nextNodePtr)
{
} // end constructor

template<class T>
void Node<T>::setItem(const T& anItem)
{
   item = anItem;
} // end setItem

template<class T>
void Node<T>::setPrev(Node<T>* prevNodePtr)
{
    prev = prevNodePtr;
}

template<class T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template<class T>
const T& Node<T>::getItem() const
{
   return item;
} // end getItem

template<class T>
Node<T>* Node<T>::getPrev() const
{
    return prev;
}

template<class T>
const Node<T>& Node<T>::operator--() const
{
    if(prev)
        return *prev;
    return *this;
}

template<class T>
Node<T>* Node<T>::getNext() const
{
   return next;
} // end getNext

template<class T>
const Node<T>& Node<T>::operator++() const
{
    if(next)
        return *next;
    return *this;
}

//  End of implementation file.  Add definitions of template types we will use (int or string):
template class Node<int>;
template class Node<std::string>;
