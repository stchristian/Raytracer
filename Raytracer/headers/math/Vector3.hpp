#pragma once
#include <array>
#include <iostream>


template <class T> 
class Mat3;

template <class T>
class Vector3 {
public:
	union
	{
		struct
		{
			T x, y, z;
		};
		std::array<T, 3> arr;
	};

	Vector3() = default;
	Vector3(const T& _x, const T& _y, const T& _z) :x(_x), y(_y), z(_z) {}
	Vector3(std::array<T, 3> _array) :arr(_a) {}
	Vector3(T value) { arr.fill(value); }

	Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
	Vector3 operator+(const Vector3& o) const { return Vector3(x + o.x, y + o.y, z + o.z); }
	Vector3 operator*(const Vector3& o) const { return Vector3(x * o.x, y * o.y, z * o.z); }
	Vector3 operator/(const Vector3& o) const { return Vector3(x / o.x, y / o.y, z / o.z); }

	Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
	Vector3& operator-=(const Vector3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
	Vector3& operator/=(const Vector3& o) { x /= o.x; y /= o.y; z /= o.z; return *this; }
	Vector3& operator*=(const Vector3& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }

	T& operator[](int index) { return arr[index]; }
	T operator[](int index) const { return arr[index]; }

	Vector3& multiply(const Mat3<T>& o);

	Vector3& normalize() { return *this /= length(); }
	Vector3 cross(const Vector3& o) { return Vector3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x); }
	T length() { return sqrt(x * x + y * y + z * z); }

	T dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& vector)
{
	return os << "x: " << vector.x << " y: " << vector.y << " z: " << vector.z << std::endl;
}