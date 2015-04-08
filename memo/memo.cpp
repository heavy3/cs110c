#include <iostream>
#include <unordered_map>
using namespace std;

template<typename T, typename U>
using umap = unordered_map<T, U>;
using ullong = unsigned long long;

ullong fibo(ullong n)
{
    umap<ullong, ullong> table;
    ullong f;
    for(ullong k = 1; k < n + 1; ++k)
    {
        f = k <= 2 ? f = 1 : table[k - 1] + table[k - 2];
        table[k] = f;
    }

    return table[n];
}

int main()
{
    cout << fibo(10000) << endl;
    return 0;
}

