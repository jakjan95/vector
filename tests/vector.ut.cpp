#include "gtest/gtest.h"
#include <cstddef>

#include "vector.hpp"

TEST(Vector, DefaultConstructorShouldCreateEmptyVector)
{
    my_vec::vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, ConstructorShouldConstructVectorWithGivenCountCopiesOfElementsWithDefaultValue)
{
    constexpr std::size_t vectorSize = 5;
    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
}
