#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <cassert>

#include "vector.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& s, const my_vec::vector<T>& v) 
{
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

void vectorBasicExample()
{
    my_vec::vector<int> v = { 7, 5, 16, 8 };

    v.push_back(25);
    v.push_back(13);

    std::cout << v << '\n';
}

void vectorConstructorsExample()
{
    my_vec::vector<std::string> words1 { "the", "frogurt", "is", "also", "cursed" };
    std::cout << "words1: " << words1 << '\n';

    my_vec::vector<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2(words2 == words1): " << words2 << '\n';

    my_vec::vector<std::string> words3(words1);
    std::cout << "words3(words3 == words1): " << words3 << '\n';

    my_vec::vector<std::string> words4(5, "Mo");
    std::cout << "words4: " << words4 << '\n';
}

void vectorAssignmentsExample()
{
    my_vec::vector<int> nums1 { 3, 1, 4, 6, 5, 9 };
    my_vec::vector<int> nums2;
    my_vec::vector<int> nums3;

    std::cout << "Initially:\n"
              << " nums1: " << nums1.size() << ','
              << " nums2: " << nums2.size() << ','
              << " nums3: " << nums3.size() << '\n';

    nums2 = nums1;
    std::cout << "After assignment:\n"
              << " nums1: " << nums1.size() << ','
              << " nums2: " << nums2.size() << ','
              << " nums3: " << nums3.size() << '\n';


    nums3 = std::move(nums1);
    std::cout << "After move assignment:\n"
              << " nums1: " << nums1.size() << ','
              << " nums2: " << nums2.size() << ','
              << " nums3: " << nums3.size() << '\n';

    std::cout << "Now nums3 = " << nums3 << '\n';

    nums3 = { 1, 2, 3 };
    std::cout << "After assignment of initializer_list \n nums3 = " << nums3 << '\n';
}

void vectorAtExample()
{
    my_vec::vector<int> data = { 1, 2, 4, 5, 5, 6 };
    std::cout << "data = " << data << '\n';

    data.at(1) = 88;
    std::cout << "Element at index 2 has value " << data.at(2) << '\n';
    std::cout << "data size = " << data.size() << '\n';

    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';
    }
    
    std::cout << "data = " << data << '\n';
}

void vectorSquareBracketExample()
{
    my_vec::vector<int> numbers { 2, 4, 6, 8 };
    std::cout << "numbers = " << numbers << '\n';
    std::cout << "Second element: " << numbers[1] << '\n';

    numbers[0] = 5;
    std::cout << "numbers = " << numbers << '\n';
}

void vectorFrontExample()
{
    my_vec::vector<char> letters { 'o', 'm', 'g', 'w', 't', 'f' };

    if (!letters.empty()) {
        std::cout << "The first character is '" << letters.front() << "'.\n";
    }
}

void vectorBackExample()
{
    my_vec::vector<char> letters { 'a', 'b', 'c', 'd', 'e', 'f' };

    if (!letters.empty()) {
        std::cout << "The last character is '" << letters.back() << "'.\n";
    }
}

void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data read as pointer = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

void vectorDataExample()
{
    my_vec::vector<int> container { 1, 2, 3, 4 };
    pointer_func(container.data(), container.size());
}

void vectorBeginAndEndExample()
{
    my_vec::vector<int> nums { 1, 2, 4, 8, 16 };
    my_vec::vector<std::string> fruits { "orange", "apple", "raspberry" };
    my_vec::vector<char> empty;

    // Print vector.
    std::for_each(nums.begin(), nums.end(), [](const int n) { std::cout << n << ' '; });
    std::cout << '\n';

    // Sums all integers in the vector nums (if any), printing only the result.
    std::cout << "Sum of nums: "
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';

    // Prints the first fruit in the vector fruits, checking if there is any.
    if (!fruits.empty())
        std::cout << "First fruit: " << *fruits.begin() << '\n';

    if (empty.begin() == empty.end())
        std::cout << "vector 'empty' is indeed empty.\n";
}

void vectorReverseBeginAndReverseEndExample()
{
    my_vec::vector<int> nums { 1, 2, 4, 8, 16 };
    my_vec::vector<std::string> fruits { "orange", "apple", "raspberry" };
    my_vec::vector<char> empty;

    // Print vector.
    std::for_each(nums.rbegin(), nums.rend(), [](const int n) { std::cout << n << ' '; });
    std::cout << '\n';

    // Sums all integers in the vector nums (if any), printing only the result.
    std::cout << "Sum of nums: "
              << std::accumulate(nums.rbegin(), nums.rend(), 0) << '\n';

    // Prints the first fruit in the vector fruits, checking if there is any.
    if (!fruits.empty())
        std::cout << "First fruit: " << *fruits.rbegin() << '\n';

    if (empty.rbegin() == empty.rend())
        std::cout << "vector 'empty' is indeed empty.\n";
}

void vectorEmptyExample()
{
    std::cout << std::boolalpha;
    my_vec::vector<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

    numbers.push_back(42);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
}

void vectorSizeExample()
{
    my_vec::vector<int> nums { 1, 3, 5, 7 };
    std::cout << "nums contains " << nums.size() << " elements.\n";
}

void vectorReserveExample()
{
    my_vec::vector<int> foo;
    auto sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
        foo.push_back(i);
        if (sz != foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    my_vec::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);
    std::cout << "making bar grow(after reserve of 100 elements):\n";
    for (int i = 0; i < 100; ++i) {
        bar.push_back(i);
        if (sz != bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
}

void vectorCapacityExample()
{
    int sz = 200;
    my_vec::vector<int> v1;

    auto cap = v1.capacity();
    std::cout << "initial capacity=" << cap << '\n';

    for (int n = 0; n < sz; ++n) {
        v1.push_back(n);
        if (cap != v1.capacity()) {
            cap = v1.capacity();
            std::cout << "new capacity=" << cap << '\n';
        }
    }

    std::cout << "final size=" << v1.size() << '\n';
    std::cout << "final capacity=" << v1.capacity() << '\n';
}

void vectorShrinkToFitExample()
{
    my_vec::vector<int> v;
    std::cout << "Default-constructed capacity is " << v.capacity() << '\n';
    v.resize(100);
    std::cout << "Capacity of a 100-element vector is " << v.capacity() << '\n';
    v.resize(50);
    std::cout << "Capacity after resize(50) is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    v.clear();
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    for (int i = 1000; i < 1300; ++i) {
        v.push_back(i);
    }
    std::cout << "Capacity after adding 300 elements is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
}

void vectorClearExample()
{
    my_vec::vector<int> container { 1, 2, 3 };

    std::cout << "Before clear: " << container << '\n';
    std::cout << "Size=" << container.size() << ", Capacity=" << container.capacity() << '\n';

    std::cout << "Clear\n";
    container.clear();

    std::cout << "After clear: " << container << '\n';
    std::cout << "Size=" << container.size() << ", Capacity=" << container.capacity() << '\n';
}

void vectorSimplifiedInsertExample()
{
    my_vec::vector<int> vec(std::size_t(3), 100);
    std::cout << vec << '\n';

    auto it = vec.begin();
    it = vec.insert(it, 200);
    std::cout << vec << '\n';
}

struct A {
    std::string s;
    A() = default;
    A(std::string str)
        : s(std::move(str))
    {
        std::cout << " constructed\n";
    }
    A(const A& o)
        : s(o.s)
    {
        std::cout << " copy constructed\n";
    }
    A(A&& o)
        : s(std::move(o.s))
    {
        std::cout << " move constructed\n";
    }
    A& operator=(const A& other)
    {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    A& operator=(A&& other)
    {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
};

void vectorEmplaceExample()
{
    //not work as expected due to lack of placement new in implementation
    my_vec::vector<A> container;
    // reserve enough place so vector does not have to resize
    container.reserve(10);
    std::cout << "construct 2 times A:\n";
    A two { "two" };
    A three { "three" };

    std::cout << "emplace:\n";
    container.emplace(container.end(), "one");

    std::cout << "emplace with A&:\n";
    container.emplace(container.end(), two);

    std::cout << "emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));

    std::cout << "content:\n";
    for (const auto& obj : container)
        std::cout << ' ' << obj.s;
    std::cout << '\n';
}

void vectorSimplifiedEraseExample()
{
    my_vec::vector<int> c { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << c << '\n';

    c.erase(c.begin());
    std::cout << c << '\n';

    // Erase all even numbers (C++11 and later)
    for (auto it = c.begin(); it != c.end();) {
        if (*it % 2 == 0) {
            it = c.erase(it);
        } else {
            ++it;
        }
    }
    std::cout << c << '\n';
}

void vectorPushBackExample()
{
    my_vec::vector<std::string> letters;

    letters.push_back("abc");
    std::string s = "def";
    letters.push_back(std::move(s));

    std::cout << "vector holds: ";
    for (auto&& letter : letters) {
        std::cout << std::quoted(letter) << ' ';
    }
    std::cout << "\nMoved-from string holds " << std::quoted(s) << '\n';
}

struct President {
    std::string name;
    std::string country;
    int year;

    President() = default;
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name))
        , country(std::move(p_country))
        , year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name))
        , country(std::move(other.country))
        , year(other.year)
    {
        std::cout << "I am being moved.\n";
    }
    President& operator=(const President& other) = default;
};

void vectorEmplaceBackExample()
{
    my_vec::vector<President> elections;
    std::cout << "emplace_back:\n";
    auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
    assert(ref.year == 1994 && "uses a reference to the created object (C++17)");

    my_vec::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president : elections) {
        std::cout << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    for (President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
}

void vectorPopBackExample()
{
    my_vec::vector<int> numbers;
    std::cout << numbers << '\n';

    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
    std::cout << numbers << '\n';

    numbers.pop_back();
    std::cout << numbers << '\n';
}

void vectorResizeExample()
{
    my_vec::vector<int> c = { 1, 2, 3 };
    std::cout << "The vector holds: " << c << '\n';
    c.resize(5);
    std::cout << "After resize up to 5: " << c << '\n';
    c.resize(2);
    std::cout << "After resize down to 2: " << c << '\n';
    c.resize(6, 4);
    std::cout << "After resize up to 6 (initializer = 4): " << c << '\n';
}

void vectorSwapExample()
{
    my_vec::vector<int> a1 { 1, 2, 3 }, a2 { 4, 5 };

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    std::cout << a1 << ' ' << a2 << ' ' << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << ' ' << a2 << ' ' << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.
}

int main()
{
    std::cout << " vectorBasicExample: \n";
    vectorBasicExample();

    std::cout << "\n vectorConstructorsExample: \n";
    vectorConstructorsExample();

    std::cout << "\n vectorAssignmentsExample: \n";
    vectorAssignmentsExample();

    std::cout << "\n vectorAtExample: \n";
    vectorAtExample();

    std::cout << "\n vectorSquareBracketExample: \n";
    vectorSquareBracketExample();

    std::cout << "\n vectorFrontExample: \n";
    vectorFrontExample();

    std::cout << "\n vectorBackExample: \n";
    vectorBackExample();

    std::cout << "\n vectorDataExample: \n";
    vectorDataExample();

    std::cout << "\n vectorBeginAndEndExample: \n";
    vectorBeginAndEndExample();

    std::cout << "\n vectorReverseBeginAndReverseEndExample: \n";
    vectorReverseBeginAndReverseEndExample();

    std::cout << "\n vectorEmptyExample: \n";
    vectorEmptyExample();

    std::cout << "\n vectorSizeExample: \n";
    vectorSizeExample();

    std::cout << "\n vectorReserveExample: \n";
    vectorReserveExample();

    std::cout << "\n vectorCapacityExample: \n";
    vectorCapacityExample();

    std::cout << "\n vectorShrinkToFitExample: \n";
    vectorShrinkToFitExample();

    std::cout << "\n vectorClearExample: \n";
    vectorClearExample();

    std::cout << "\n vectorInsertExample: \n";
    vectorSimplifiedInsertExample();

    std::cout << "\n vectorEmplaceExample: \n";
    vectorEmplaceExample();

    std::cout << "\n vectorSimplifiedEraseExample: \n";
    vectorSimplifiedEraseExample();

    std::cout << "\n vectorPushBackExample: \n";
    vectorPushBackExample();

    std::cout << "\n vectorEmplaceBackExample: \n";
    vectorEmplaceBackExample();

    std::cout << "\n vectorPopBackExample: \n";
    vectorPopBackExample();

    std::cout << "\n vectorResizeExample: \n";
    vectorResizeExample();

    std::cout << "\n vectorSwapExample: \n";
    vectorSwapExample();

    return 0;
}
