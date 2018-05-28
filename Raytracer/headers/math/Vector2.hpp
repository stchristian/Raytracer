#pragma once
#include <array>
#include <iostream>

template <class T>
class Vector2 {
public:
	union
	{
		struct
		{
			T x, y;
		};
		std::array<T, 2> arr;
	};

	Vector2() = default;
	Vector2(const T& _x, const T& _y) :x(_x), y(_y) {}
	Vector2(std::array<T, 2> _array) :arr(_a) {}
	Vector2(T value) { arr.fill(value); }

	Vector2 operator-(const Vector2& o) const { return Vector2(x - o.x, y - o.y); }
	Vector2 operator+(const Vector2& o) const { return Vector2(x + o.x, y + o.y); }
	Vector2 operator*(const Vector2& o) const { return Vector2(x * o.x, y * o.y); }
	Vector2 operator/(const Vector2& o) const { return Vector2(x / o.x, y / o.y); }

	T dot(const Vector2& o) const { return x * o.x + y * o.y; }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector)
{
	return os << "x: " << vector.x << " y: " << vector.y << std::endl;
}