// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <cassert>
#include <typeinfo>
#include <iostream>

#include <type-storage/type_storage.hpp>

// Container to keep track of sums of type int32_t, uint32_t and float types
type_storage::type_storage<int32_t, uint32_t, float> sums;

// Function that adds to the sum of type 'T' in container 'sums'.
// Does not compile if T is not in types stored in 'sums'.
template<typename T>
void add(T t)
{
    sums.get<T>()+=t;
}

int main()
{
    // Create variables of different types to add with function 'add'
    int32_t a = -5;
    uint32_t b = 10U;
    float c = 3.14;

    // Add the values a couple of times.

    add(a);
    add(a);
    add(b);
    add(b);
    add(c);
    add(c);

    // The sums can now be tracked using a type, and thus only using one
    // variable (sums) to keep track of an arbitrary amount of sums.
    std::cout << "sums are: \n"
              << "int32_t:  \t" << sums.get<int32_t>() << "\n"
              << "uint32_t:  \t" << sums.get<uint32_t>() << "\n"
              << "float:  \t" << sums.get<float>()
              << std::endl;
}
