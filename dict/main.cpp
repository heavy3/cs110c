#include "dict.hpp"
#include <functional>
#include <iostream>
using namespace std;
using namespace nix;

uint hash_string(string s)
{
    uint h {0};

    return h;
}

void hash_test()
{
    nix::hash<std::string> shash;
    nix::hash<char> chash;

    cout << "Hello = " << shash("Hello") << endl;
    cout << "H = " << chash('H') << endl;
}

void dict_test()
{
    dict<std::string, int> dict;
    string k("Kevin"), c("Carl");

    dict[k] = 6;
    cout << dict[k] << endl;
    
    dict[c] = 7;
    cout << dict[c] << endl;

    cout << dict[k] << endl;

}

int main()
{
    cout << "Hash Test\n";
    hash_test();

    cout << "\nDict Test\n";
    dict_test();
    return 0;
}


