#include <iostream>

#include "vector.hpp"

int main()
{
    my_vec::vector<int> vec1;

    if (vec1.size() == 0 && vec1.capacity() == 0) {
        std::cout << "Vector created by default constructor should have size equal to 0\n";
        std::cout << "Vector created by default constructor should have capacity equal to 0\n";
    }

    return 0;
}
