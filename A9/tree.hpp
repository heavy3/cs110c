/* Author: Kevin Morris
 * File: tree.hpp
 * An implementation of an array-based binary search tree.
 * Copyright (C) 2015 Kevin Morris
 */
#ifndef TREE_HPP
#define TREE_HPP

#include <cmath>
#include <utility>
#include <stdexcept>
#include <iostream>

/*! @class ArrayTree
 * A templated class that performs insertions and traversals
 * on a given specific type T. This structure is a Complete
 * Binary Tree implemented with an array of nodes.
 */
template<typename T>
class ArrayTree
{
private:
    /* Order of member variables matters here,
    data needs to know about cap */
    using size_t = unsigned int; // Type alias

    size_t cap {8}; // Capacity; starts at 8 (height 3)
    size_t sz {0}; // No items are inserted at initialization

    /* A node with two members: value, and enabled.
     * Enabled keeps track of null state. false == null. */
    struct Node
    {
        T value;
        bool enabled {false};
    };

    Node *data; // Will be an array of Nodes

public:
    ArrayTree() : data(new Node[cap])
    {
        /* Default constructor, allocate initial capacity */
    }

    ArrayTree(std::initializer_list<T> il)
        : data(new Node[cap])
    {
        if(il.size() > cap)
            throw std::domain_error("Initializer List too large");

        for(auto& e : il)
            add(std::move(e));
    }

    /* Frees our array */
    ~ArrayTree()
    {
        delete [] data;
    }

    // Return the capacity of the current array
    const size_t capacity() const
    {
        return cap;
    }

    // Return the size of the tree: The number of items we've added.
    const size_t size() const
    {
        return sz;
    }

    /* Adds one value of type T to the tree. */
    bool add(T value)
    {
        if(sz == cap) /* If we're full, return false */
            return false;

        size_t i = getFirstEmptyNode();

        // Set value and set node to enabled (non-null flag)
        data[i].value = std::move(value);
        data[i].enabled = true;
        ++sz; // Increase real length of the tree

        return true; // Operations went smoothly
    }

    void preorder()
    {
        std::cout << "Preorder Traversal: ";
        preorder(1);
        std::cout << std::endl;
    }



private:
    /* Left child of a given index in a Complete Binary Tree */
    size_t leftChild(size_t i)
    {
        return i * 2;
    }

    /* Right child of a given index in a Complete Binary Tree */
    size_t rightChild(size_t i)
    {
        return i * 2 + 1;
    }

    /* Starting at the root, recursively traverse the tree
     * preorder to find the first empty node encountered */
    size_t getFirstEmptyNode(size_t i = 1) // Starts at root = 1
    {
        if(data[i].enabled)
        {
            size_t c = leftChild(i); // Look at left child
            if(data[c].enabled) // If left child != null
                c = rightChild(i); // Look at right child
            if(data[c].enabled) // If right child != null
                c = leftChild(i); // Then we move to left child
            i = c; // Set index to decided child
            return getFirstEmptyNode(i); // Recurse with new index
        }

        return i; // When not data[i].enabled
    }

    /* Preorder traversal. From root to left to right,
     * this function recursively prints out the current node */
    void preorder(size_t i)
    {
        if(data[i].enabled)
        {
            std::cout << data[i].value << ' ';
            preorder(leftChild(i));
            preorder(rightChild(i));
        }
    }

};

#endif /* TREE_HPP */

