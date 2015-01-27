/**
Author: Kevin Morris
File: recursive.cpp
Two recursive implementations of numerical and string backward printing
Copyright (C) 2014 Kevin Morris
**/
#include <iostream>
using namespace std;

void writeBackward(const string& s);
void writeBackward(int n);

int main(int argc, char *argv[])
{
    writeBackward("Hello");
    cout << endl;

    writeBackward(63935);
    cout << endl;
    return 0;
}

void writeBackward(const string& s)
{
    if(s.size() > 0)
    {
        writeBackward(s.substr(1));
        cout << s[0];
    }
}

void writeBackward(int n)
{
    cout << n % 10;

    if(n >= 10)
        writeBackward(n / 10);
}


