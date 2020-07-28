#pragma once
#include <cstdint>
#include <limits>

namespace ENGH {

template<typename T>
class Number {
  using ref = std::numeric_limits<T>;
public:
  using type = T;
  static constexpr T MAX = ref::max();
  static constexpr T MIN = ref::min();
  static constexpr bool SIGNED = ref::is_signed;
  static constexpr bool INTEGER = ref::is_integer;
  static constexpr int DIGITS = ref::digits;
  static constexpr size_t SIZE = sizeof(T);
};

typedef int8_t byte;
using Byte = Number<byte>;

typedef uint8_t ubyte;
using UByte = Number<byte>;

typedef int16_t int16;
using Int16 = Number<int16>;

typedef uint16_t uint16;
using UInt16 = Number<uint16>;

typedef int32_t int32;
using Int32 = Number<int32>;

typedef uint32_t uint32;
using UInt32 = Number<uint32>;

typedef int64_t int64;
using Int64 = Number<int64>;

typedef uint64_t uint64;
using UInt64 = Number<uint64>;

using Int = Number<int>;

using Float = Number<float>;
using Double = Number<double>;

typedef unsigned int uint;
using UInt = Number<uint>;

}
