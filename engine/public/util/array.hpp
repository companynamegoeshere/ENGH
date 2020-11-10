#pragma once

#include <core/data_types.hpp>
#include <core/debug.hpp>
#include <util/memory.hpp>
#include <algorithm>
#include <vector>

namespace ENGH::Util {

template<typename T>
class TArray : public std::vector<T> {
public:

  TArray() : std::vector<T>() {
  }

  TArray(std::initializer_list<T> elements) : std::vector<T>(elements) {
  }

  uint16 length() const {
    return this->size();
  }

  constexpr void operator+=(T value) {
    this->push_back(value);
  }

  constexpr void operator+=(std::initializer_list<T> elements) {
    this->insert(this->end(), elements);
  }

  constexpr void Clear() {
    this->clear();
  }

  constexpr T& Last() {
    return static_cast<struct IndexData &>(this[this->size() - 1]);
  }

  constexpr const T& Last() const {
    return this[this->size() - 1];
  }
};

/*template<typename T>
class TArray {

  T *arr;
  uint16 len;
  uint16 cap;

public:

  constexpr TArray() :
      arr(nullptr),
      len(0),
      cap(0) {}

  TArray(std::initializer_list<T> elements) :
      arr(new T[elements.size()]),
      len(elements.size()),
      cap(elements.size()) {
    Memory::copy(elements.begin(), elements.end(), arr);
  }

  constexpr TArray(const TArray<T> &other) :
      arr(new T[other.len]),
      len(other.len),
      cap(other.cap) {
    Memory::copy(other.arr, arr, len);
  }

  constexpr TArray(TArray<T> &&other) noexcept :
      arr(other.arr),
      len(other.len),
      cap(other.cap) {
    other.arr = nullptr;
    other.len = other.cap = 0;
  }

  ~TArray() {
    delete arr;
  }

  constexpr inline T &operator[](uint16 index) const {
#ifdef ENGH_DEBUG
    if (index >= len) { // IndexOutOfBound Exception
      ENGH::Debug::Break();
    }
#endif
    return arr[index];
  }

  constexpr inline T operator[](uint16 index) {
#ifdef ENGH_DEBUG
    if (index >= len) { // IndexOutOfBound Exception
      ENGH::Debug::Break();
    }
#endif
    return arr[index];
  }

  constexpr inline uint16 length() const {
    return len;
  }

  constexpr inline uint16 capacity() const {
    return cap;
  }

  constexpr TArray &insert(T value) {
    if (len == cap) {
      reserve(1);
#ifdef ENGH_DEBUG
      if (arr == nullptr) { // OutOfMemory Exception
        ENGH::Debug::Break();
      }
#endif
    }
    arr[len++] = value;
    return *this;
  }

  constexpr void operator+=(T value) {
    this->insert(value);
  }

  TArray &reserve(uint16 size) {
    arr = reinterpret_cast<T *>(std::realloc(arr, sizeof(T) * (cap += size)));
    return *this;
  }

  constexpr inline const T *data() const {
    return arr;
  }

  constexpr inline T *data() {
    return arr;
  }

  constexpr inline void Clear() {
    this->len = 0;
  }

private:
  class Iterator {
    uint16 index;
    TArray<T> *target;
  public:
    Iterator(uint16 index, TArray<T> *target) : index(index), target(target) {}

    T &operator*() const {
      return (*target)[index];
    }

    T operator*() {
      return (*target)[index];
    }

    bool operator==(const Iterator &iter) const {
      return this->index == iter.index;
    }

    bool operator!=(const Iterator &iter) const {
      return this->index != iter.index;
    }

    Iterator &operator++() {
      index++;
      return *this;
    }
  };
public:

  constexpr Iterator begin() {
    return Iterator(0, this);
  }

  constexpr Iterator end() {
    return Iterator(this->len, this);
  }

};*/

}
