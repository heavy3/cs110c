#include "stack.hpp"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Stack<int> yolo;
    yolo.push(6);
    yolo.push(3);

    cout << "Peek: " << yolo.peek() << endl;

    auto value = yolo.pop();
    cout << value << endl << yolo.pop() << endl;
    return 0;
}

