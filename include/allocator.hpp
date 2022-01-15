#pragma once

#include <cstddef>
#include <new>
#include <type_traits>

namespace my_alloc {
template <typename T>
struct allocator {
    using value_type = T;
    using size_type = std::size_t;
    // using difference_type = std::ptrdiff_t;
    // using propagate_on_container_move_assignment = std::true_type;

    constexpr allocator() noexcept = default;
    constexpr allocator(const allocator& other) noexcept = default;
    constexpr ~allocator() = default;

    [[nodiscard]] constexpr T* allocate(size_type n);
    constexpr void deallocate(T* p, [[maybe_unused]] size_type n);
};

template <typename T>
[[nodiscard]] constexpr T* allocator<T>::allocate(size_type n)
{
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template <typename T>
constexpr void allocator<T>::deallocate(T* p, [[maybe_unused]] size_type n)
{
    ::operator delete(p);
}
}
