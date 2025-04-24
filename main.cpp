// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <cassert>
#include <iostream>
#include <chrono>
#include "my_array.h"
#include "my_vector.h"

template<typename F>
long long measure_us(F fn, size_t iterations = 1) {
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    for (size_t i = 0; i < iterations; ++i) fn();
    auto end   = clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void test_my_array() {
    my_array<int, 3> ca = {10, 20, 30};
    assert(ca[0] == 10 && "operator[] failed");
    assert(ca.size() == 3 && "size failed");

    my_array<int, 5> a = {1, 2, 3, 4, 5};
    assert(a.size() == 5);
    assert(!a.empty());
    assert(a[0] == 1);
    assert(a.at(4) == 5);
    a.at(2) = 42;
    assert(a[2] == 42);

    int sum = 0;
    for (auto it = a.begin(); it != a.end(); ++it) sum += *it;
    assert(sum == (1 + 2 + 42 + 4 + 5));

    assert(*a.rbegin() == 5);
    assert(*a.crbegin() == 5);

    my_array<int, 5> b = {1, 2, 42, 4, 5};
    assert(a == b);
    b[3] = 99;
    assert(a != b);
    assert((a < b) == true);

    std::cout << "my_array tests passed;\n";
}

void test_my_vector() {
    my_vector<std::string> v;
    assert(v.empty());
    assert(v.size() == 0);

    v.push_back("alpha");
    v.push_back("beta");
    v.emplace_back("gamma");
    assert(v.size() == 3);
    assert(v[0] == "alpha" && v[1] == "beta" && v[2] == "gamma");

    try {
        v.at(3);
        assert(false && "Expected out_of_range");
    } catch (const std::out_of_range&) {
    }

    v.insert(v.begin() + 1, "inserted");
    assert(v.size() == 4);
    assert(v[1] == "inserted");
    v.erase(v.begin() + 1);
    assert(v.size() == 3);
    assert(v[1] == "beta");

    v.resize(5, "X");
    assert(v.size() == 5);
    assert(v[3] == "X" && v[4] == "X");

    v.pop_back();
    assert(v.size() == 4);

    my_vector<std::string> w = {"alpha", "beta", "gamma", "X"};
    assert(v == w);
    w.push_back("extra");
    assert(v < w);
    swap(v, w);
    assert(w.size() == 4);
    assert(v.size() == 5);

    std::cout << "my_vector tests passed\n";
}

void time_comparison_my_array() {
    constexpr size_t N = 1000000;

    std::array<int, N> std_arr{};
    my_array<int, N> my_arr{};

    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) std_arr[i] = int(i);
    long long sum1 = 0;
    for (size_t i = 0; i < N; ++i) sum1 += std_arr[i];
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) my_arr[i] = int(i);
    long long sum2 = 0;
    for (size_t i = 0; i < N; ++i) sum2 += my_arr[i];
    auto t4 = std::chrono::high_resolution_clock::now();

    auto dt_std = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto dt_my  = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "std::array: " << dt_std << " μs, sum=" << sum1 << "\n";
    std::cout << "my_array:  " << dt_my  << " μs, sum=" << sum2 << "\n\n";
}

void time_comparison_my_vector() {
    constexpr size_t N = 1000000;

    std::vector<int> std_vec;
    my_vector<int> my_vec;
    std_vec.reserve(N);
    my_vec.reserve(N);

    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) std_vec.push_back(int(i));
    long long sum1 = 0;
    for (auto x : std_vec) sum1 += x;
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) my_vec.push_back(int(i));
    long long sum2 = 0;
    for (auto x : my_vec) sum2 += x;
    auto t4 = std::chrono::high_resolution_clock::now();

    auto dt_std = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto dt_my  = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "std::vector: " << dt_std << " μs, sum=" << sum1 << "\n";
    std::cout << "my_vector:   " << dt_my  << " μs, sum=" << sum2 << "\n";
}

int main(int argc, char* argv[]) {
    std::cout << "= Testing functionality =\n";
    test_my_array();
    test_my_vector();
    std::cout << "All tests passed!" << std::endl;

    std::cout << "\n= Time comparison =\n";
    std::cout << "1. my_array:\n";
    time_comparison_my_array();
    std::cout << "1. my_vector:\n";
    time_comparison_my_vector();
    return 0;
}
