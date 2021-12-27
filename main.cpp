#include <cstddef>
#include <iostream>

#include "vector.hpp"

int main()
{
    my_vec::vector<int> vec1;

    if (vec1.size() == 0 && vec1.capacity() == 0) {
        std::cout << "Vector created by default constructor should have size equal to 0\n";
        std::cout << "Vector created by default constructor should have capacity equal to 0\n";
    }

    std::size_t vec2Size = 5;
    my_vec::vector<int> vec2(vec2Size);
    std::cout << "my_vec::vector<int> vec2(5);\n";
    if (vec2.size() == vec2Size && vec2.capacity() == vec2Size) {
        std::cout << "Vector should have size equal to " << vec2Size << " \n";
        std::cout << "Vector should have capacity equal to " << vec2Size << " \n";
    }

    for (std::size_t i = 0; i < vec2Size; ++i) {
        if (vec2[i] == 0) {
            std::cout << "vec2[" << i << "] have default value\n";
        }
    }

    std::size_t vec2NewCapacity = 10;
    vec2.reserve(vec2NewCapacity);
    if (vec2.size() == vec2Size && vec2.capacity() == vec2NewCapacity) {
        std::cout << "Vector should have size equal to " << vec2Size << " \n";
        std::cout << "Vector should have capacity equal to " << vec2NewCapacity << " \n";
    }

    std::size_t vec2NewSize = 8;
    vec2.resize(vec2NewSize);
    if (vec2.size() == vec2NewSize && vec2.capacity() == vec2NewCapacity) {
        std::cout << "Vector should have size equal to " << vec2NewSize << " \n";
        std::cout << "Vector should have capacity equal to " << vec2NewCapacity << " \n";
    }

    std::cout << "After implementing begin and end range-based for loop can be use\n";
    for (auto el : vec2) {
        std::cout << el << '\n';
    }

    if (!vec2.empty()) {
        std::cout << "vec2 is not empty\n";
    }

    return 0;
}
