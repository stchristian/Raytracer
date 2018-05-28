#pragma once
#include "Math.h"
#include "Ray.h"

class BoundingBox {
public:
	union {
		struct {
			Vec3f min, max;
		};
		Vec3f bounds[2];
	};

	BoundingBox() = default;
	BoundingBox(const Vec3f& _min, const Vec3f& _max) :min(_min), max(_max) {}

	//Copy & paste from: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	bool Hit(const Ray& r)
	{
		FLOAT_T tmin, tmax, tymin, tymax, tzmin, tzmax;

		tmin = (bounds[r.sign[0]].x - r.o.x) * r.invdir.x;
		tmax = (bounds[1 - r.sign[0]].x - r.o.x) * r.invdir.x;
		tymin = (bounds[r.sign[1]].y - r.o.y) * r.invdir.y;
		tymax = (bounds[1 - r.sign[1]].y - r.o.y) * r.invdir.y;

		if ((tmin > tymax) || (tymin > tmax))
			return false;
		if (tymin > tmin)
			tmin = tymin;
		if (tymax < tmax)
			tmax = tymax;

		tzmin = (bounds[r.sign[2]].z - r.o.z) * r.invdir.z;
		tzmax = (bounds[1 - r.sign[2]].z - r.o.z) * r.invdir.z;

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;
		if (tzmin > tmin)
			tmin = tzmin;
		if (tzmax < tmax)
			tmax = tzmax;

		return true;
	}
};