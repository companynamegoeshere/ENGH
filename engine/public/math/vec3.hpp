namespace ENGH::Math {

	template <typename T>
	class TVec3 {
	public:
		T x, y, z;

		constexpr explicit TVec3(const T& value = 0);
		constexpr TVec3(const T& x, const T& y, const T& z);
		constexpr TVec3(const TVec3<T>& other) = default;
		constexpr TVec3(TVec3<T>&& other) = default;

		constexpr TVec3<T> operator+(const TVec3<T>& other) const;
		constexpr TVec3<T>& operator+=(const TVec3<T>& other);
		constexpr TVec3<T> operator-(const TVec3<T>& other) const;
		constexpr TVec3<T>& operator-=(const TVec3<T>& other);
		constexpr TVec3<T> operator*(const TVec3<T>& other) const;
		constexpr TVec3<T>& operator*=(const TVec3<T>& other);
		constexpr TVec3<T> operator/(const TVec3<T>& other) const;
		constexpr TVec3<T>& operator/=(const TVec3<T>& other);

		//Scale
		constexpr TVec3<T> operator+(const T& other) const;
		constexpr TVec3<T>& operator+=(const T& other);
		constexpr TVec3<T> operator-(const T& other) const;
		constexpr TVec3<T>& operator-=(const T& other);
		constexpr TVec3<T> operator*(const T& other) const;
		constexpr TVec3<T>& operator*=(const T& other);
		constexpr TVec3<T> operator/(const T& other) const;
		constexpr TVec3<T>& operator/=(const T& other);
	};

	template <typename T>
	constexpr TVec3<T>::TVec3(const T& value) : x(value), y(value), z(value) {}

	template <typename T>
	constexpr TVec3<T>::TVec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator+(const TVec3<T>& other) const {
		return TVec3<T>(x + other.x, y + other.y, z + other.z);
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator-(const TVec3<T> & other) const {
		return TVec3<T>(x - other.x, y - other.y, z - other.z);
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator*(const TVec3<T> & other) const {
		return TVec3<T>(x * other.x, y * other.y, z * other.z);
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator/(const TVec3<T> & other) const {
		return TVec3<T>(x / other.x, y / other.y, z / other.z);
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator+=(const TVec3<T> & other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator-=(const TVec3<T> & other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator*=(const TVec3<T> & other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator/=(const TVec3<T> & other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator+(const T & other) const {
		return TVec3<T>(x + other, y + other, z + other);
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator+=(const T & other) {
		x += other;
		y += other;
		z += other;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator-(const T & other) const {
		return TVec3<T>(x - other, y - other, z - other);
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator-=(const T & other) {
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator*(const T & other) const {
		return TVec3<T>(x * other, y * other, z * other);
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator*=(const T & other) {
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	template<typename T>
	constexpr TVec3<T> TVec3<T>::operator/(const T & other) const {
		return TVec3<T>(x / other, y / other, z / other);
	}

	template<typename T>
	constexpr TVec3<T>& TVec3<T>::operator/=(const T & other) {
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	using Vec3 = TVec3<float>;
	using Vec3i = TVec3<int>;

}// namespace ends here