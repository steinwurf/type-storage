// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include <type-storage/wrapped_type_storage.hpp>

// Container to keep track of types int32_t, uint32_t and float types,
// all stored in std::vector type containers
template<typename T>
using type_wrapper = std::vector<T>;

type_storage::wrapped_type_storage<type_wrapper,
    bool, int32_t, uint32_t, float> log_storage;

std::mt19937 engine(0);
std::bernoulli_distribution randbool(0.5);
std::uniform_int_distribution<int32_t> randint(-100, 100);
std::uniform_int_distribution<uint32_t> randuint(0, 100);
std::uniform_real_distribution<float> randfloat(-1, 1);


// Provide random generators for each supported type
// It is possible that this may be done with just one function, instead of
// template specializations
template<typename T> T generate_random()
{
    return T();
}
template<> bool generate_random<bool>() { return randbool(engine); }
template<> int32_t generate_random<int32_t>() { return randint(engine); }
template<> uint32_t generate_random<uint32_t>() { return randuint(engine); }
template<> float generate_random<float>() { return randfloat(engine); }


template<typename T>
void log_random()
{
    log_storage.get<T>().push_back(generate_random<T>());
}

// Log each type of random variable generated
template<typename T, typename U, typename... Types>
void log_random()
{
    log_random<T>();
    log_random<U, Types...>();
}

int main()
{
    // do several calls of each, then print the log_storage container
    for (uint32_t i = 0; i < 25; ++i)
    {
        // Order of template arguments does not matter, as long as all are
        // supported by the log_storage container. It can also be called with
        // just a subset of supported types, e.g. float and bool.
        log_random<uint32_t, float, int32_t, bool>();
    }

    std::cout << "bools: ";

    for (const auto& i : log_storage.get<bool>())
        std::cout << i << ' ';
    std::cout << std::endl << "uint32_ts: \t";

    for (const auto& i : log_storage.get<uint32_t>())
        std::cout << i << ' ';
    std::cout << std::endl << "int32_ts: \t";

    for (const auto& i : log_storage.get<int32_t>())
        std::cout << i << ' ';
    std::cout << std::endl << "floats: \t";

    for (const auto& i : log_storage.get<float>())
        std::cout << i << ' ';
    std::cout << std::endl;
}
