namespace ENGH::math {

template<typename T>
class TVec2 {
public:
    T x, y;

    TVec2();

    TVec2(const T &x, const T &y);

    TVec2(const TVec2<T> &other) = default;

    TVec2(TVec2<T> &&other) noexcept = default;

    TVec2<T> &operator+(const TVec2<T> &other) const;

    TVec2<T> &operator+=(const TVec2<T> &other);

    TVec2<T> &operator-(const TVec2<T> &other) const;

    TVec2<T> &operator-=(const TVec2<T> &other);

    TVec2<T> &operator*(const TVec2<T> &other) const;

    TVec2<T> &operator*=(const TVec2<T> &other);

    TVec2<T> &operator/(const TVec2<T> &other) const;

    TVec2<T> &operator/=(const TVec2<T> &other);
};

template<typename T>
TVec2<T>::TVec2() : x(0), y(0) {}

template<typename T>
TVec2<T>::TVec2(const T &x, const T &y) : x(x), y(y) {}

template<typename T>
TVec2<T> &TVec2<T>::operator+(const TVec2<T> &other) const {
    return TVec2<T>(x + other.x, y + other.y);
}

template<typename T>
TVec2<T> &TVec2<T>::operator-(const TVec2<T> &other) const {
    return TVec2<T>(x - other.x, y - other.y);
}

template<typename T>
TVec2<T> &TVec2<T>::operator*(const TVec2<T> &other) const {
    return TVec2<T>(x * other.x, y * other.y);
}

template<typename T>
TVec2<T> &TVec2<T>::operator/(const TVec2<T> &other) const {
    return TVec2<T>(x / other.x, y / other.y);
}

template<typename T>
TVec2<T> &TVec2<T>::operator+=(const TVec2<T> &other) {
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
TVec2<T> &TVec2<T>::operator-=(const TVec2<T> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
TVec2<T> &TVec2<T>::operator*=(const TVec2<T> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

template<typename T>
TVec2<T> &TVec2<T>::operator/=(const TVec2<T> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

using Vec2 = TVec2<float>;
using Vec2i = TVec2<int>;

}//namespace ends here


