/**
Author: Kevin Morris
A queue test for queue.hpp
Copyright (C) 2015 Kevin Morris
**/
#include "queue.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Queue<int> q;

    q.enqueue(3634);
    q.enqueue(1039);

    cout << q.peekFront() << endl;
    q.dequeue();

    cout << q.peekFront() << endl;
    q.dequeue();

    return 0;
}

