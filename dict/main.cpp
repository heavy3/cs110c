#include "dict.hpp"
#include <functional>
#include <iostream>
using namespace std;
using namespace nix;

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
    cout << "Kevin: " << dict[k] << endl;

    dict[c] = 11;
    cout << "Carl:  " << dict[c] << endl;
    cout << "Kevin: " << dict[k] << endl;

    dict["Haha"] = 63;
    cout << "Haha: " << dict["Haha"] << endl;
    cout << "Carl: " << dict[c] << endl;
    cout << "Kevin: " << dict[k] << endl;
}

int main()
{
    cout << "Hash Test\n";
    hash_test();

    cout << "\nDict Test\n";
    dict_test();
    return 0;
}


