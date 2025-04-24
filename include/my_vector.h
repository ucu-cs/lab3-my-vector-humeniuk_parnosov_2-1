//
// Created by denhumen on 4/24/25.
//

#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <stdexcept>

template<typename T>
class my_vector {
public:
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using ref = T&;
    using const_ref = const T&;

    my_vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}
    my_vector(std::size_t count, const T& value) : my_vector() {
        reserve(count);
        for (std::size_t i = 0; i < count; ++i) push_back(value);
    }
    my_vector(std::initializer_list<T> init) : my_vector() {
        reserve(init.size());
        for (auto& v : init) push_back(v);
    }
    my_vector(const my_vector& other) : my_vector() {
        reserve(other.size_);
        for (std::size_t i = 0; i < other.size_; ++i) push_back(other.data_[i]);
    }
    my_vector(my_vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }
    ~my_vector() { delete[] data_; }

    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            clear();
            reserve(other.size_);
            for (std::size_t i = 0; i < other.size_; ++i) push_back(other.data_[i]);
        }
        return *this;
    }
    my_vector& operator=(my_vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    ref operator[](std::size_t i) noexcept { return data_[i]; }
    const_ref operator[](std::size_t i) const noexcept { return data_[i]; }
    ref at(std::size_t i) {
        if (i >= size_) throw std::out_of_range("out of vector length range");
        return data_[i];
    }
    ref front() { return data_[0]; }
    const_ref front() const { return data_[0]; }
    ref back() { return data_[size_ - 1]; }
    const_ref back() const { return data_[size_ - 1]; }
    iterator data() noexcept { return data_; }
    const_iterator data() const noexcept { return data_; }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
    void reserve(std::size_t new_cap) {
        if (new_cap <= capacity_) return;
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }
    void shrink_to_fit() {
        if (size_ < capacity_) {
            T* new_data = size_ ? new T[size_] : nullptr;
            for (std::size_t i = 0; i < size_; ++i) new_data[i] = std::move(data_[i]);
            delete[] data_;
            data_ = new_data;
            capacity_ = size_;
        }
    }

    void clear() noexcept { size_ = 0; }
    void push_back(const T& value) { ensure_capacity(size_ + 1); data_[size_++] = value; }
    void push_back(T&& value) { ensure_capacity(size_ + 1); data_[size_++] = std::move(value); }
    template<typename... Args>
    void emplace_back(Args&&... args) {
        ensure_capacity(size_ + 1);
        data_[size_++] = T(std::forward<Args>(args)...);
    }
    void pop_back() noexcept { if (size_) --size_; }
    void resize(std::size_t count) { resize(count, T()); }
    void resize(std::size_t count, const T& value) {
        if (count < size_) size_ = count;
        else {
            reserve(count);
            for (; size_ < count; ++size_) data_[size_] = value;
        }
    }
    iterator insert(const_iterator pos, const T& value) {
        std::size_t idx = pos - data_;
        ensure_capacity(size_ + 1);
        for (std::size_t i = size_; i > idx; --i) data_[i] = std::move(data_[i - 1]);
        data_[idx] = value;
        ++size_;
        return data_ + idx;
    }
    iterator erase(const_iterator pos) {
        std::size_t idx = pos - data_;
        for (std::size_t i = idx; i + 1 < size_; ++i) data_[i] = std::move(data_[i + 1]);
        --size_;
        return data_ + idx;
    }
    iterator erase(const_iterator first, const_iterator last) {
        std::size_t idx = first - data_;
        std::size_t count = last - first;
        for (std::size_t i = idx; i + count < size_; ++i) data_[i] = std::move(data_[i + count]);
        size_ -= count;
        return data_ + idx;
    }
    void swap(my_vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    friend void swap(my_vector& a, my_vector& b) noexcept { a.swap(b); }

    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }
    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cend() const noexcept { return data_ + size_; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    friend bool operator==(const my_vector& a, const my_vector& b) {
        if (a.size_ != b.size_) return false;
        for (std::size_t i = 0; i < a.size_; ++i)
            if (!(a.data_[i] == b.data_[i])) return false;
        return true;
    }
    friend bool operator!=(const my_vector& a, const my_vector& b) { return !(a == b); }
    friend auto operator<(const my_vector &a, const my_vector &b) -> bool {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
    friend bool operator<=(const my_vector& a, const my_vector& b) { return !(b < a); }
    friend bool operator>(const my_vector& a, const my_vector& b) { return b < a; }
    friend bool operator>=(const my_vector& a, const my_vector& b) { return !(a < b); }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void ensure_capacity(std::size_t min_cap) {
        if (capacity_ < min_cap) {
            std::size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            if (new_cap < min_cap) new_cap = min_cap;
            reserve(new_cap);
        }
    }
};

#endif //MY_VECTOR_H
