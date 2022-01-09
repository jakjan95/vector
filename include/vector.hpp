#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

namespace my_vec {
template <typename T>
class vector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type = std::ptrdiff_t;

    constexpr vector() noexcept;
    explicit vector(size_type count, const T& value = T());
    constexpr vector(const vector& other);
    constexpr vector& operator=(const vector& other);
    constexpr vector(vector&& other) noexcept;
    constexpr vector& operator=(vector&& other) noexcept;
    constexpr vector(std::initializer_list<T> init);
    constexpr vector& operator=(std::initializer_list<T> ilist);
    template <class InputIt>
    constexpr vector(InputIt first, InputIt last);
    ~vector() noexcept { delete[] elem_; }

    constexpr reference at(size_type pos);
    constexpr const_reference at(size_type pos) const;
    constexpr reference operator[](size_type pos) { return elem_[pos]; }
    constexpr const_reference operator[](size_type pos) const { return elem_[pos]; }
    constexpr reference front() { return elem_[0]; }
    constexpr const_reference front() const { return elem_[0]; }
    constexpr reference back() { return elem_[size_ - 1]; }
    constexpr const_reference back() const { return elem_[size_ - 1]; }
    constexpr T* data() noexcept { return elem_; }
    constexpr const T* data() const noexcept { return elem_; }

    iterator begin() noexcept { return elem_; }
    const_iterator begin() const noexcept { return elem_; }
    iterator end() noexcept { return elem_ + size_; }
    const_iterator end() const noexcept { return elem_ + size_; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    bool empty() const noexcept { return begin() == end(); }
    size_type size() const { return size_; }
    void reserve (size_type new_cap);
    size_type capacity() const { return space_; }
    constexpr void shrink_to_fit();

    constexpr void clear() noexcept;
    constexpr iterator insert(iterator pos, const T& value);
    template <typename... Args>
    constexpr iterator emplace(iterator pos, Args&&... args);
    constexpr iterator erase(const_iterator pos);
    void push_back(const T& value);
    void push_back(T&& value);
    template <typename... Args>
    constexpr reference emplace_back(Args&&... args);
    constexpr void pop_back();
    void resize(size_type count, T value = T());
    constexpr void swap(vector& other) noexcept;

private:
    T* elem_;
    size_type size_;
    size_type space_;
    const size_type defaultContainerCapacity_ = 8;
};


/*
* A memory space optimized specialization of vector for bools
* which offers fixed time access to individual elements in any order.
*/

template <>
class vector<bool> {
    using block_t = std::uint64_t;

public:
    using value_type = bool;
    using size_type = std::size_t;
    using const_reference = bool;
    // using pointer = TODO;
    // using const_pointer = TODO;
    // using iterator = TODO;
    // using const_iterator = TODO;
    // using reverse_iterator = std::reverse_iterator<iterator>;
    // using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    class reference {
    public:
        ~reference() = default;

        constexpr reference& operator=(bool x) noexcept
        {
            if (x) {
                value_ |= mask_;
            } else {
                value_ &= ~mask_;
            }
            return *this;
        }

        constexpr reference& operator=(const reference& x) noexcept
        {
            value_ = bool(x);
            return *this;
        }

        constexpr operator bool() const noexcept
        {
            return !!(value_ & mask_);
        }

        constexpr void flip() noexcept
        {
            value_ ^= mask_;
        }

    private:
        block_t& value_;
        block_t mask_;
        friend vector<bool>;

        constexpr reference(block_t& value, block_t mask) noexcept
            : value_ { value }
            , mask_ { mask }
        {
        }
    };

    constexpr vector() noexcept;
    vector(size_type count, bool value = false);
    vector(const vector& other);
    constexpr vector& operator=(const vector& other);
    constexpr vector(vector&& other) noexcept;
    ~vector() noexcept { delete[] elem_; }

    constexpr reference operator[](size_type pos);
    constexpr const_reference operator[](size_type pos) const;

    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }
    constexpr size_type size() const noexcept { return size_; }
    constexpr void reserve(size_type new_cap);
    constexpr size_type capacity() const noexcept { return space_; }

    constexpr void push_back(const value_type& value);
    constexpr void resize( size_type count, const value_type& value = {});

private:
    block_t* elem_;
    size_type size_;
    size_type space_;

    constexpr inline size_type getNumberOfBlocksTypeToAllocateSpace(size_type count) const;
    constexpr inline size_type getCapacityValueForAllocatedSpace(size_type count) const;
    constexpr std::tuple<size_type, size_type>  getBlockWithBitAndMask(size_type position) const;
    constexpr void setValueAtPosition(size_type position, bool value);
    constexpr inline auto getBlockCapacity() const { return sizeof(block_t) * 8; }
};

/*
* Generic vector functions
*/

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
constexpr vector<T>::vector(std::initializer_list<T> init)
    : elem_ { new T[init.size()] }
    , size_ { init.size() }
    , space_ { init.size() }
{
    size_type arrIndex = 0;
    for (const auto& el : init) {
        elem_[arrIndex++] = el;
    }
}

template <typename T>
constexpr vector<T>& vector<T>::operator=(std::initializer_list<T> ilist)
{
    clear();
    reserve(ilist.size());
    size_ = ilist.size();
    space_ = ilist.size();

    size_type arrIndex = 0;
    for (const auto& el : ilist) {
        elem_[arrIndex++] = el;
    }

    return *this;
}

template <typename T>
template <class InputIt>
constexpr vector<T>::vector(InputIt first, InputIt last)
    : elem_ { new T[static_cast<size_type>(last - first)] }
    , size_ { static_cast<size_type>(last - first) }
    , space_ { static_cast<size_type>(last - first) }
{
    size_type arrIndex = 0;
    for (auto it = first; it != last; ++it) {
        elem_[arrIndex++] = *it;
    }
}

template <typename T>
constexpr typename vector<T>::reference vector<T>::at(size_type pos)
{
    if (pos >= size()) {
        throw std::out_of_range { "Position not within range of vector" };
    }
    return elem_[pos];
}

template <typename T>
constexpr typename vector<T>::const_reference vector<T>::at(size_type pos) const
{
    if (pos >= size()) {
        throw std::out_of_range { "Position not within range of vector" };
    }
    return elem_[pos];
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
constexpr void vector<T>::shrink_to_fit()
{
    reserve(size_);
    space_ = size_;
}

template <typename T>
constexpr void vector<T>::clear() noexcept
{
    std::destroy(elem_, elem_ + size_);
    size_ = 0;
}

template <typename T>
constexpr typename vector<T>::iterator vector<T>::insert(iterator pos, const T& value)
{
    if (size() == capacity()) {
        auto posDistance = static_cast<size_type>(pos - elem_);
        reserve(capacity() == 0 ? defaultContainerCapacity_ : 2 * capacity());
        pos = elem_ + posDistance;
    }

    size_++;
    for (auto itCurrent = pos + 1, itPrevious = pos; itCurrent != elem_ + size_; ++itCurrent, ++itPrevious) {
        *itCurrent = *itPrevious;
    }

    *pos = value;
    return pos;
}

template <typename T>
template <typename... Args>
constexpr typename vector<T>::iterator vector<T>::emplace(iterator pos, Args&&... args)
{
    if (size() == capacity()) {
        auto posDistance = static_cast<size_type>(pos - elem_);
        reserve(capacity() == 0 ? defaultContainerCapacity_ : 2 * capacity());
        pos = elem_ + posDistance;
    }

    size_++;
    for (auto itCurrent = pos + 1, itPrevious = pos; itCurrent != elem_ + size_; ++itCurrent, ++itPrevious) {
        *itCurrent = *itPrevious;
    }

    *pos = T(std::forward<Args>(args)...);
    return pos;
}

template <typename T>
constexpr typename vector<T>::iterator vector<T>::erase(const_iterator pos)
{
    (*pos).~T();
    size_--;
    const auto posDistance = static_cast<size_type>(pos - elem_);
    for (auto itCurrent = elem_ + posDistance, itNext = itCurrent + 1; itCurrent != elem_ + size_; ++itCurrent, ++itNext) {
        *itCurrent = *itNext;
    }

    return elem_ + posDistance;
}

template <typename T>
void vector<T>::push_back(const T& value)
{
    if(capacity() == 0){
        reserve(defaultContainerCapacity_);
    }
    else if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    elem_[size_++] = value;
}

template <typename T>
void vector<T>::push_back(T&& value)
{
    if(capacity() == 0){
        reserve(defaultContainerCapacity_);
    }
    else if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    elem_[size_++] = std::move(value);
}

template <typename T>
template <typename... Args>
constexpr typename vector<T>::reference vector<T>::emplace_back(Args&&... args)
{
    if(capacity() == 0){
        reserve(defaultContainerCapacity_);
    }
    else if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    return elem_[size_++] = T(std::forward<Args>(args)...);
}

template <typename T>
constexpr void vector<T>::pop_back()
{
    elem_[--size_].~T();
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

template <typename T>
constexpr void vector<T>::swap(vector& other) noexcept
{
    T* tmpElem = other.elem_;
    size_type tmpSize = other.size_;
    size_type tmpSpace = other.space_;

    other.elem_ = elem_;
    other.size_ = size_;
    other.space_ = space_;

    elem_ = tmpElem;
    size_ = tmpSize;
    space_ = tmpSpace;
}

/*
* Vector bool specialization functions
*/

constexpr vector<bool>::vector() noexcept
    : elem_ { nullptr }
    , size_ { 0 }
    , space_ { 0 }
{
}

vector<bool>::vector(size_type count, bool value)
    : elem_ { new block_t[getNumberOfBlocksTypeToAllocateSpace(count)] }
    , size_ { count }
    , space_ { getCapacityValueForAllocatedSpace(count) }
{
    std::fill(elem_, elem_ + getNumberOfBlocksTypeToAllocateSpace(count), block_t {});
    for (size_type i = 0; i < count; ++i) {
        setValueAtPosition(i, value);
    }
}

vector<bool>::vector(const vector& other)
    : elem_ { new block_t[getCapacityValueForAllocatedSpace(other.space_)] }
    , size_ { other.size_ }
    , space_ { other.space_ }
{
    std::fill(elem_, elem_ + getNumberOfBlocksTypeToAllocateSpace(space_), block_t {});
    for (size_type i = 0; i < size(); ++i) {
        const auto [blockWithBit, mask] = getBlockWithBitAndMask(i);
        const auto value = !!(other.elem_[blockWithBit] & mask);
        elem_[blockWithBit] ^= (-value ^ elem_[blockWithBit]) & mask;
    }
}

constexpr vector<bool>& vector<bool>::operator=(const vector& other)
{
    reserve(other.space_);
    size_ = other.size_;
    for (size_type i = 0; i < size(); ++i) {
        const auto [blockWithBit, mask] = getBlockWithBitAndMask(i);
        const auto value = !!(other.elem_[blockWithBit] & mask);
        elem_[blockWithBit] ^= (-value ^ elem_[blockWithBit]) & mask;
    }

    return *this;
}

constexpr vector<bool>::vector(vector&& other) noexcept
    : elem_ { other.elem_ }
    , size_ { other.size_ }
    , space_ { other.space_ }
{
    other.elem_ = nullptr;
    other.size_ = 0;
    other.space_ = 0;
}

constexpr vector<bool>::reference vector<bool>::operator[](size_type pos)
{
    const auto [blockWithBit, mask] = getBlockWithBitAndMask(pos);
    return reference(elem_[blockWithBit], mask);
}

constexpr vector<bool>::const_reference vector<bool>::operator[](size_type pos) const
{
    const auto [blockWithBit, mask] = getBlockWithBitAndMask(pos);
    return reference(elem_[blockWithBit], mask);
}

constexpr void vector<bool>::reserve(size_type new_cap)
{
    if (new_cap > capacity()) {
        block_t* tmp = new block_t[getNumberOfBlocksTypeToAllocateSpace(new_cap)];
        std::fill(tmp, tmp + getNumberOfBlocksTypeToAllocateSpace(new_cap), block_t {});
        for (size_type i = 0; i < size(); ++i) {
            const auto [blockWithBit, mask] = getBlockWithBitAndMask(i);
            const auto value = !!(elem_[blockWithBit] & mask);
            tmp[blockWithBit] ^= (-value ^ tmp[blockWithBit]) & mask;
        }

        delete[] elem_;
        elem_ = tmp;
        space_ = getCapacityValueForAllocatedSpace(new_cap);
    }
}

constexpr void vector<bool>::resize(size_type count, const value_type& value)
{
    reserve(count);
    if (count > size()) {
        for (size_type i = size(); i < count; ++i) {
            setValueAtPosition(i, value);
        }
    }
    size_ = count;
}

constexpr void vector<bool>::push_back(const value_type& value)
{
    if (capacity() == 0) {
        reserve(getBlockCapacity());
    } else if (size() >= capacity()) {
        reserve(2 * capacity());
    }
    setValueAtPosition(size_++, value);
}

constexpr inline vector<bool>::size_type vector<bool>::getNumberOfBlocksTypeToAllocateSpace(size_type count) const
{
    return static_cast<size_type>(std::ceil(static_cast<double>(count) / static_cast<double>(getBlockCapacity())));
}

constexpr inline vector<bool>::size_type vector<bool>::getCapacityValueForAllocatedSpace(size_type count) const
{
    return getNumberOfBlocksTypeToAllocateSpace(count) * getBlockCapacity();
}

constexpr std::tuple<vector<bool>::size_type, vector<bool>::size_type> vector<bool>::getBlockWithBitAndMask(size_type position) const
{
    const auto blockWithBit = position / getBlockCapacity();
    const auto bitPositionInBlock = position % getBlockCapacity();
    const auto mask = 1ULL << bitPositionInBlock;
    return std::make_tuple(blockWithBit, mask);
}

constexpr void vector<bool>::setValueAtPosition(size_type position, bool value)
{
    const auto [blockWithBit, mask] = getBlockWithBitAndMask(position);
    elem_[blockWithBit] ^= (-value ^ elem_[blockWithBit]) & mask;
}
}
