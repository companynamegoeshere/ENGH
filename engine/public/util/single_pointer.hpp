#pragma once

#include <stdexcept>

namespace ENGH::Util {

template<typename T>
class TSinglePointer {
private:
    T *value;
public:

    TSinglePointer() : value(nullptr) {}

    explicit TSinglePointer(T *value) : value(value) {}

    TSinglePointer(const TSinglePointer<T> &other) = delete;

    TSinglePointer(TSinglePointer<T> &&other) noexcept : value(other.value) {
        other.value = nullptr;
    }

    TSinglePointer &operator=(T *value) {
        delete this->value;
        this->value = value;
        return *this;
    }

    T *operator*() {
        return value;
    }

    ~TSinglePointer() {
        delete this->value;
    }
};

}