# vector - a simplified version of std::vector
## General Information

Simplified version of vector container from standard template library.
To manage memory vector uses simplified allocator, to constructing objects in unitialised memory it uses `construct_at`(c++20) which is wrapper of placement new, for filling/copying to uninitialised memory it uses bunch  of functions from \<memory\> header. Vector offers most of orginal functions but not  all of thier variations.

Bool specialization of vector uses std::uint64_t as a block type to keep inside 64 bits. For bool vector just basic functionality is implemented(without comparisons, iterators and some modifiers).

## Technologies Used
Project created with:
- C++20
- cmake
- gtest
- valgrind
- clang-format (WebKit style)

## Setup
Requirements to run project:
- machine with linux
- cmake (3.16 or newer)
- at least gcc-10 and g++10 which supports c++20

To build examples locally follow the sequence below:
```
mkdir build
cd build
cmake ..
make -j
```

To run tests and examples:
```
ctest -v or ./vector-ut
./vector
```

## Usage
Basic usage of implemented vector is presented below

```c++
my_vec::vector<int> v = { 7, 5, 16, 8 };
v.push_back(25);
v.push_back(13);
```

For more use cases check **[Use Cases](main.cpp#L32)**

## Project Status
Generic vector finished, vector of bools needs polishing.

### TODO:
#### **vector\<bool>**:
- Iterators
- Pointer
- Modifiers(insert, emplace)
- Comparisions
