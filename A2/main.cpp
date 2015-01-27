/**
Author: Kevin Morris
File: list.hpp
A generic list implementation
Copyright (C) 2014 Kevin Morris
**/
#include "list.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    List<int> L;
    L += 63;
    L += 73;

    cout << L[0] << endl
         << L[1] << endl;


    return 0;
}



