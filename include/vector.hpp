#pragma once

#include <cstddef>
#include <utility>

namespace my_vec {
template <typename T>
class vector {
public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    constexpr vector() noexcept;
    explicit vector(size_type count, const T& value = T());
    constexpr vector(const vector& other);
    constexpr vector& operator=(const vector& other);
    constexpr vector(vector&& other) noexcept;
    constexpr vector& operator=(vector&& other) noexcept;
    ~vector() noexcept { delete[] elem_; }

    constexpr reference operator[](size_type pos) { return elem_[pos]; }
    constexpr const_reference operator[](size_type pos) const { return elem_[pos]; }
    iterator begin() noexcept { return elem_; }
    const_iterator begin() const noexcept { return elem_; }
    iterator end() noexcept { return elem_ + size_; }
    const_iterator end() const noexcept { return elem_ + size_; }

    bool empty() const noexcept { return begin() == end(); }
    size_type size() const { return size_; }
    void reserve (size_type new_cap);
    size_type capacity() const { return space_; }

    void push_back(const T& value);
    void push_back(T&& value);
    void resize(size_type count, T value = T());

private:
    T* elem_;
    size_type size_;
    size_type space_;
};

template <typename T>
constexpr vector<T>::vector() noexcept
    : elem_ { nullptr }
    , size_ { 0 }
    , space_ { 0 }
{
}

template <typename T>
vector<T>::vector(size_type count, const T& value)
    : elem_ { new T[count] }
    , size_ { count }
    , space_ { count }
{
    for (size_type i = 0; i < count; ++i) {
        elem_[i] = value;
    }
}

template <typename T>
constexpr vector<T>::vector(const vector<T>& other)
    : elem_ { new T[other.space_] }
    , size_ { other.size_ }
    , space_ { other.space_ }
{
    for (size_type i = 0; i < size(); ++i) {
        elem_[i] = other.elem_[i];
    }
}

template <typename T>
constexpr vector<T>& vector<T>::operator=(const vector<T>& other)
{
    reserve(other.space_);
    size_ = other.size_;
    space_ = other.space_;
    for (size_type i = 0; i < size(); ++i) {
        elem_[i] = other.elem_[i];
    }
    return *this;
}

template <typename T>
constexpr vector<T>::vector(vector&& other) noexcept
    : elem_ { other.elem_ }
    , size_ { other.size_ }
    , space_ { other.space_ }
{
    other.elem_ = nullptr;
    other.size_ = 0;
    other.space_ = 0;
}

template <typename T>
constexpr vector<T>& vector<T>::operator=(vector&& other) noexcept
{
    elem_ = other.elem_;
    size_ = other.size_;
    space_ = other.space_;
    other.elem_ = nullptr;
    other.size_ = 0;
    other.space_ = 0;
    return *this;
}

template <typename T>
void vector<T>::reserve(size_type new_cap)
{
    if (new_cap > capacity()) {
        T* tmp = new T[new_cap];
        for (size_type i = 0; i < size(); ++i) {
            tmp[i] = elem_[i];
        }
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
void vector<T>::resize(size_type count, T value)
{
    reserve(count);
    if (count > size()) {
        for (size_type i = size(); i < count; ++i) {
            elem_[i] = value;
        }
    }
    size_ = count;
}
}
