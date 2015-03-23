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

                // Construct a binary string of the hash
                std::string bin;
                bin.reserve(255);
                for(sz_t i = 0, k = h; k / 2 != 0; k /= 2, ++i)
                    bin[i] = i % 2 ? '1' : '0';

                // Get that binary string's length for shifting over
                sz_t len = bin.length();

                var |= ~( (var << len) | h );
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
            sz_t trial = 1;
            auto k = trial_hash(key, trial) % _m;

            while(data[k].set)
                k = trial_hash(key, ++trial) % _m;

            data[k].value = value;
            data[k].set = true;

            return data[k];
        }

        const Value& operator[](const Key& key) const
        {
            sz_t trial = 1;

            auto k = trial_hash(key, trial) % _m;
            if(data[k].key == key)
            {
                return data[k].value;
            }
            else
            {
                while(data[k].set && data[k].key != key)
                    k = trial_hash(key, ++trial) % _m;
                if(!data[k].set)
                    throw std::domain_error("key does not exist");
            }

            return data[k].value;
        }

        Value& operator[](const Key& key)
        {
            sz_t trial = 1;

            auto k = trial_hash(key, trial) % _m;
            if(data[k].key == key)
            {
                if(!data[k].set)
                    data[k].set = ++_n;
                return data[k].value;
            }

            while(data[k].set && data[k].key != key)
                k = trial_hash(key, ++trial) % _m;

            if(!data[k].set)
                data[k].set = ++_n;

            return data[k].value;
        }

    private:

        sz_t trial_hash(const Key& key, sz_t step)
        {
            return hash(key) * step;
        }

        void rehash(sz_t m, sz_t n)
        {
        }

    };

};

#endif



