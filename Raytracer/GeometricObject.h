#ifndef GEOMETRICOBJECT_H
#define GEOMETRICOBJECT_H

#include "Ray.h"
#include "ShadeRec.h"

class GeometricObject
{
public:
	/*Intersect the ray with the object. 
	Returns true if intersects, if so the hit point will be ray.o + ray.dir * tmin.
	shadeRec must be filled with the shading information.*/
	virtual bool hit(const Ray& ray, FLOAT_T& tmin, ShadeRec& shadeRec) const = 0;
	Vec3f color;
protected:
	//TODO: Material
};
#endif // !GEOMETRICOBJECT_H
