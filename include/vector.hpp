#pragma once

#include <cstddef>
#include <cstring>
#include <utility>

namespace my_vec {
template <typename T>
class vector {
public:
    constexpr vector() noexcept;
    explicit vector(std::size_t count, const T& value = T());
    ~vector() noexcept { delete[] elem_; }

    constexpr T& operator[](std::size_t pos) { return elem_[pos]; }
    constexpr const T& operator[](std::size_t pos) const { return elem_[pos]; }

    T* begin() noexcept { return elem_; }
    const T* begin() const noexcept { return elem_; }
    T* end() noexcept { return elem_ + size_; }
    const T* end() const noexcept { return elem_ + size_; }

    bool empty() const noexcept { return begin() == end(); }
    std::size_t size() const { return size_; }
    void reserve (std::size_t new_cap);
    std::size_t capacity() const { return space_; }

    void push_back(const T& value);
    void push_back(T&& value);
    void resize(std::size_t count, T value = T());

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

template <typename T>
void vector<T>::reserve(std::size_t new_cap)
{
    if (new_cap > capacity()) {
        T* tmp = new T[new_cap];
        std::memcpy(tmp, elem_, size());
        delete[] elem_;

        elem_ = tmp;
        space_ = new_cap;
    }
}

template <typename T>
void vector<T>::push_back(const T& value)
{
    if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    elem_[size_++] = value;
}

template <typename T>
void vector<T>::push_back(T&& value)
{
    if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    elem_[size_++] = std::move(value);
}

template <typename T>
void vector<T>::resize(std::size_t count, T value)
{
    reserve(count);
    if (count > size()) {
        for (std::size_t i = size(); i < count; ++i) {
            elem_[i] = value;
        }
    }
    size_ = count;
}
}
