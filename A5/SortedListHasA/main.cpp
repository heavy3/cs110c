//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Edited by Kevin Morris; Copyright (C) 2015 Kevin Morris
#include "SortedListHasA.h" // ADT sorted list operations
#include <iostream>
#include <string>
#include <limits>
using namespace std;

string getInput(string message)
{
    cout << message;
    string temp;
    getline(cin, temp);
    return temp;
}

// Gets input for a score
int getScore()
{
    string temp = getInput("Enter a score (negative to quit): ");
    int value;

    try
    {
        value = stoi(temp);
    }
    catch(...) {
        // std::stoi failed, so clear up the stream and try again
        cout << "You did not enter a valid integer\n";
        return getScore();
    }

    return value;
}

template<typename T>
void printDescending(const SortedListHasA<T>& L, string label = "")
{
    cout << label;
    for(int i = L.getLength(); i >= 1; --i)
        cout << L.getEntry(i) << ' ';
    cout << endl;
}

int max(const SortedListHasA<int>& L)
{
    if(L.getLength() == 0)
        return -1;

    int max = L.getEntry(1);
    for(int i = 2; i <= L.getLength(); ++i)
    {
        auto entry = L.getEntry(i);
        if(entry > max)
            max = entry;
    }

    return max;
}

// Main execution point
int main(int argc, char *argv[])
{
    SortedListHasA<int> list;

    int newScore = getScore();
    while(newScore >= 0)
    {
        list.insertSorted(newScore);
        printDescending(list, "High Scores: ");
        newScore = getScore();
    }

    cout << "Good bye! The highest score was " << max(list) << endl;

    return 0;
}

/*
void displayList(SortedListInterface<string>* listPtr)
{
	cout << "The sorted list contains " << endl;
   for (int pos = 1; pos <= listPtr->getLength(); pos++)
   {
      cout << listPtr->getEntry(pos) << " ";
   } // end for
	cout << endl << endl;
}  // end displayList

void copyConstructorTester()
{
	SortedListHasA<string> list;
   string items[] = {"zero", "one", "two", "three", "four", "five"};
	for (int i = 0; i < 6; i++)
   {
		cout << "Adding " << items[i] << endl;
      list.insertSorted(items[i]);
	}
   displayList(&list);
   
   SortedListHasA<string> copyOfList(list);
   cout << "Copy of list: ";
   displayList(&copyOfList);
   
   cout << "The copied list: ";
   displayList(&list);
}  // end copyConstructorTester

void sortedListTester(SortedListInterface<string>* listPtr)
{
   string luke = "Luke";
   string brent = "Brent";
   string donna = "Donna";
   string tom = "Tom";
   string sue = "Sue";
   string jerry = "Jerry";
   
   cout << "\nTest isEmpty with an empty list:" << endl;
   if (listPtr->isEmpty())
      cout << "OK" << endl;
   else
      cout << "isEmpty() error" << endl;
	
   listPtr->insertSorted(luke);
   listPtr->insertSorted(brent);
   listPtr->insertSorted(donna);
   listPtr->insertSorted(tom);
   listPtr->insertSorted(sue);
   listPtr->insertSorted(jerry);
   
   // display the list
   cout << "List should contain\nBrent, Donna, " <<
   "Jerry, Luke, Sue, Tom" << endl;
   cout << "\nList actually contains:" << endl;
   displayList(listPtr);
   cout << endl;
   
   // test getPosition
   cout << "\nTest getPosition:\n" << endl;
   
   // These names are in the list
   cout << "Brent is at position " << listPtr->getPosition(brent) << endl;
   cout << "Donna is at position " << listPtr->getPosition(donna) << endl;
   cout << "Jerry is at position " << listPtr->getPosition(jerry) << endl;
   cout << "Luke is at position "  << listPtr->getPosition(luke) << endl;
   cout << "Sue is at position "   << listPtr->getPosition(sue) << endl;
   cout << "Tom is at position "   << listPtr->getPosition(tom) << endl;
   
   // These names are not in the list
   string missy = "Missy";
   cout << "Missy belongs at position " << listPtr->getPosition(missy) << endl;
   string zeke = "Zeke";
   cout << "Zeke belongs at position " << listPtr->getPosition(zeke) << endl;
   string aaron = "Aaron";
   cout << "Aaron belongs at position " << listPtr->getPosition(aaron) << endl;
   
   // test getLength and getEntry
   cout << "\nTest getLength and getEntry:\n" << endl;
   
   cout << "\nList has " << listPtr->getLength() << " entries, as follows:\n" << endl;
   for (int i = 1; i <= listPtr->getLength(); i++)
      cout << i << ": " << listPtr->getEntry(i) << endl;
   
   
   // test remove
   cout << "\nTest remove:\n" << endl;
   
   // remove first entry
   cout << "\nRemoving first item (Brent): " << listPtr->removeSorted(brent) << "; should be 1 (true)" << endl;
   cout << "\nAfter removing Brent, list contains " << listPtr->getLength()
   << " items, as follows:" << endl;
   displayList(listPtr);
   
   // remove interior
   cout << "\nRemoving interior item (Luke): " << listPtr->removeSorted(luke) << "; should be 1 (true)" << endl;
   cout << "\nAfter removing Luke, list contains " << listPtr->getLength()
   << " items, as follows:" << endl;
   displayList(listPtr);
   
   // remove last
   cout << &"\nRemoving last item (Tom): " [ listPtr->removeSorted(tom)] << "; should be 1 (true)" << endl;
   cout << "\nAfter removing last item, list contains " << listPtr->getLength()
   << " items, as follows:" << endl;
   displayList(listPtr);
   
   cout << "\nRemoving a missing item (Brent): " << listPtr->removeSorted(brent) << "; should be 0 (false)" << endl;
   cout << "\nRemoving a missing item (Luke): " << listPtr->removeSorted(luke) << "; should be 0 (false)" << endl;
   cout << "\nRemoving a missing item (Tom): " << listPtr->removeSorted(tom) << "; should be 0 (false)" << endl;
   
   cout << "\nThe list contains " << listPtr->getLength()
   << " items, as follows:" << endl;
   displayList(listPtr);
   
   // test clear()
   cout << "\nTest clear():\n" << endl;
   listPtr->clear();
   
   if (listPtr->isEmpty())
      cout << "\nThe list is empty after invoking clear()." << endl;
   else
      cout << "\nclear() error" << endl;
} // end sortedListTester

void listOpsTester(SortedListInterface<string>* listPtr)
{
   string luke = "Luke";
   string brent = "Brent";
   string donna = "Donna";
   string tom = "Tom";
   string sue = "Sue";
   string jerry = "Jerry";
   
   listPtr->insertSorted(luke);
   listPtr->insertSorted(brent);
   listPtr->insertSorted(donna);
   listPtr->insertSorted(tom);
   listPtr->insertSorted(sue);
   listPtr->insertSorted(jerry);
   
   displayList(listPtr);
   
   cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 0 (false)" << endl;
   cout << "getLength returns : " << listPtr->getLength() << "; should be 6" << endl;
   
   cout << "remove(2): returns " << listPtr->remove(2) << "; should be 1 (true)" << endl;
   cout << "remove(1): returns " << listPtr->remove(1) << "; should be 1 (true)" << endl;
   cout << "remove(6): returns " << listPtr->remove(6) << "; should be 0 (false)" << endl;
   displayList(listPtr);
   cout << "getLength returns : " << listPtr->getLength() << "; should be 4" << endl;
   cout << "clear: " << endl;
   listPtr->clear();
   cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)" << endl;
   
   try
   {
      cout << "Attempt an illegal retrieval from position 6: " << endl;
      listPtr->getEntry(6);
   }
   catch(PrecondViolatedExcep e)
   {
      cout << e.what() << endl;
   }  // end try/catch
} // end listOpsTester

int main()
{
   copyConstructorTester();

	SortedListInterface<string>* listPtr = new SortedListHasA<string>();
	cout << "Testing the Link-Based Sorted List:" << endl;
	sortedListTester(listPtr);
   cout << "======================================" << endl;
   
	cout << "\nTesting the List Operations:" << endl;
	listOpsTester(listPtr);

   return 0;
}  // end main

*/

/*
 Adding zero
 Adding one
 Adding two
 Adding three
 Adding four
 Adding five
 The sorted list contains
 five four one three two zero
 
 Copy of list: The sorted list contains
 five four one three two zero
 
 The copied list: The sorted list contains
 five four one three two zero
 
 Testing the Link-Based Sorted List:
 
 Test isEmpty with an empty list:
 OK
 List should contain
 Brent, Donna, Jerry, Luke, Sue, Tom
 
 List actually contains:
 The sorted list contains
 Brent Donna Jerry Luke Sue Tom
 
 
 
 Test getPosition:
 
 Brent is at position 1
 Donna is at position 2
 Jerry is at position 3
 Luke is at position 4
 Sue is at position 5
 Tom is at position 6
 Missy belongs at position -5
 Zeke belongs at position -7
 Aaron belongs at position -1
 
 Test getLength and getEntry:
 
 
 List has 6 entries, as follows:
 
 1: Brent
 2: Donna
 3: Jerry
 4: Luke
 5: Sue
 6: Tom
 
 Test remove:
 
 
 Removing first item (Brent): 1; should be 1 (true)
 
 After removing Brent, list contains 5 items, as follows:
 The sorted list contains
 Donna Jerry Luke Sue Tom
 
 
 Removing interior item (Luke): 1; should be 1 (true)
 
 After removing Luke, list contains 4 items, as follows:
 The sorted list contains
 Donna Jerry Sue Tom
 
 Removing last item (Tom): ; should be 1 (true)
 
 After removing last item, list contains 3 items, as follows:
 The sorted list contains
 Donna Jerry Sue
 
 
 Removing a missing item (Brent): 0; should be 0 (false)
 
 Removing a missing item (Luke): 0; should be 0 (false)
 
 Removing a missing item (Tom): 0; should be 0 (false)
 
 The list contains 3 items, as follows:
 The sorted list contains
 Donna Jerry Sue
 
 
 Test clear():
 
 
 The list is empty after invoking clear().
 ======================================
 
 Testing the List Operations:
 The sorted list contains
 Brent Donna Jerry Luke Sue Tom
 
 isEmpty: returns 0; should be 0 (false)
 getLength returns : 6; should be 6
 remove(2): returns 1; should be 1 (true)
 remove(1): returns 1; should be 1 (true)
 remove(6): returns 0; should be 0 (false)
 The sorted list contains
 Jerry Luke Sue Tom
 
 getLength returns : 4; should be 4
 clear:
 isEmpty: returns 1; should be 1 (true)
 Attempt an illegal retrieval from position 6:
 Precondition Violated Exception: getEntry() called with an empty list or invalid position.

*/
