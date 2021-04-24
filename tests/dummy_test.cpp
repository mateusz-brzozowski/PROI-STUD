#include <gtest/gtest.h>

TEST(example, ok) {
    EXPECT_EQ(1, 1);
}

TEST(example, fail) {
    EXPECT_EQ(0, 1);
}