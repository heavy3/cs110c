/* Author: Kevin Morris
 * License: GPL2
 * A set of sorting algorithms in different stages of O(complexity)
 * Copyright (C) 2015 Kevin Morris
*/
#ifndef SORT_H
#define SORT_H

#include <algorithm>
#include <vector>
#include <array>
#include <iostream> // Debug
using uint = unsigned int;

class Complexity
{
public:
    template<typename T>
    static void insertion(T *src, uint start, uint size)
    {
        int min {0};
        uint idx {0};
        for(uint i = start; i < size - 1; ++i)
        {
            min = src[(idx = i)];
            for(uint j = i + 1; j < size; ++j)
            {
                // Increase comparison count
                if(src[j] < min)
                {
                    min = src[(idx = j)];
                }
            }
            if(i != idx)
                std::swap(src[i], src[idx]);
        }

    }

    template<typename T>
    static void merge(T *src, uint start, uint end)
    {
        if(start < end)
        {
            uint mid = start + (end - start) / 2;
            merge(src, start, mid);
            merge(src, mid + 1, end);

            mergeHalf(src, start, mid, end);
        }

    }

private:
    struct MergePoint { uint start, end; };

    template<typename T>
    static void mergeHalf(T *src, uint beg, uint mid, uint end)
    {
        MergePoint half[2] = {
            {beg, mid},
            {mid + 1, end}
        };

        uint i = half[0].start;
        T *temp = new T[end + 2];

        std::cout << "Initialize\n";

        while((half[0].start <= half[0].end) && (half[1].start <= half[1].end))
        {
            if(src[half[0].start] <= src[half[1].start])
                temp[i] = src[half[0].start++];
            else
                temp[i] = src[half[1].start++];
            ++i;
        }

        std::cout << "Halfway through\n";

        while(half[0].start <= half[0].end)
        {
            temp[i] = src[half[0].start];
            half[0].start++;
            i++;
        }

        while(half[1].start <= half[1].end)
        {
            temp[i] = src[half[1].start];
            half[1].start++;
            i++;
        }

        for(i = beg; i <= end; ++i)
            src[i] = temp[i];

        delete [] temp;
    }

public:
    template<typename T>
    static void bucket(T *src, uint start, uint end)
    {
    }

};

#endif /* SORT_H */

