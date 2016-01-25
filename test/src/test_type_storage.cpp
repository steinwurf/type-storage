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

TEST(TestTypeStorage, get_type)
{
    std::tuple<uint8_t, uint16_t, uint32_t, uint64_t> tup;

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
