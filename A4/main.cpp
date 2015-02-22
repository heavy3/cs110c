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

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&... args)
{
    return unique_ptr<T>(new T(forward<Args>(args)...));
}

/* Main helper functions */
template<typename T>
void noop(T *src, uint size) {}

template<typename T, typename Functor = decltype(noop<T>)>
void auditSort(Functor fn = &noop)
{
    auto& f = *fn;
    random_device rd;

    // Distribution to random a number 1-100
    uniform_int_distribution<int> dist(1, 100);

    for(uint i = 2; i <= 4; ++i)
    {
        const uint n = 2 << i;

        // Allocate data of size (2 << i) and initialize everything to random
        T *data = new T[n];
        for(uint k = 0; k < n; ++k)
        {
            data[k] = dist(rd);
            cout << data[k] << ' ';
        }
        cout << endl;

        f(data, 0, n);

        for(uint k = 0; k < n; ++k)
            cout << data[k] << ' ';
        cout << endl;

        delete [] data;
    }

}

/* Main execution point */
int main(int argc, char *argv[])
{
    random_device rd;

    auto fn = &Complexity::insertion<int>;

    auditSort<int>(fn);
    auditSort<int>(&Complexity::merge<int>);
    //auditSort<int>(&Complexity::bucket<int>);

    return 0;
}


