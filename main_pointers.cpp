//
// Created by denhumen on 4/24/25.
//

#include <iostream>
#include "my_unique_ptr.h"
#include "my_shared_ptr.h"
#include "my_weak_ptr.h"

struct Car {
    std::string model;

    explicit Car(std::string n) : model(std::move(n)) {
        std::cout << "Car " << model << " created" << std::endl;
    }
    ~Car() {
        std::cout << "Car " << model << " destroyed" << std::endl;
    }
};

void test_my_unique_ptr() {
    std::cout << "= Testing my_unique_ptr =\n";
    my_unique_ptr ptr1(new Car("Audi"));
    std::cout << "Ptr1 name: " << ptr1->model << std::endl;

    my_unique_ptr<Car> ptr2 = std::move(ptr1);
    std::cout << "";
    std::cout << "Ptr1 validation:  " << static_cast<bool>(ptr1) << std::endl;
    std::cout << "Ptr2 name: " << ptr2->model << std::endl;

    ptr2.reset(new Car("Mercedes"));
    std::cout << "Ptr2 name: " << ptr2->model << std::endl;

    ptr2.release();
    std::cout << "Ptr2 validation: " << static_cast<bool>(ptr2) << std::endl;
}

void test_my_shared_ptr() {
    std::cout << "\n= Testing my_shared_ptr =\n";
    my_shared_ptr a(new Car("Porsche"));
    std::cout << "First use_count(): " << a.use_count() << std::endl;

    const my_shared_ptr<Car> b = a;
    std::cout << "Second use_count(): " << b.use_count() << std::endl;
    std::cout << "Second model " << b->model << std::endl;

    std::cout << "After second is destroyed, first use_count(): " << a.use_count() << std::endl;

    a.reset();
}

void test_my_weak_ptr() {
    std::cout << "\n= Testing my_weak_ptr =\n";
    my_shared_ptr shared(new Car("Skoda"));
    const my_weak_ptr weak(shared);

    std::cout << "Car use_count before lock: " << shared.use_count() << std::endl;
    if (const auto locked = weak.lock()) {
        std::cout << "locked car: " << locked->model << std::endl;
    }

    shared.reset();

    std::cout << "After reset, trying to lock again:\n";
    if (const auto locked = weak.lock()) {
        std::cout << "Still alive: " << locked->model << std::endl;
    } else {
        std::cout << "Object destroyed" << std::endl;
    }
}

int main() {
    test_my_unique_ptr();
    test_my_shared_ptr();
    test_my_weak_ptr();

    return 0;
}