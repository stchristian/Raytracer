#pragma once

#include <iomanip>
#include <utility>

#include "Vector3.hpp"

template <class T>
class Mat3
{
public:
	union
	{
		T m[3][3];
		Vector3<T> v[3];
	};


	Mat3(T e00, T e01, T e02,
		 T e10, T e11, T e12,
		 T e20, T e21, T e22)
		: m{{e00, e01, e02},
			{e10, e11, e12},
			{e20, e21, e22}}
	{ }

	Mat3(Vector3<T> v0, Vector3<T> v1, Vector3<T> v2)
		:v{ v0, v1, v2 }
	{ }

	static Mat3 identity()
	{
		return Mat3(1, 0, 0,
				    0, 1, 0,
				    0, 0, 1);
	}

	static Mat3 rotate(T angle, Vector3<T> w)
	{
		T c = cos(angle), s = sin(angle);
		w.normalize();
		return Mat3(c * (1 - w.x*w.x) + w.x*w.x, w.x*w.y*(1 - c) + w.z*s, w.x*w.z*(1 - c) - w.y*s,
			          w.x*w.y*(1 - c) - w.z*s, c * (1 - w.y*w.y) + w.y*w.y, w.y*w.z*(1 - c) + w.x*s,
			          w.x*w.z*(1 - c) + w.y*s, w.y*w.z*(1 - c) - w.x*s, c * (1 - w.z*w.z) + w.z*w.z);
	}

	static Mat3 rotate_x(T angle)
	{
		T c = cos(angle), s = sin(angle);
		return Mat3(1, 0, 0,
					0, c, s,
					0, -s, c);
	}

	static Mat3 rotate_y(T angle)
	{
		T c = cos(angle), s = sin(angle);
		return Mat3(c, 0, -s,
					0, 1, 0,
					s, 0, c);
	}

	static Mat3 rotate_z(T angle)
	{
		T c = cos(angle), s = sin(angle);
		return Mat3(c, s, 0,
					-s, c, 0,
					0, 0, 1);
	}

	void transpose()
	{
		using namespace std;
		swap(m[0][1], m[1][0]);
		swap(m[2][0], m[0][2]);
		swap(m[1][2], m[2][1]);
	}

	Mat3& multiply(const Mat3& o)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				T res = 0;
				for (int k = 0; k < 3; k++)
				{
					res += v[i][k] * o.v[k][j];
				}
				m[i][j] = res;
			}
		}
		return *this;
	}

};

template <class T>
std::ostream& operator<<(std::ostream& os, const Mat3<T>& matrix)
{	
	os << std::right << std::setprecision(4) << std::fixed;
	for (int i = 0; i < 3; i++)
		os << std::setw(10) << matrix.v[i].x << " " <<
			  std::setw(10) << matrix.v[i].y << " " <<
		      std::setw(10) << matrix.v[i].z << std::endl;
	return os;
}

template<class T>
inline Vector3<T>& Vector3<T>::multiply(const Mat3<T>& o)
{
	Vector3<T> old(*this);
	x = old.x * o.m[0][0] + old.y * o.m[1][0] + old.z * o.m[2][0];
	y = old.x * o.m[0][1] + old.y * o.m[1][1] + old.z * o.m[2][1];
	z = old.x * o.m[0][2] + old.y * o.m[1][2] + old.z * o.m[2][2];
	return *this;
}