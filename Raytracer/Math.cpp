#include "headers/math/Math.h"

bool solve_quadratic_equation(const FLOAT_T& a, const FLOAT_T& b, const FLOAT_T& c, FLOAT_T& x1, FLOAT_T& x2)
{
	FLOAT_T discr = b * b - 4 * a * c;
	if (discr < 0.0) return false;
	FLOAT_T sqrt_discr = sqrt(discr), denom = 2.0 * a;
	x1 = (-b - sqrt_discr) / denom; //The smaller if denom is > 0
	x2 = (-b + sqrt_discr) / denom;
	return true;
}