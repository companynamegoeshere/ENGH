#pragma once

namespace ENGH::Math {

template<typename T>
class TVec2 {
public:
  T x, y;

  constexpr explicit TVec2(const T &value = 0);
  constexpr TVec2(const T &x, const T &y);
  constexpr TVec2(const TVec2<T>& other) = default;
  constexpr TVec2(TVec2<T>&& other) noexcept = default;

  constexpr TVec2<T> operator+(const TVec2<T>& other) const;
  constexpr TVec2<T>& operator+=(const TVec2<T>& other);
  constexpr TVec2<T> operator-(const TVec2<T>& other) const;
  constexpr TVec2<T>& operator-=(const TVec2<T>& other);
  constexpr TVec2<T> operator*(const TVec2<T>& other) const;
  constexpr TVec2<T>& operator*=(const TVec2<T>& other);
  constexpr TVec2<T> operator/(const TVec2<T>& other) const;
  constexpr TVec2<T>& operator/=(const TVec2<T>& other);

  //Scale
  constexpr TVec2<T>& operator+(const T& other) const;
  constexpr TVec2<T>& operator+=(const T& other);
  constexpr TVec2<T>& operator-(const T& other) const;
  constexpr TVec2<T>& operator-=(const T& other);
  constexpr TVec2<T>& operator*(const T& other) const;
  constexpr TVec2<T>& operator*=(const T& other);
  constexpr TVec2<T>& operator/(const T& other) const;
  constexpr TVec2<T>& operator/=(const T& other);
};

template<typename T>
constexpr TVec2<T>::TVec2(const T& value) : x(value), y(value) {}

template<typename T>
constexpr TVec2<T>::TVec2(const T& x, const T& y) : x(x), y(y) {}

template<typename T>
constexpr TVec2<T> TVec2<T>::operator+(const TVec2<T>& other) const {
  return TVec2<T>(x + other.x, y + other.y);
}

template<typename T>
constexpr TVec2<T> TVec2<T>::operator-(const TVec2<T> & other) const {
  return TVec2<T>(x - other.x, y - other.y);
}

template<typename T>
constexpr TVec2<T> TVec2<T>::operator*(const TVec2<T> & other) const {
  return TVec2<T>(x * other.x, y * other.y);
}

template<typename T>
constexpr TVec2<T> TVec2<T>::operator/(const TVec2<T> & other) const {
  return TVec2<T>(x / other.x, y / other.y);
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator+=(const TVec2<T> & other) {
  x += other.x;
  y += other.y;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator-=(const TVec2<T> & other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator*=(const TVec2<T> & other) {
  x *= other.x;
  y *= other.y;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator/=(const TVec2<T> & other) {
  x /= other.x;
  y /= other.y;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator+(const T& other) const {
  return TVec2<T>(x + other, y + other);
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator+=(const T & other) {
  x += other;
  y += other;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator-(const T & other) const {
  return TVec2<T>(x - other, y - other);
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator-=(const T & other) {
  x -= other;
  y -= other;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator*(const T & other) const {
  return TVec2<T>(x * other, y * other);
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator*=(const T & other) {
  x *= other;
  y *= other;
  return *this;
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator/(const T & other) const {
  return TVec2<T>(x / other, y / other);
}

template<typename T>
constexpr TVec2<T>& TVec2<T>::operator/=(const T & other) {
  x /= other;
  y /= other;
  return *this;
}

using Vec2 = TVec2<float>;
using Vec2i = TVec2<int>;

}//namespace ends here


