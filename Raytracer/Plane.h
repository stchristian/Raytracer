#ifndef PLANE_H
#define PLANE_H

#include "GeometricObject.h"

class Plane : public GeometricObject
{
	Vec3f point, normal;
public:
	Plane(const Vec3f& _point, const Vec3f& _normal)
		: point(_point),
		normal(_normal)
	{}

	bool hit(const Ray& ray, FLOAT_T& tmin, ShadeRec& shadeRec) const;
};
#endif // !PLANE_H
