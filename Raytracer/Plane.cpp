#include "Plane.h"

bool Plane::hit(const Ray& ray, FLOAT_T& tmin, ShadeRec& shadeRec) const
{
	FLOAT_T t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
	if (isinf(t))
		return false;

	if (t > K_EPSILON)
	{
		tmin = t;
		shadeRec.normal = normal;
		shadeRec.hit_point = ray.origin + ray.direction * t;
		return true;
	}
	else
	{
		return false;
	}
}