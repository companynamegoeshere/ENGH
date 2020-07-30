#pragma once

namespace ENGH::SafeCast {

template<typename T, typename F>
inline constexpr T num(F f) {
  if (f > Number<T>::MAX) {
    return Number<T>::MAX;
  }
  if (f < Number<T>::MIN) {
    return Number<T>::MIN;
  }
  return static_cast<T>(f);
}

}
