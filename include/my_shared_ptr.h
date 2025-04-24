//
// Created by denhumen on 4/24/25.
//

#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

#include "control_block_base.h"

template<typename T>
class my_weak_ptr;

template<typename T>
class my_shared_ptr {
    template<typename U> friend class my_shared_ptr;
    template<typename U> friend class my_weak_ptr;

public:
    my_shared_ptr() : ptr_  (nullptr), cb_(nullptr) {}

    template<typename Deleter = std::default_delete<T>>
    explicit my_shared_ptr(T* ptr, Deleter d = Deleter()) {
        cb_ = new control_block<T, Deleter>(ptr, d);
        ptr_ = ptr;
    }

    my_shared_ptr(const my_shared_ptr& other) : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) cb_->strong_count += 1;
    }

    my_shared_ptr(my_shared_ptr&& other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
        other.ptr_ = nullptr;
        other.cb_ = nullptr;
    }

    ~my_shared_ptr() {
        release();
    }

    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_ = other.cb_;
            if (cb_) cb_->strong_count += 1;
        }
        return *this;
    }

    my_shared_ptr& operator=(my_shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_ = other.cb_;
            other.ptr_ = nullptr;
            other.cb_ = nullptr;
        }
        return *this;
    }

    void reset() {
        release();
        ptr_ = nullptr;
        cb_ = nullptr;
    }

    T* get() const noexcept { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    std::size_t use_count() const noexcept { return cb_ ? cb_->strong_count : 0; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T* ptr_;
    control_block_base* cb_;

    void release() {
        if (cb_ && --cb_->strong_count == 0) {
            cb_->destroy();
            if (cb_->weak_count == 0) delete cb_;
        }
    }

    my_shared_ptr(T* ptr, control_block_base* cb) : ptr_(ptr), cb_(cb) {
        if (cb_) cb_->strong_count += 1;
    }
};


#endif //MY_SHARED_PTR_H
