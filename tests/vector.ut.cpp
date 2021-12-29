#include "gtest/gtest.h"
#include <cstddef>

#include "vector.hpp"

constexpr int defaultValue = 0;
constexpr int newValue = 5;
constexpr std::size_t vectorCapacity = 6;
constexpr int valueToInsert = 42;

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

TEST(Vector, MoveConstructorShouldConstructVectorByMovingContentOfGivenVector)
{
    constexpr std::size_t vectorSize = 3;

    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    my_vec::vector<int> vec2(std::move(vec));

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec2.size(), vectorSize);
    EXPECT_EQ(vec2.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(newValue, vec2[i]);
    }
}

TEST(Vector, MoveAssignmentShouldMoveDataFromGivenVector)
{
    constexpr std::size_t vectorSize = 3;

    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    my_vec::vector<int> vec2;
    vec2 = std::move(vec);

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec2.size(), vectorSize);
    EXPECT_EQ(vec2.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(newValue, vec2[i]);
    }
}

TEST(Vector, ShrinkToFitShouldRemoveUnusedSpace)
{
    constexpr std::size_t vectorSize = 3;

    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
}

TEST(Vector, FrontShouldReturnReferenceToFirstElementInContainer)
{
    constexpr std::size_t vectorSize = 3;
    constexpr std::size_t firstElementIndex = 0;

    my_vec::vector<int> vec(vectorSize);
    vec[firstElementIndex] = newValue;
    EXPECT_EQ(vec[firstElementIndex], vec.front());
    EXPECT_EQ(*vec.begin(), vec.front());
}

TEST(Vector, BackShouldReturnReferenceToLastElementInContainer)
{
    constexpr std::size_t vectorSize = 3;
    constexpr std::size_t lastElementIndex = vectorSize - 1;

    my_vec::vector<int> vec(vectorSize);
    vec[lastElementIndex] = newValue;
    EXPECT_EQ(vec[lastElementIndex], vec.back());
    EXPECT_EQ(*std::prev(vec.end()), vec.back());
}

TEST(Vector, AtShouldReturnReferenceToElementAtSpecificPositon)
{
    constexpr std::size_t vectorSize = 1;
    my_vec::vector<int> vec(vectorSize);
    EXPECT_EQ(vec.at(0), defaultValue);
    vec.at(0) = newValue;
    EXPECT_EQ(vec.at(0), newValue);
}

TEST(Vector, AtShouldThrowExceptionWhenPositionIsNotWithinRangeOfContainer)
{
    constexpr std::size_t vectorSize = 1;
    constexpr std::size_t invalidPosition = 10;
    my_vec::vector<int> vec(vectorSize);
    EXPECT_THROW(vec.at(invalidPosition), std::out_of_range);
}

TEST(Vector, DataShouldReturnsPointerToUnderlyingArrayInsideVector)
{
    constexpr std::size_t vectorSize = 2;
    my_vec::vector<int> vec(vectorSize, newValue);
    auto arrayFromVector = vec.data();
    for (std::size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(arrayFromVector[i], vec[i]);
    }
}

TEST(Vector, ClearShouldErasesAllElementsFromVector)
{
    constexpr std::size_t vectorSize = 3;
    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);
    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.capacity(), vectorCapacity);
}

TEST(Vector, InsertShouldInsertGivenValueBeforeBeginAndEndPosition)
{
    constexpr std::size_t vectorSize = 3;
    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);

    vec.insert(vec.begin(), valueToInsert);
    auto vectorSizeAfterInsertion = vectorSize + 1;

    EXPECT_EQ(*vec.begin(), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);

    vec.insert(vec.end(), valueToInsert);
    vectorSizeAfterInsertion++;

    EXPECT_EQ(*std::prev(vec.end()), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST(Vector, InsertShouldInsertGivenValueBeforeMiddlePosition)
{
    constexpr std::size_t vectorSize = 3;
    my_vec::vector<int> vec(vectorSize, newValue);
    vec.reserve(vectorCapacity);
    auto middleIterator = vec.begin() + vectorSize / 2;

    middleIterator = vec.insert(middleIterator, valueToInsert);
    auto vectorSizeAfterInsertion = vectorSize + 1;

    EXPECT_EQ(*middleIterator, valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST(Vector, InsertShouldInsertGivenValueAndIncreaseCapacity)
{
    constexpr std::size_t vectorSize = 3;
    my_vec::vector<int> vec(vectorSize, newValue);

    auto capacityOfVectorAfterInsertion = vec.capacity() * 2;
    vec.insert(vec.end(), valueToInsert);
    auto vectorSizeAfterInsertion = vectorSize + 1;

    EXPECT_EQ(*std::prev(vec.end()), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
    EXPECT_EQ(vec.capacity(), capacityOfVectorAfterInsertion);
}
