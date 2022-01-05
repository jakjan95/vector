# vector - a simplified version of std::vector
## General Information

Simplified version of vector container from standard template library.
To manage memory vector uses new expression instead of placement new as it is done in library. Vector offers most of orginal functions but not  all of thier variations.

## Technologies Used
Project created with:
- C++17
- cmake
- gtest
- valgrind

## Setup

Requirements to run project:
- machine with linux
- cmake (3.16 or newer)
- gcc compiler supporting modern c++(c++17 or newer)

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
Project is still in progress.

To do:
- Adding vector specialization for bool
- Adding allocator
- Improve allocation with placement new
- Implementation all variations of functions(insert, emplace etc)
