//
// Created by denhumen on 4/24/25.
//

#ifndef MY_WEAK_PTR_H
#define MY_WEAK_PTR_H

#include "my_shared_ptr.h"

template<typename T>
class my_weak_ptr {
public:
    my_weak_ptr() : ptr_(nullptr), cb_(nullptr) {}

    explicit my_weak_ptr(const my_shared_ptr<T>& shared) : ptr_(shared.ptr_), cb_(shared.cb_) {
        if (cb_) cb_->weak_count += 1;
    }

    my_weak_ptr(const my_weak_ptr& other) : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) cb_->weak_count += 1;
    }

    my_weak_ptr& operator=(const my_weak_ptr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_ = other.cb_;
            if (cb_) ++cb_->weak_count;
        }
        return *this;
    }

    ~my_weak_ptr() {
        release();
    }

    my_shared_ptr<T> lock() const {
        if (cb_ && cb_->strong_count > 0)
            return my_shared_ptr<T>(ptr_, cb_);
        return my_shared_ptr<T>();
    }

private:
    T* ptr_;
    control_block_base* cb_;

    void release() {
        if (cb_ && --cb_->weak_count == 0 && cb_->strong_count == 0)
            delete cb_;
    }
};

#endif //MY_WEAK_PTR_H
