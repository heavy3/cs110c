/* Author: Kevin Morris
 * License: GPL2
 * A set of sorting algorithms in different stages of O(complexity),
 * Assignment 4: CS110C
 * Copyright (C) 2015 Kevin Morris */
#ifndef SORT_H
#define SORT_H

#include <vector>

using uint = unsigned int;

/* Complexity class: A class used to keep track of sort
complexity with a memoized variable. All of these functions work
standalone with merge hidden for protection. */
class Complexity
{
public:
    static std::vector<uint> O; // O Complexity

    template<typename T>
    static void swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
        O.back()++; // +1 complexity for swap
    }

    // Insertion Sort
    // @pre beg <= end, beg && end are valid pointers to array indices
    // @post beg .. end sorted
    // @param beg => pointer to first element of array
    //        end => pointer to last element of array
    // This Insertion Sort iterates through pointers, has an O(n^2)
    // worst-case complexity, and O(n) best-case. It finds the minimum
    // value for i + 1 .. n and swaps it with i, for i .. n - 1.
    template<typename T>
    static void insertion(T *beg, T* const end)
    {
        O.emplace_back(0);
        uint& ops = O.back();

        T min {0}, *idx {beg};

        for(auto i = beg; i < end; ++i, idx = i)
        {
            ++ops;
            min = *i;
            for(auto j = i + 1; j <= end; ++j)
            {
                ++ops; // Increase comparison count
                if(*j < min)
                {
                    ++ops;
                    min = *j;
                    idx = j;
                }
            }
            ++ops;
            if(i != idx)
                swap(*i, *idx);
        }
    }

    // Merge Sort
    // @pre beg <= end, beg && end are valid pointers to array indices
    // @post beg .. end sorted
    // @param beg => pointer to first element of merge slice
    //        end => pointer to last element of merge slice
    // This function divides [beg .. end] into halves and sorts them
    // back into place. O(n log n) complexity, always.
    template<typename T>
    static void mergeSort(T* const beg, T* const end)
    {
        if(beg < end)
        {
            // Get middle pointer
            T* const mid = beg + (end - beg) / 2;

            // Recurse two splits of this half
            mergeSort(beg, mid);
            mergeSort(mid + 1, end);

            // Merge this half
            merge(beg, mid, end);
        }
    }

private:
    // @pre beg <= mid <= end and beg + end are valid
    // @post beg .. end range merged
    // @param beg => pointer to first element of merge slice
    //        mid => pointer to middle element of merge slice
    //        end => pointer to last element of merge slice
    // This function cuts a range beg <= mid <= end in half and merges
    // the two halves.
    template<typename T>
    static void merge(T *beg, T* const mid, T* const end)
    {
        O.emplace_back(0);
        auto& ops = O.back();

        // Create two vectors of pointers for the left and right halves
        std::vector<T> l(beg, mid + 1);
        std::vector<T> ri(mid + 1, end + 1);

        // Set n1 to n of left half
        int const n1 = mid - beg + 1;
        // Set n2 to n of right half
        int const n2 = end - mid;

        int i = 0, j = 0;

        // Loop [i .. n1] or [j .. n2]
        while(i < n1 && j < n2)
        {
            // if left half index is less than right half
            if(l[i] < ri[j])
                *beg++ = l[i++]; // Set current pointer to the value and inc
            else
                *beg++ = ri[j++]; // Otherwise, set it to right hand value
            ++ops;
        }

        // Finish off left side
        while(i < n1)
        {
            ++ops;
            *beg++ = l[i++];
        }

        // Finish off right side
        while(j < n2)
        {
            ++ops;
            *beg++ = ri[j++];
        }
    }

public:

    // Bucket Sort (Counting Sort?)
    // @pre beg <= end and beg && end are valid pointers to array indices
    //      Any data in the array must be in the range 1 .. 100 integer
    // @post [beg .. end] sorted
    // @param beg => valid pointer to an array index
    //        end => valid pointer to an array index
    // This sort function has great performance for small k, where k is the
    // maximum integer value stored in the array to be sorted. Counting Sort
    // has an overall complexity of O(n + k) where n is the size of the array
    // and k is the maximum integer value in the array. Counting sort creates
    // an array that can be used to index values and store counts from the
    // array, therefore, there is k allocation and use cost.
    template<typename T>
    static void bucket(T *beg, T* const end)
    {
        O.emplace_back(0);
        auto& ops = O.back();

        const int MAX_NUM = 100;
        T count[MAX_NUM + 1] = {0}; // Bucket to hold counts, init all to 0

        // Count instances
        for(auto i = beg; i <= end; ++i, ++ops)
            count[*i] += 1;

        // Redistribute counts
        for(int i = 1; i <= MAX_NUM; ++i)
        {
            for(int k = 0; k < count[i]; ++k)
            {
                ++ops;
                *beg++ = i;
            }
        }

    }

};

#endif /* SORT_H */

