//
// Created by denhumen on 4/24/25.
//

#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <cstddef>

template<typename T, std::size_t N>
class my_array {
public:
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using ref = T&;
    using const_ref = const T&;

    constexpr my_array() noexcept = default;
    my_array(std::initializer_list<T> init) {
        if (init.size() != N) throw std::length_error("can't initialize list from a list with different length");
        std::copy(init.begin(), init.end(), data_);
    }

    constexpr ref operator[](std::size_t i) noexcept { return data_[i]; }
    constexpr const_ref operator[](std::size_t i) const noexcept { return data_[i]; }
    ref at(std::size_t i) {
        if (i >= N) throw std::out_of_range("out of array length range");
        return data_[i];
    }
    [[nodiscard]] constexpr std::size_t size() const noexcept { return N; }
    [[nodiscard]] constexpr bool empty() const noexcept { return N == 0; }
    ref front() noexcept { return data_[0]; }
    const_ref front() const noexcept { return data_[0]; }
    ref back() noexcept { return data_[N - 1]; }
    const_ref back() const noexcept { return data_[N - 1]; }
    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }
    iterator end() noexcept { return data_ + N; }
    const_iterator end() const noexcept { return data_ + N; }
    const_iterator cend() const noexcept { return data_ + N; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    void swap(my_array& other) noexcept {
        for (std::size_t i = 0; i < N; ++i) std::swap(data_[i], other.data_[i]);
    }

    friend bool operator==(const my_array& a, const my_array& b) noexcept {
        for (std::size_t i = 0; i < N; ++i)
            if (!(a.data_[i] == b.data_[i])) return false;
        return true;
    }
    friend bool operator!=(const my_array& a, const my_array& b) noexcept { return !(a == b); }
    friend bool operator<(const my_array& a, const my_array& b) noexcept {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
    friend bool operator<=(const my_array& a, const my_array& b) noexcept { return !(b < a); }
    friend bool operator>(const my_array& a, const my_array& b) noexcept { return b < a; }
    friend bool operator>=(const my_array& a, const my_array& b) noexcept { return !(a < b); }

private:
    T data_[N]{};
};

#endif //MY_ARRAY_H
