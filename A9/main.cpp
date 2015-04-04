/* Author: Kevin Morris
 * File: main.cpp
 * Unit tests for an array-based binary search tree.
 * Copyright (C) 2015 Kevin Morris
 */
#include "tree.hpp"
#include <iostream>
using namespace std;

void test_tree()
{
    static unsigned int ti = 0; // Test index
    ++ti;

    cout << "Tree Test " << ti << endl;

    tree<string> bst;
    bst.reserve(16);
    cout << "Start size: " << bst.capacity() << endl;

}

int main(int argc, char *argv[])
{
    test_tree();
    test_tree();
    test_tree();

    return 0;
}

