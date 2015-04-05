/* Author: Kevin Morris
 * File: main.cpp
 * Unit tests for an array-based binary search tree.
 * Copyright (C) 2015 Kevin Morris
 */
#include "tree.hpp"
#include <vector>
#include <iostream>
using namespace std;

void tree(std::initializer_list<string> il)
{
    static unsigned int ti = 0; // Test index
    cout << "Tree Test " << ++ti << endl;

    ArrayTree<string> bt(il);
    cout << "Binary Tree Size: " << bt.capacity() << endl;

    cout << "Insertion order: ";
    for(auto& e : il)
        cout << e << ' ';
    cout << endl;

    bt.preorder();
    cout << endl;
}

int main(int argc, char *argv[])
{
    tree({"10", "20", "30", "40"});
    tree({"10", "25", "35", "45"});
    tree({"35", "25", "15", "65", "10"});

    return 0;
}

