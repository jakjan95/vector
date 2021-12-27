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

TEST(Vector, SquareBracketOperatorShouldReturnReferenceToElementAtSpecificPositon)
{
    constexpr std::size_t vectorSize = 1;
    constexpr int defaultValue = 0;
    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec[0], defaultValue);
    constexpr int newValue = 5;
    vec[0] = newValue;
    EXPECT_EQ(vec[0], newValue);
}

TEST(Vector, ConstructorShouldConstructVectorWithGivenCountCopiesOfElementsWithGivenValue)
{
    constexpr std::size_t vectorSize = 2;
    constexpr int givenValue = 1;

    my_vec::vector<int> vec(vectorSize, givenValue);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], givenValue);
    }
}
