// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <type-storage/type_storage.hpp>

#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

TEST(TestTypeStorage, detail)
{
    const size_t idx = type_storage::detail::find_index<std::is_same, uint32_t,
                       char, uint8_t, uint16_t, uint32_t, uint64_t,
                       std::string, float>::value;
    EXPECT_EQ(3u, idx);
}

TEST(TestTypeStorage, get_type)
{
    std::tuple<uint8_t, uint32_t, uint16_t, uint64_t> tup;

    // Verify that we get the right size out by using sizeof function
    EXPECT_EQ(1U, sizeof(type_storage::get<uint8_t>(tup)));
    EXPECT_EQ(2U, sizeof(type_storage::get<uint16_t>(tup)));

    EXPECT_EQ(4U, sizeof(type_storage::get<uint32_t>(tup)));
    EXPECT_EQ(8U, sizeof(type_storage::get<uint64_t>(tup)));
}

TEST(TestTypeStorage, set_get_type)
{
    std::tuple<uint8_t, uint16_t, uint32_t, uint64_t> tup;

    // Verify that we assign the correct value to the correct type by using
    // numeric limits of each type

    {
        uint64_t value = std::numeric_limits<uint8_t>::max();
        type_storage::get<uint8_t>(tup) = value;
        EXPECT_EQ(value, type_storage::get<uint8_t>(tup));
    }

    {
        uint64_t value = std::numeric_limits<uint16_t>::max();
        type_storage::get<uint16_t>(tup) = value;
        EXPECT_EQ(value, type_storage::get<uint16_t>(tup));
    }

    {
        uint64_t value = std::numeric_limits<uint32_t>::max();
        type_storage::get<uint32_t>(tup) = value;
        EXPECT_EQ(value, type_storage::get<uint32_t>(tup));
    }

    {
        uint64_t value = std::numeric_limits<uint64_t>::max();
        type_storage::get<uint64_t>(tup) = value;
        EXPECT_EQ(value, type_storage::get<uint64_t>(tup));
    }
}

namespace
{
struct base
{
    char m_c = 'b';
};

struct special_a : public base
{ };

struct special_b : public base
{ };
}

TEST(TestTypeStorage, baget_basetype)
{
    std::tuple<
        std::stringstream,
        std::string, std::vector<char>, std::mutex, uint64_t,
        special_a, special_b> tup;

    // Verify that we can get an object out based on the base type using
    // the baget function:
    // Here we get the stringstream object using the istream base
    {
        auto& os = type_storage::baget<std::ostream>(tup);
        os.put('a');
        os.put('b');
        os.put('c');
    }
    // Then we fetch the same object out again, using the istream base
    {
        auto& is = type_storage::baget<std::istream>(tup);
        EXPECT_EQ('a', is.get());
        EXPECT_EQ('b', is.get());
        EXPECT_EQ('c', is.get());
    }

    // We can get the special_a and special_b types from tup using get(),
    // but baget() will not compile as they share the same base.
    auto& a = type_storage::get<special_a>(tup); // OK
    auto& b = type_storage::get<special_b>(tup); // OK
    // auto& ba = type_storage::baget<base>(tup); // will not compile

    EXPECT_EQ(a.m_c, b.m_c);
}

TEST(TestTypeStorage, get_baget_const)
{
    const std::tuple<
        std::stringstream,
        std::string, std::vector<char>, std::mutex, uint64_t,
        special_a> tup;

    const auto& ba = type_storage::baget<base>(tup);
    (void) ba;

    const auto& sa = type_storage::get<special_a>(tup);
    (void) sa;

    // Ignores const statement when searching
    const auto& bac = type_storage::baget<const base>(tup);
    (void) bac;

    const auto& sac = type_storage::get<const special_a>(tup);
    (void) sac;
}
