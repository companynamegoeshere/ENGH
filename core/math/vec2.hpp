namespace ENGH::math {

template <typename T>
class Vec2 {
public:
	T x, y;
	Vec2();
	Vec2(const T &x, const T &y);
	// Vec2(const Vec2<T>& other);

	Vec2<T>& operator+(const Vec2<T> &other) const;
	Vec2<T>& operator+=(const Vec2<T> &other);
	Vec2<T>& operator-(const Vec2<T> &other) const;
	Vec2<T>& operator-=(const Vec2<T> &other);
	Vec2<T>& operator*(const Vec2<T> &other) const;
	Vec2<T>& operator*=(const Vec2<T> &other);
	Vec2<T>& operator/(const Vec2<T> &other) const;
	Vec2<T>& operator/=(const Vec2<T> &other);
};

template <typename T>
Vec2<T>::Vec2() : x(0), y(0) {}

template <typename T>
Vec2<T>::Vec2(const T &x, const T &y) : x(x), y(y) {}

/* template <typename T>
Vec2<T>::Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {} */

template<typename T>
Vec2<T>& Vec2<T>::operator+(const Vec2<T> &other) const {
	return Vec2<T> (x + other.x, y + other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator-(const Vec2<T> &other) const {
	return Vec2<T>(x - other.x, y - other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator*(const Vec2<T> &other) const {
	return Vec2<T>(x * other.x, y * other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator/(const Vec2<T> &other) const {
	return Vec2<T>(x / other.x, y / other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T> &other) {
	x += other.x;
	y += other.y;
	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T> &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator*=(const Vec2<T> &other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator/=(const Vec2<T> &other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

}//namespace ends here


