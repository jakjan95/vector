#include "gtest/gtest.h"

#include "vector.hpp"

TEST(Vector, DefaultConstructorShouldCreateEmptyVector)
{
    my_vec::vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}
