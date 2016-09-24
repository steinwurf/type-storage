// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <type-storage/wrapped_type_storage.hpp>

#include <limits>
#include <memory>

#include <gtest/gtest.h>

namespace
{
template<typename T> struct size_wrap
{
    T value;
    const size_t size = sizeof(T);
};

template<typename T>
using type_counter = int32_t;

// Add default constructor to a "wrapper type"
template<typename T>
class shared_pointer : public std::shared_ptr<T>
{
public:
    shared_pointer() :
        std::shared_ptr<T>(std::make_shared<T>())
    { }
};
}


TEST(TestWrappedTypeStorage, initialize)
{
    type_storage::wrapped_type_storage<size_wrap,
        uint8_t, uint16_t, uint32_t, uint64_t> storage;
}

TEST(TestWrappedTypeStorage, get_type)
{
    type_storage::wrapped_type_storage<size_wrap,
        uint8_t, uint16_t, uint32_t, uint64_t> storage;

    EXPECT_EQ(1U, storage.get<uint8_t>().size);
    EXPECT_EQ(2U, storage.get<uint16_t>().size);
    EXPECT_EQ(4U, storage.get<uint32_t>().size);
    EXPECT_EQ(8U, storage.get<uint64_t>().size);
}


/// The Wrapped Type Storage can also be used to lookup a set of equal typed
/// objects based on a range of other types.
/// That is, the storage can associate a "list" of uints to a list a types.
TEST(TestWrappedTypeStorage, unrelated_type_lookup)
{
    type_storage::wrapped_type_storage<type_counter,
        uint8_t, uint16_t, uint32_t, uint64_t> counters;

    // object 'counters' is basically a list of uint32_t's that can be fetched
    // based on the associated type:
    counters.get<uint8_t>()--;
    counters.get<uint8_t>()--;
    counters.get<uint8_t>()--;

    counters.get<uint16_t>()--;
    counters.get<uint16_t>()--;

    counters.get<uint32_t>()--;

    counters.get<uint64_t>()--;
    counters.get<uint64_t>()--;
    counters.get<uint64_t>()--;
    counters.get<uint64_t>()--;

    EXPECT_EQ(-3, counters.get<uint8_t>());
    EXPECT_EQ(-2, counters.get<uint16_t>());
    EXPECT_EQ(-1, counters.get<uint32_t>());
    EXPECT_EQ(-4, counters.get<uint64_t>());

    /// Verify that the type return by get is int32_t:
    EXPECT_TRUE(bool(std::is_same<decltype(counters.get<uint8_t>()),
                     int32_t&>::value));
    EXPECT_TRUE(bool(std::is_same<decltype(counters.get<uint16_t>()),
                     int32_t&>::value));
    EXPECT_TRUE(bool(std::is_same<decltype(counters.get<uint32_t>()),
                     int32_t&>::value));
    EXPECT_TRUE(bool(std::is_same<decltype(counters.get<uint64_t>()),
                     int32_t&>::value));
}

/// Some wrapper types does not provide sufficient default construction,
/// e.g. does an std::shared_ptr<T> not provide a valid object,
/// and the default no-argument constructor can be overridden for convienience,
/// as in shared_pointer definition at the top of this file.
TEST(TestWrappedTypeStorage, add_default_construct)
{
    type_storage::wrapped_type_storage<shared_pointer,
        uint8_t, uint16_t, uint32_t> storage;

    EXPECT_TRUE(bool(storage.get<uint8_t>()));

    storage.get<uint8_t>().reset();

    EXPECT_FALSE(bool(storage.get<uint8_t>()));
}