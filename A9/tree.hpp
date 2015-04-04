/* Author: Kevin Morris
 * File: tree.hpp
 * An implementation of an array-based binary search tree.
 * Copyright (C) 2015 Kevin Morris
 */
#ifndef TREE_HPP
#define TREE_HPP

#include <cmath>
#include <utility>

template<typename T>
class tree
{
private:
    /* Order of member variables matters here,
    data needs to know about POWER and exp to be allocated */
    using size_t = unsigned int;

    size_t cap {2}; // Capacity; starts at 2 and doubles when needed
    size_t sz {0};

    T* data {nullptr}; // Data array which can be table doubled
    bool* enabled {nullptr};

public:
    tree() : data(new T[cap]), enabled(new bool[cap])
    {
        /* Default constructor, allocate initial capacity */
    }

    ~tree()
    {
        delete [] enabled;
        delete [] data;
    }

    const size_t capacity() const
    {
        return cap;
    }

    const size_t size() const
    {
        return sz;
    }

    // Slots will be something like 62, or 64
    // This function will satisfy slots by allocating size
    // a power of 2 >= slots.
    void reserve(const size_t slots)
    {
        auto ln = log2(slots);
        size_t x = ln; // Exponent,
        x = ln > x ? x + 1 : x;
        cap = 2 << (x - 1);

        T *ndata = new T[cap];

        // Use algorithm to insert old values into new tree
        //
        if(sz > cap)
            sz = cap;

        copy_tree(ndata);

        delete [] data;
        data = ndata;
    }

    void add(T value)
    {
        if(sz == cap)
        {
            cap *= 2;
            // Realloc tree
            auto *d = data;
            data = new T[cap];
            copy_tree(d);
        }

        data[0] = std::move(value);
        enabled[0] = true;
        ++sz;
    }

    bool remove(const T& value)
    {
        for(size_t i = 0; i < sz; ++i)
        {
            if(enabled[i] && data[i] == value)
            {
                enabled[i] = false;
                return true;
            }
        }

        return false;
    }

    bool find(const T& value)
    {
        for(size_t i = 0; i < sz; ++i)
        {
            if(enabled[i] && data[i] == value)
                return true;
        }
        return false;
    }

private:
    void copy_tree(T *ndata) // T = new data array
    {
        for(size_t i = 0; i < sz; ++i)
            add(ndata[i]);
    }

};

#endif /* TREE_HPP */

