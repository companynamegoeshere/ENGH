#pragma once

#include <stdexcept>

namespace ENGH::Util {

template<typename T>
class SinglePointer {
private:
    T *value;
public:

    SinglePointer() : value(nullptr) {}

    explicit SinglePointer(T *value) : value(value) {}

    SinglePointer(const SinglePointer<T> &other) = delete;

    SinglePointer(SinglePointer<T> &&other) noexcept : value(other.value) {
        other.value = nullptr;
    }

    SinglePointer &operator=(T *value) {
        delete this->value;
        this->value = value;
        return *this;
    }

    T *operator*() {
        return value;
    }

    ~SinglePointer() {
        delete this->value;
    }
};

}