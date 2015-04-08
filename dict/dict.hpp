/**
Author: Kevin Morris
File: dict.hpp
License: GPL2
Implementations of hash table descriptions from MIT OCW 6.006
Copyright (C) 2015 Kevin Morris
**/
#ifndef DICT_HPP
#define DICT_HPP

#include <string>
#include <iostream>
#include <stdexcept>

namespace nix
{
    using uint = unsigned int;
    using ulong = unsigned long;
    using uchar = unsigned char;
    using sz_t = std::size_t;

    template<typename U, typename V, typename T>
    V double_cast(T v)
    {
        return static_cast<V>(static_cast<U>(v));
    }

    template<typename T>
    struct hash;

    template<>
    struct hash<sz_t>
    {
        sz_t operator()(sz_t n)
        {
            return n;
        }
    };

    template<>
    struct hash<int>
    {
        sz_t operator()(int n)
        {
            return static_cast<sz_t>(n);
        }
    };

    template<>
    struct hash<char>
    {
        sz_t operator()(char c)
        {
            return double_cast<uchar, sz_t>(c);
        }
    };

    template<>
    struct hash<std::string>
    {
        sz_t operator()(std::string s)
        {
            hash<char> hash;
            sz_t var {0};

            for(const char c : s)
            {
                sz_t h = hash(c);
                var = ( (var << (sizeof(char) * 8)) | h );
            }

            return var;
        }
    };

    template<typename Key, typename Value>
    class dict
    {
    private:
        struct item
        {
            Key key;
            Value value;
            bool set {false};
            bool used {false};
        };

        nix::hash<Key> hash;

        sz_t _m {2}; // _m = size of table, start at 2
        sz_t _n {0}; // _n = amount of keys used in table

        item *data {nullptr}; // item pair array

    public:

        dict()
        {
            // Allocate initial table of size _m
            data = new item[_m];
        }

        ~dict()
        {
            // Free data storage
            delete [] data;
        }

        item& insert(const Key& key, const Value& value)
        {
            return data[0];
        }

        bool remove(const Key& key)
        {
            auto k = trial(key, [&](sz_t k) {
                return data[k].used && data[k].key != key;
            });

            if(!data[k].set)
                return false;

            return !(data[k].set = false);
        }

        const Value& operator[](const Key& key) const
        {
            auto k = trial(key, [&](sz_t k) {
                return data[k].used && data[k].key != key;
            });

            if(!data[k].set || data[k].key != key)
                throw std::domain_error("Key Error");

            return data[k].value;
        }

        Value& operator[](const Key& key)
        {
            if(_n == _m)
                rehash(_m * 2);

            auto k = trial(key, [&](sz_t k) {
                return data[k].used && data[k].key != key;
            });

            if(!data[k].set)
            {
                data[k].key = key;
                data[k].set = data[k].used = true;
                ++_n;
            }

            return data[k].value;
        }

    private:

        sz_t thash(const Key& key, sz_t step)
        {
            auto k = hash(key) + step;
            return k;
        }

        /* ContPred cp = Contiuation Predicate */
        template<typename ContPred>
        sz_t trial(const Key& key, ContPred cp, sz_t t = 1)
        {
            auto k = thash(key, t) % _m;
            return cp(k) ? trial(key, cp, t + 1) : k;
        }

        void rehash(sz_t m)
        {
            _m = m;
            item *new_array = new item[_m];
            for(sz_t i = 0; i < m; ++i)
            {
                if(!data[i].set)
                    continue;

                const auto& key = data[i].key;
                auto k = trial(key, [&](sz_t k) {
                    return new_array[k].set && new_array[k].key != key;
                });

                new_array[k].key = std::move(data[i].key);
                new_array[k].value = std::move(data[i].value);
                new_array[k].set = true;

            }
            delete [] data;
            data = new_array;
        }

    };

};

#endif



