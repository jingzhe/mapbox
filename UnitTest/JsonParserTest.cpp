//
// Created by Jingzhe Yu on 9.5.2024.
//

#include <gtest/gtest.h>

TEST(JsonParserTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
    EXPECT_EQ(7 * 6, 42);
}