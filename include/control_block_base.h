//
// Created by denhumen on 4/24/25.
//

#ifndef CONTROL_BLOCK_BASE_H
#define CONTROL_BLOCK_BASE_H

#include <cstddef>

struct control_block_base {
    std::size_t strong_count = 1;
    std::size_t weak_count = 0;
    virtual void destroy() = 0;
    virtual ~control_block_base() = default;
};

template<typename T, typename Deleter>
struct control_block final : control_block_base {
    T* ptr;
    Deleter deleter;

    control_block(T* p, Deleter d) : ptr(p), deleter(d) {}
    void destroy() override {
        deleter(ptr);
    }
};


#endif //CONTROL_BLOCK_BASE_H
