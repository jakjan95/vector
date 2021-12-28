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

TEST(Vector, BeginShouldReturnIteratorToFirstElementOfContainer)
{
    constexpr std::size_t vectorSize = 2;
    constexpr int firstValue = 10;

    my_vec::vector<int> vec(vectorSize);
    vec[0] = firstValue;

    EXPECT_EQ(vec[0], *vec.begin());
}

TEST(Vector, EndShouldReturnIteratorToElementFollowingLastElementOfContainer)
{
    constexpr std::size_t vectorSize = 2;
    constexpr int lastValue = 10;

    my_vec::vector<int> vec(vectorSize);
    constexpr auto lastIndexOfVector = vectorSize - 1;
    vec[lastIndexOfVector] = lastValue;

    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(vec[lastIndexOfVector], *lastElementOfVector);
}

TEST(Vector, EmptyShouldReturnTrueWhenContainerHasNoElements)
{
    my_vec::vector<int> vec;
    EXPECT_TRUE(vec.empty());
}

TEST(Vector, EmptyShouldReturnFalseWhenContainerHasElements)
{
    constexpr std::size_t vectorSize = 2;
    my_vec::vector<int> vec(vectorSize);
    EXPECT_FALSE(vec.empty());
}

TEST(Vector, PushBackShouldAddElementAtEndOfContainerAndIncrementSizeOfContainer)
{
    constexpr std::size_t vectorSize = 2;

    my_vec::vector<int> vec(vectorSize);
    vec.reserve(vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);

    vec.push_back(newValue);
    
    constexpr std::size_t incrementedVectorSize = vectorSize + 1;
    EXPECT_EQ(vec.size(), incrementedVectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST(Vector, PushBackShouldAddElementAtEndOfContainerWhenSizeIsEqualToCapacityItShouldIncreaseSizeAndCapacityOfContainer)
{
    constexpr std::size_t vectorSize = 2;

    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);

    vec.push_back(newValue);

    constexpr std::size_t incrementedVectorSize = vectorSize + 1;
    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), 2 * vectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST(Vector, PushBackShouldMoveElementAtEndOfContainer)
{
    constexpr std::size_t vectorSize = 2;

    my_vec::vector<int> vec(vectorSize);
    vec.reserve(vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);

    int valToMove = 2;
    vec.push_back(std::move(valToMove));

    constexpr std::size_t incrementedVectorSize = vectorSize + 1;
    EXPECT_EQ(vec.size(), incrementedVectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(valToMove, *lastElementOfVector);
}

TEST(Vector, CopyConstructorShouldCreateNewVectorByCopyingGiven)
{
    constexpr std::size_t vectorSize = 3;

    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    my_vec::vector<int> vec2(vec);

    EXPECT_EQ(vec.size(), vec2.size());
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], vec2[i]);
    }
}

TEST(Vector, CopyAssignmentShouldCopyGivenVectorToVector)
{
    constexpr std::size_t vectorSize = 3;

    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    my_vec::vector<int> vec2;
    vec2 = vec;

    EXPECT_EQ(vec.size(), vec2.size());
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], vec2[i]);
    }
}
