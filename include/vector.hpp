#pragma once

#include <cstddef>

namespace my_vec {
template <typename T>
class vector {
public:
    constexpr vector() noexcept;
    ~vector() noexcept { delete[] elem_; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return space_; }

private:
    T* elem_;
    std::size_t size_;
    std::size_t space_;
};

template <typename T>
constexpr vector<T>::vector() noexcept
    : elem_ { nullptr }
    , size_ { 0 }
    , space_ { 0 }
{
}
}
