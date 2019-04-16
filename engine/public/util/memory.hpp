#pragma once

#include <core/data_types.hpp>

namespace ENGH::Util::Memory {

template<typename T>
constexpr inline void copy(const T *begin, const T *end, T *target) {
    while (begin != end) {
        *target = *begin;
        ++begin;
        ++target;
    }
}

template<typename T, typename R>
constexpr inline void copy(const T *begin, T *target, R len) {
    copy(begin, begin + len, target);
}

}