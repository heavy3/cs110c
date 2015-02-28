/* Author: Kevin Morris
 * License: GPL2
 * A test program for sort.h efficiency
 * Copyright (C) 2015 Kevin Morris
*/
#include "sort.h"
#include <cmath>
#include <memory>
#include <iostream>
#include <functional>
#include <random>
#include <typeinfo>
using namespace std;

// Initialize Complexity::O
std::vector<uint> Complexity::O {0};

template<typename T>
void printArray(T *beg, T* const end)
{
    while(beg <= end)
        cout << *beg++ << ' ';
    cout << endl;
}

uint sum(const std::vector<uint>& v)
{
    uint s = 0;
    for(auto& e : v)
        s += e;
    return s;
}

template<typename T>
bool sorted(T *beg, T* const end)
{
    while(beg < end)
    {
        if(*(beg + 1) < *beg)
            return false;
        ++beg;
    }
    return true;
}

template<typename T>
void randomArray(T *beg, T *end)
{
    random_device rd;
    uniform_int_distribution<T> dist(1, 100);
    while(beg <= end)
        *beg++ = dist(rd);
}

template<typename T, typename Functor>
void auditSort(const string& sortName, Functor fn)
{
    cout << "\n== " << sortName << " ==\n";
    auto& f = *fn; // Just bind *fn to f for convenience
    random_device rd;

    // Distribution to random a number 1-100
    uniform_int_distribution<int> dist(1, 100);

    for(uint i = 2; i <= 6; ++i)
    {
        const uint n = 2 << i;

        // Allocate data of size (2 << i) and initialize everything to random
        T *data = new T[n];

        vector<uint> passes;
        cout << "\nRun Size " << n << endl;

        for(int i = 0; i < 4; ++i)
        {
            passes.push_back(0);
            // Create randomized array
            randomArray(data, &data[n - 1]);

            Complexity::O.clear();
            f(data, &data[n - 1]); // Call sort function with 0 .. n - 1
            passes.back() = sum(Complexity::O);
            cout << "Pass " << i + 1 << "... n = " << passes.back() << ", "
                 << "Sorted: " << sorted(data, &data[n - 1]) << endl;
        }

        cout << "Average: " << sum(passes) / passes.size() << endl;

        delete [] data;
    }

    cout << endl;
}

/* Main execution point */
int main(int argc, char *argv[])
{
    auditSort<int>("Insertion", &Complexity::insertion<int>);
    auditSort<int>("Merge", &Complexity::mergeSort<int>);
    auditSort<int>("Bucket", &Complexity::bucket<int>);

    return 0;
}


