#ifndef RAY_H
#define RAY_H


#include "headers/math/Math.h"

class Ray
{
public:
	union {
		struct {
			Vec3f origin, direction;
		};
		struct {
			Vec3f o, d;
		};
	};

	//For optimization purposes
	int sign[3];
	Vec3f invdir;

	Ray() = default;
	Ray(const Vec3f& o, const Vec3f& d) :origin(o), direction(d) {
		invdir = Vec3f(1) / d;
		sign[0] = (invdir.x < 0);
		sign[1] = (invdir.y < 0);
		sign[2] = (invdir.z < 0);
	}
};
#endif // !RAY_H
