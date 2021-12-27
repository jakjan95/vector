#include "gtest/gtest.h"
#include <cstddef>

#include "vector.hpp"

constexpr int defaultValue = 0;
constexpr int newValue = 5;
constexpr std::size_t vectorCapacity = 6;

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
    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec[0], defaultValue);
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

TEST(Vector, ReserveShouldIncreaseVectorCapacity)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorCapacity = 6;

    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }

    vec.reserve(newVectorCapacity);

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), newVectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }
}

TEST(Vector, ResizeShouldResizesCointainerToContainCountElements)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;
    
    my_vec::vector<int> vec(vectorSize);
    vec.reserve(vectorCapacity);

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }

    vec.resize(newVectorSize);

    EXPECT_EQ(vec.size(), newVectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < newVectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }
}

TEST(Vector, ResizeOfContainerWithValueHigherThanCapacityShouldIncreaseCapacityOfContainer)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;

    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }

    vec.resize(newVectorSize);

    EXPECT_EQ(vec.size(), newVectorSize);
    EXPECT_EQ(vec.capacity(), newVectorSize);
    for (std::size_t i = 0; i < newVectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }
}

TEST(Vector, ResizeOfContainerWithGivenValueShouldSetGivenValueForNewElements)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;

    my_vec::vector<int> vec(vectorSize);
    vec.reserve(vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);

    vec.resize(newVectorSize, newValue);

    EXPECT_EQ(vec.size(), newVectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], defaultValue);
    }

    for (std::size_t i = vectorSize; i < newVectorSize; ++i) {
        EXPECT_EQ(vec[i], newValue);
    }
}
