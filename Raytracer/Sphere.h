#ifndef SPHERE_H
#define SPHERE_H

#include "GeometricObject.h"

class Sphere : public GeometricObject
{
	Vec3f center;
	FLOAT_T radius;
public:
	Sphere(const Vec3f& _center, const FLOAT_T& _radius)
		: center(_center),
		radius(_radius)
	{ color = Vec3f(1,0,0); }

	bool hit(const Ray& ray, FLOAT_T& tmin, ShadeRec& shadeRec) const;
};
#endif // !SPHERE_H
