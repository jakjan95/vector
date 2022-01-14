#include "gtest/gtest.h"
#include <cstddef>
#include <deque>
#include <memory>

#include "allocator.hpp"

constexpr int baseTestValue = 42;

class ClassToTest {
public:
    ClassToTest() = default;

    ClassToTest(int testValue)
        : testValue_ { testValue + counter_++ }
    {
    }

    ~ClassToTest()
    {
        counter_--;
    };

    int getTestValue() const { return testValue_; }
    int getCounter() const { return counter_; }

private:
    inline static int counter_ { 0 };
    int testValue_;
};

TEST(Allocator, AllocatorShouldAllocateMemoryToInitializeItUsingConstruct)
{
    constexpr std::size_t numOfElems = 4;
    constexpr int counterBase = 1;
    constexpr int expectedTotalForAllocatedSpace = 174;
    my_alloc::allocator<ClassToTest> allocator;

    ClassToTest* allocatedSpace = allocator.allocate(numOfElems);

    //Checking state of elements after space allocation
    int totalForAllocatedSpace = 0;
    for (std::size_t i = 0; i != numOfElems; ++i) {
        totalForAllocatedSpace += allocatedSpace[i].getTestValue();
        EXPECT_NE(allocatedSpace[i].getCounter(), counterBase + i);
    }
    EXPECT_NE(totalForAllocatedSpace, expectedTotalForAllocatedSpace);

    for (std::size_t i = 0; i != numOfElems; ++i) {
        std::construct_at(&allocatedSpace[i], baseTestValue);
        EXPECT_EQ(allocatedSpace[i].getCounter(), counterBase + i);
    }

    //Checking state of elements after construction
    totalForAllocatedSpace = 0;
    for (std::size_t i = 0; i != numOfElems; ++i) {
        totalForAllocatedSpace += allocatedSpace[i].getTestValue();
    }
    EXPECT_EQ(totalForAllocatedSpace, expectedTotalForAllocatedSpace);

    std::destroy_n(allocatedSpace, numOfElems);
    EXPECT_EQ(0, allocatedSpace[0].getCounter());
    allocator.deallocate(allocatedSpace, numOfElems);
}
