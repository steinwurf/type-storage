// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF STEINWURF
// The copyright notice above does not evidence any
// actual or intended publication of such source code.

#include <type-storage/type_queue.hpp>

#include <vector>

#include <gtest/gtest.h>


TEST(TestTypeQueue, initialize)
{
    type_storage::type_queue<uint8_t, uint16_t, uint32_t, uint64_t> queue;
}
