#pragma once
#include <array>
#include <iostream>

template <class T>
class Vector4 {
public:
	union
	{
		struct 
		{
			T x, y, z, w;
		};
		std::array<T, 4> arr;
	};

	Vector4() = default;

	Vector4(const T& _x, const T& _y, const T& _z, const T& _w) :x(_x), y(_y), z(_z), w(_w) {}

	Vector4(std::array<T, 4> _array) :arr(_a) {}

	Vector4(T value) { arr.fill(value); }

	Vector4 operator-(const Vector4& o) { return Vector4(x - o.x, y - o.y, z - o.z, w - o.w); }
	Vector4 operator+(const Vector4& o) { return Vector4(x + o.x, y + o.y, z + o.z, w + o.w); }
	Vector4 operator*(const Vector4& o) { return Vector4(x * o.x, y * o.y, z * o.z, w * o.w); }
	Vector4 operator/(const Vector4& o) { return Vector4(x / o.x, y / o.y, z / o.z, w / o.w); }


};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector4<T>& vector)
{
	return os << "x: " << vector.x << " y: " << vector.y << " z: " << vector.z << " w: " << vector.w << std::endl;
}