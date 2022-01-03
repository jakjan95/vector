#include "gtest/gtest.h"
#include <cstddef>
#include <string>

#include "vector.hpp"

constexpr std::size_t vectorSize = 3;
constexpr int defaultValue = 0;
constexpr std::size_t defaultContainerCapacity = 8;
constexpr int newValue = 5;
constexpr std::size_t vectorCapacity = 6;
constexpr int valueToInsert = 42;
const std::string stringValue = "string";

class VectorTest : public ::testing::Test {
protected:
    template <typename T>
    my_vec::vector<T> makeEmptyVector()
    {
        return my_vec::vector<T> {};
    }

    template <typename T>
    my_vec::vector<T> makeVectorWithSameSizeAndCapacity(std::size_t size, T value = {})
    {
        return my_vec::vector<T>(size, value);
    }

    template <typename T>
    my_vec::vector<T> makeVectorWithSizeAndCapacity(std::size_t size, std::size_t capacity, T value = {})
    {
        auto vec = my_vec::vector<T>(size, value);
        vec.reserve(capacity);
        return vec;
    }
};

TEST(VectorConstructor, DefaultConstructorShouldCreateEmptyVector)
{
    my_vec::vector<int> vec;

    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorConstructor, ConstructorShouldConstructVectorWithGivenCountCopiesOfElementsWithDefaultValue)
{
    my_vec::vector<int> vec(vectorSize);

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
}

TEST_F(VectorTest, SquareBracketOperatorShouldReturnReferenceToElementAtSpecificPositon)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    EXPECT_EQ(vec[0], defaultValue);

    vec[0] = newValue;

    EXPECT_EQ(vec[0], newValue);
}

TEST(VectorConstructor, ConstructorShouldConstructVectorWithGivenCountCopiesOfElementsWithGivenValue)
{
    constexpr int givenValue = 1;

    my_vec::vector<int> vec(vectorSize, givenValue);

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], givenValue);
    }
}

TEST_F(VectorTest, ReserveShouldIncreaseVectorCapacity)
{
    constexpr std::size_t newVectorCapacity = 6;
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
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

TEST_F(VectorTest, ResizeShouldResizesCointainerToContainCountElements)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;

    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity);

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

TEST_F(VectorTest, ResizeOfContainerWithValueHigherThanCapacityShouldIncreaseCapacityOfContainer)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;

    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
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

TEST_F(VectorTest, ResizeOfContainerWithGivenValueShouldSetGivenValueForNewElements)
{
    constexpr std::size_t vectorSize = 2;
    constexpr std::size_t newVectorSize = 4;

    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity);
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

TEST_F(VectorTest, BeginShouldReturnIteratorToFirstElementOfContainer)
{
    constexpr int firstValue = 10;

    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    vec[0] = firstValue;

    EXPECT_EQ(vec[0], *vec.begin());
}

TEST_F(VectorTest, ReverseBeginShouldReturnIteratorToFirstElementOfReversedVector)
{
    constexpr int lastValue = 10;
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    const auto lastElementIndex = vec.size() - 1;
    vec[lastElementIndex] = lastValue;

    EXPECT_EQ(vec[lastElementIndex], *vec.rbegin());
}

TEST_F(VectorTest, EndShouldReturnIteratorToElementFollowingLastElementOfContainer)
{
    constexpr int lastValue = 10;
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    constexpr auto lastIndexOfVector = vectorSize - 1;
    vec[lastIndexOfVector] = lastValue;

    auto lastElementOfVector = std::prev(vec.end());

    EXPECT_EQ(vec[lastIndexOfVector], *lastElementOfVector);
}

TEST_F(VectorTest, ReverseEndShouldReturnIteratorToElementFollowingLastElementOfReversedContainer)
{
    constexpr int firstValue = 10;
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    vec[0] = firstValue;

    auto firstElementOfVector = std::prev(vec.rend());

    EXPECT_EQ(vec[0], *firstElementOfVector);
}

TEST_F(VectorTest, EmptyShouldReturnTrueWhenContainerHasNoElements)
{
    auto vec = makeEmptyVector<int>();
    EXPECT_TRUE(vec.empty());
}

TEST_F(VectorTest, EmptyShouldReturnFalseWhenContainerHasElements)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    EXPECT_FALSE(vec.empty());
}

TEST_F(VectorTest, PushBackShouldAddElementAtEndOfContainerAndIncrementSizeOfContainer)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);

    const auto incrementedVectorSize = vec.size() + 1;
    vec.push_back(newValue);

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST_F(VectorTest, PushBackOnEmptyContainerShouldReserveSpaceAndAddElementAtEndOfContainer)
{
    auto vec = makeEmptyVector<int>();
    EXPECT_TRUE(vec.empty());

    const auto incrementedVectorSize = vec.size() + 1;
    vec.push_back(newValue);

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), defaultContainerCapacity);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST_F(VectorTest, PushBackShouldAddElementAtEndOfContainerWhenSizeIsEqualToCapacityItShouldIncreaseSizeAndCapacityOfContainer)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);

    const auto incrementedVectorSize = vec.size() + 1;
    vec.push_back(newValue);

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), 2 * vectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST_F(VectorTest, PushBackShouldMoveElementAtEndOfContainer)
{
    int valToMove = 2;
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);

    const auto incrementedVectorSize = vec.size() + 1;
    vec.push_back(std::move(valToMove));

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(valToMove, *lastElementOfVector);
}

TEST_F(VectorTest, CopyConstructorShouldCreateNewVectorByCopyingGiven)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);

    my_vec::vector<int> vec2(vec);

    EXPECT_EQ(vec.size(), vec2.size());
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], vec2[i]);
    }
}

TEST_F(VectorTest, CopyAssignmentShouldCopyGivenVectorToVector)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);
    my_vec::vector<int> vec2;

    vec2 = vec;

    EXPECT_EQ(vec.size(), vec2.size());
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(vec[i], vec2[i]);
    }
}

TEST_F(VectorTest, MoveConstructorShouldConstructVectorByMovingContentOfGivenVector)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);

    my_vec::vector<int> vec2(std::move(vec));

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec2.size(), vectorSize);
    EXPECT_EQ(vec2.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(newValue, vec2[i]);
    }
}

TEST_F(VectorTest, MoveAssignmentShouldMoveDataFromGivenVector)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);

    my_vec::vector<int> vec2;
    vec2 = std::move(vec);

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec2.size(), vectorSize);
    EXPECT_EQ(vec2.capacity(), vectorCapacity);
    for (std::size_t i = 0; i < vectorSize; ++i) {
        EXPECT_EQ(newValue, vec2[i]);
    }
}

TEST(VectorConstructor, InitializerListConstructorShouldConstructVectorByUsingContentOfGivenInitializerList)
{
    auto initializerLst = { 1, 2, 3 };
    my_vec::vector<int> vec(initializerLst);

    EXPECT_EQ(vec.size(), initializerLst.size());
    EXPECT_EQ(vec.capacity(), initializerLst.size());

    std::size_t index = 0;
    for (const auto el : initializerLst) {
        EXPECT_EQ(vec[index++], el);
    }
}

TEST_F(VectorTest, InitializerListAssignmentShouldCopyContentOfGivenInitializerListToVector)
{
    auto initializerLst = { 1, 2, 3 };
    auto vec = makeEmptyVector<int>();
    EXPECT_TRUE(vec.empty());

    vec = initializerLst;

    EXPECT_EQ(vec.size(), initializerLst.size());
    EXPECT_EQ(vec.capacity(), initializerLst.size());

    std::size_t index = 0;
    for (const auto el : initializerLst) {
        EXPECT_EQ(vec[index++], el);
    }
}

TEST_F(VectorTest, ShrinkToFitShouldRemoveUnusedSpace)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);
}

TEST_F(VectorTest, FrontShouldReturnReferenceToFirstElementInContainer)
{
    constexpr std::size_t firstElementIndex = 0;
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);

    vec.front() = newValue;

    EXPECT_EQ(vec[firstElementIndex], newValue);
    EXPECT_EQ(vec[firstElementIndex], vec.front());
    EXPECT_EQ(*vec.begin(), vec.front());
}

TEST_F(VectorTest, BackShouldReturnReferenceToLastElementInContainer)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    constexpr std::size_t lastElementIndex = vectorSize - 1;

    vec.back() = newValue;

    EXPECT_EQ(vec[lastElementIndex], newValue);
    EXPECT_EQ(vec[lastElementIndex], vec.back());
    EXPECT_EQ(*std::prev(vec.end()), vec.back());
}

TEST_F(VectorTest, AtShouldReturnReferenceToElementAtSpecificPositon)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    EXPECT_EQ(vec.at(0), defaultValue);

    vec.at(0) = newValue;

    EXPECT_EQ(vec.at(0), newValue);
}

TEST_F(VectorTest, AtShouldThrowExceptionWhenPositionIsNotWithinRangeOfContainer)
{
    constexpr std::size_t invalidPosition = 10;

    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);

    EXPECT_THROW(vec.at(invalidPosition), std::out_of_range);
}

TEST_F(VectorTest, DataShouldReturnsPointerToUnderlyingArrayInsideVector)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize, newValue);

    auto arrayFromVector = vec.data();
    for (std::size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(arrayFromVector[i], vec[i]);
    }
}

TEST_F(VectorTest, ClearShouldErasesAllElementsFromVector)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorCapacity);

    vec.clear();

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.capacity(), vectorCapacity);
}

TEST_F(VectorTest, InsertShouldInsertGivenValueBeforeBeginAndEndPosition)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);

    auto vectorSizeAfterInsertion = vec.size() + 1;
    vec.insert(vec.begin(), valueToInsert);

    EXPECT_EQ(*vec.begin(), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);

    vec.insert(vec.end(), valueToInsert);

    vectorSizeAfterInsertion++;
    EXPECT_EQ(*std::prev(vec.end()), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST_F(VectorTest, InsertShouldInsertGivenValueBeforeMiddlePosition)
{
    auto vec = makeVectorWithSizeAndCapacity<int>(vectorSize, vectorCapacity, newValue);
    auto middleIterator = vec.begin() + vectorSize / 2;

    const auto vectorSizeAfterInsertion = vec.size() + 1;
    middleIterator = vec.insert(middleIterator, valueToInsert);

    EXPECT_EQ(*middleIterator, valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST_F(VectorTest, InsertShouldInsertGivenValueAndIncreaseCapacity)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize, newValue);

    const auto vectorSizeAfterInsertion = vec.size() + 1;
    const auto capacityOfVectorAfterInsertion = vec.capacity() * 2;
    vec.insert(vec.end(), valueToInsert);

    EXPECT_EQ(*std::prev(vec.end()), valueToInsert);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
    EXPECT_EQ(vec.capacity(), capacityOfVectorAfterInsertion);
}

TEST_F(VectorTest, InsertOnEmptyContainerShouldReserveSpaceAndInsertGivenValue)
{
    auto vec = makeEmptyVector<int>();
    EXPECT_TRUE(vec.empty());

    const auto incrementedVectorSize = vec.size() + 1;
    vec.insert(vec.begin(), newValue);

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), defaultContainerCapacity);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(newValue, *lastElementOfVector);
}

TEST_F(VectorTest, EmplaceBackShouldConstructElementAtTheEndOfContainerAndIncreaseSizeOfContainer)
{
    auto vec = makeVectorWithSizeAndCapacity<std::string>(vectorSize, vectorCapacity);
    EXPECT_EQ(vec.size(), vectorSize);

    const auto vectorSizeAfterEmplaceBack = vec.size() + 1;
    vec.emplace_back(stringValue);

    EXPECT_EQ(vec.size(), vectorSizeAfterEmplaceBack);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(stringValue, *lastElementOfVector);
}

TEST_F(VectorTest, EmplaceBackShouldConstructElementAtTheEndOfContainerAndIncreaseSizeAndOfContainer)
{
    auto vec = makeVectorWithSameSizeAndCapacity<std::string>(vectorSize);
    EXPECT_EQ(vec.size(), vectorSize);
    EXPECT_EQ(vec.capacity(), vectorSize);

    const auto vectorSizeAfterEmplaceBack = vec.size() + 1;
    const auto capacityAfterEmplaceBack = 2 * vec.capacity();
    vec.emplace_back(stringValue);

    EXPECT_EQ(vec.size(), vectorSizeAfterEmplaceBack);
    EXPECT_EQ(vec.capacity(), capacityAfterEmplaceBack);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(stringValue, *lastElementOfVector);
}

TEST_F(VectorTest, EmplaceBackOnEmptyContainerShouldReserveSpaceAndAddElementAtEndOfContainer)
{
    auto vec = makeEmptyVector<std::string>();
    EXPECT_TRUE(vec.empty());

    const auto incrementedVectorSize = vec.size() + 1;
    vec.emplace_back(stringValue);

    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), defaultContainerCapacity);
    EXPECT_EQ(stringValue, *lastElementOfVector);
}

TEST_F(VectorTest, PopBackShouldRemoveLastElementOfContainerAndDecreaseSize)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize, newValue);
    EXPECT_EQ(vec.size(), vectorSize);

    const auto vectorSizeAfterPopBack = vec.size() - 1;
    vec.pop_back();

    EXPECT_EQ(vec.size(), vectorSizeAfterPopBack);
}

TEST_F(VectorTest, EraseShouldErasesFirstElementsFromTheContainer)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    vec.front() = newValue;

    const auto vectorSizeAfterErase = vec.size() - 1;
    auto it = vec.erase(vec.begin());

    EXPECT_EQ(vec.size(), vectorSizeAfterErase);
    EXPECT_NE(vec.front(), newValue);
    EXPECT_EQ(it, vec.begin());
}

TEST_F(VectorTest, EraseShouldErasesLastElementsFromTheContainer)
{
    auto vec = makeVectorWithSameSizeAndCapacity<int>(vectorSize);
    vec.back() = newValue;
    auto lastElement = vec.end() - 1;

    const auto vectorSizeAfterErase = vec.size() - 1;
    auto it = vec.erase(lastElement);

    EXPECT_EQ(vec.size(), vectorSizeAfterErase);
    EXPECT_NE(vec.back(), newValue);
    EXPECT_EQ(it, vec.end());
}

TEST_F(VectorTest, EmplaceShouldInsertGivenValueBeforeBeginAndEndPosition)
{
    auto vec = makeVectorWithSizeAndCapacity<std::string>(vectorSize, vectorCapacity);

    auto vectorSizeAfterInsertion = vec.size() + 1;
    vec.emplace(vec.begin(), stringValue);

    EXPECT_EQ(*vec.begin(), stringValue);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);

    vectorSizeAfterInsertion++;
    vec.emplace(vec.end(), stringValue);

    EXPECT_EQ(*std::prev(vec.end()), stringValue);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST_F(VectorTest, EmplaceShouldInsertGivenValueBeforeMiddlePosition)
{
    auto vec = makeVectorWithSizeAndCapacity<std::string>(vectorSize, vectorCapacity);
    auto middleIterator = vec.begin() + vectorSize / 2;

    const auto vectorSizeAfterInsertion = vec.size() + 1;
    middleIterator = vec.emplace(middleIterator, stringValue);

    EXPECT_EQ(*middleIterator, stringValue);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
}

TEST_F(VectorTest, EmplaceShouldInsertGivenValueAndIncreaseCapacity)
{
    auto vec = makeVectorWithSameSizeAndCapacity<std::string>(vectorSize);

    const auto vectorSizeAfterInsertion = vec.size() + 1;
    const auto capacityOfVectorAfterInsertion = vec.capacity() * 2;
    vec.emplace(vec.end(), stringValue);

    EXPECT_EQ(*std::prev(vec.end()), stringValue);
    EXPECT_EQ(vec.size(), vectorSizeAfterInsertion);
    EXPECT_EQ(vec.capacity(), capacityOfVectorAfterInsertion);
}

TEST_F(VectorTest, EmplaceOnEmptyContainerShouldReserveSpaceAndInsertGivenValue)
{
    auto vec = makeEmptyVector<std::string>();
    EXPECT_TRUE(vec.empty());

    const auto incrementedVectorSize = vec.size() + 1;
    vec.emplace(vec.begin(), stringValue);

    EXPECT_EQ(vec.size(), incrementedVectorSize);
    EXPECT_EQ(vec.capacity(), defaultContainerCapacity);
    auto lastElementOfVector = std::prev(vec.end());
    EXPECT_EQ(stringValue, *lastElementOfVector);
}

TEST_F(VectorTest, SwapShouldExchangeContentBetweenContainers)
{
    constexpr int valueInFirstVector = 99;
    constexpr std::size_t firstVectorSize = 3;
    constexpr std::size_t firstVectorCapacity = 5;
    auto firstVector = makeVectorWithSizeAndCapacity<int>(firstVectorSize, firstVectorCapacity, valueInFirstVector);

    constexpr int valueInSecondVector = 66;
    constexpr std::size_t secondVectorSize = 6;
    constexpr std::size_t secondVectorCapacity = 8;
    auto secondVector = makeVectorWithSizeAndCapacity<int>(secondVectorSize, secondVectorCapacity, valueInSecondVector);

    firstVector.swap(secondVector);

    EXPECT_EQ(firstVector.size(), secondVectorSize);
    EXPECT_EQ(firstVector.capacity(), secondVectorCapacity);

    EXPECT_EQ(secondVector.size(), firstVectorSize);
    EXPECT_EQ(secondVector.capacity(), firstVectorCapacity);

    for (std::size_t i = 0; i < firstVector.size(); ++i) {
        EXPECT_EQ(firstVector[i], valueInSecondVector);
    }

    for (std::size_t i = 0; i < secondVector.size(); ++i) {
        EXPECT_EQ(secondVector[i], valueInFirstVector);
    }
}
