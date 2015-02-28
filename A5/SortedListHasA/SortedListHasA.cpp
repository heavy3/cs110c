//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class SortedListHasA.
 @file SortedListHasA.cpp */

#include "SortedListHasA.h"  // Header file
#include <cassert>
#include <cmath>
  
template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA()
{
    //listPtr = new LinkedList<ItemType>();
}  // end default constructor

template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA(const SortedListHasA<ItemType>& sList) 
{
	// First, create our own list
	//listPtr = new LinkedList<ItemType>();
	
	// Then add items to it using public methods
	for(int position = 1; position <= sList.getLength(); position++)
	{
		list.insert(position, sList.getEntry(position));
	}  // end for	
}  // end copy constructor

template<class ItemType>
SortedListHasA<ItemType>::~SortedListHasA()
{
    clear();

    // Delete LinkedList member
    //delete static_cast<LinkedList<ItemType>*>(listPtr);
}  // end destructor

template<class ItemType>
void SortedListHasA<ItemType>::insertSorted(const ItemType& newEntry)
{
    int newPosition = fabs(getPosition(newEntry));
    list.insert(newPosition, newEntry);
}  // end insertSorted

template<class ItemType>
bool SortedListHasA<ItemType>::removeSorted(const ItemType& anEntry)
{
    bool ableToRemove = false;
    if (!isEmpty())
    {
        int position = getPosition(anEntry);
                 
        ableToRemove = position > 0;
        if (ableToRemove)
        {
            ableToRemove = list.remove(position);
        }  // end if
    }  // end if

    return ableToRemove;
}  // end removeSorted

template<class ItemType>
int SortedListHasA<ItemType>::getPosition(const ItemType& anEntry) const
{
    int pos = 1;

    for(; pos <= list.getLength(); ++pos)
    {
        auto target = list.getEntry(pos);
        if(anEntry == target)
            return pos;
        else if(anEntry < target)
            break;
    }

    return -pos;
}  // end getPosition

//=====================
// List operations:

template<class ItemType>
bool SortedListHasA<ItemType>::remove(int position)
{
    return list.remove(position);
}  // end remove

template<class ItemType>
void SortedListHasA<ItemType>::clear()
{
    list.clear();
}  // end clear

template<class ItemType>
ItemType SortedListHasA<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
    return list.getEntry(position);
}  // end getEntry

template<class ItemType>
bool SortedListHasA<ItemType>::isEmpty() const
{
    return list.isEmpty();
}  // end isEmpty

template<class ItemType>
int SortedListHasA<ItemType>::getLength() const
{
    return list.getLength();
}  // end getLength

// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use in this .cpp file.
// (just strings for now, add more types if desired)
template class SortedListHasA<std::string>;
template class SortedListHasA<int>;

