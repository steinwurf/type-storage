// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <type-storage/type_storage.hpp>

#include <limits>
#include <memory>

#include <gtest/gtest.h>


TEST(TestTypeStorage, initialize)
{
    type_storage::type_storage<uint8_t, uint16_t, uint32_t, uint64_t> storage;
}

TEST(TestTypeStorage, get_type)
{
    type_storage::type_storage<uint8_t, uint16_t, uint32_t, uint64_t> storage;

    // Verify that we get the right size out by using sizeof function
    EXPECT_EQ(1U, sizeof(storage.get<uint8_t>()));
    EXPECT_EQ(2U, sizeof(storage.get<uint16_t>()));
    EXPECT_EQ(4U, sizeof(storage.get<uint32_t>()));
    EXPECT_EQ(8U, sizeof(storage.get<uint64_t>()));
}

TEST(TestTypeStorage, set_get_type)
{
    type_storage::type_storage<uint8_t, uint16_t, uint32_t, uint64_t> storage;

    // Verify that we assign the correct value to the correct type by using
    // numeric limits of each type

    {
        uint64_t value = std::numeric_limits<uint8_t>::max();
        storage.get<uint8_t>() = value;
        EXPECT_EQ(value, storage.get<uint8_t>());
    }

    {
        uint64_t value = std::numeric_limits<uint16_t>::max();
        storage.get<uint16_t>() = value;
        EXPECT_EQ(value, storage.get<uint16_t>());
    }

    {
        uint64_t value = std::numeric_limits<uint32_t>::max();
        storage.get<uint32_t>() = value;
        EXPECT_EQ(value, storage.get<uint32_t>());
    }

    {
        uint64_t value = std::numeric_limits<uint64_t>::max();
        storage.get<uint64_t>() = value;
        EXPECT_EQ(value, storage.get<uint64_t>());
    }
}
