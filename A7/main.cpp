/**
Author: Kevin Morris
File: main.cpp
License: GPL2
Main execution point for Assignment 7: CS110C
Copyright (C) 2015 Kevin Morris
**/
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Stack<char> stack;
    Queue<char> queue;

    if(argc < 2)
    {
        cout << "usage: " << argv[0] << " 'palindrome'\n";
        return 1;
    }

    for(const char e : string(argv[1]))
    {
        stack.push(e);
        if(!queue.enqueue(e))
        {
            cout << "Queue was full when trying to add an element\n";
            return 2;
        }
    }

    bool isPalindrome = true;
    while(!stack.empty())
    {
        if(stack.pop() != queue.dequeue())
        {
            isPalindrome = false;
            break;
        }
    }

    cout << argv[1] << (isPalindrome ? " is " : " is not ")
         << "a palindrome.\n";

    return 0;
}

