//
// Created by denhumen on 4/24/25.
//

#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H

#include <utility>
#include <memory>

template<typename T, typename Deleter = std::default_delete<T>>
class my_unique_ptr {
public:
    explicit my_unique_ptr(T* ptr = nullptr, Deleter d = Deleter()) : ptr_(ptr), deleter_(d) {}
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    my_unique_ptr(my_unique_ptr&& other) noexcept : ptr_(other.ptr_), deleter_(std::move(other.deleter_)) {
        other.ptr_ = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr_ = other.ptr_;
            deleter_ = std::move(other.deleter_);
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~my_unique_ptr() {
        if (ptr_) deleter_(ptr_);
    }

    T* get() const noexcept { return ptr_; }
    T* release() noexcept {
        T* temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }
    void reset(T* new_ptr = nullptr) {
        if (ptr_) deleter_(ptr_);
        ptr_ = new_ptr;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T* ptr_;
    Deleter deleter_;
};

#endif //MY_UNIQUE_PTR_H
