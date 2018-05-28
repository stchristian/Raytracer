#pragma once

#include <cmath>


#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Mat3.hpp"
#include "RandUtility.h"

using Vec2f = Vector2<FLOAT_T>;
using Vec3f = Vector3<FLOAT_T>;
using Vec4f = Vector4<FLOAT_T>;
using Mat3f = Mat3<FLOAT_T>;

bool solve_quadratic_equation(const FLOAT_T& a, const FLOAT_T& b, const FLOAT_T& c, FLOAT_T& x1, FLOAT_T& x2);


