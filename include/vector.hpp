#pragma once

#include <cstddef>

namespace my_vec {
template <typename T>
class vector {
public:
    constexpr vector() noexcept;
    explicit vector(std::size_t count, const T& value = T());
    ~vector() noexcept { delete[] elem_; }

    constexpr T& operator[](std::size_t pos) { return elem_[pos]; }
    constexpr const T& operator[](std::size_t pos) const { return elem_[pos]; }

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

template <typename T>
vector<T>::vector(std::size_t count, const T& value)
    : elem_ { new T[count] }
    , size_ { count }
    , space_ { count }
{
    for (size_t i = 0; i < count; ++i) {
        elem_[i] = value;
    }
}
}
