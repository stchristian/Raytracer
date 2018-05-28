#ifndef SHADEREC_H
#define SHADEREC_H

#include "Math.h"

class World;

/*A class that stores all of the information that is needed to shade a ray object hit point.*/
class ShadeRec
{
public:
	bool hit_an_object;
	Vec3f hit_point;
	Vec3f normal;
	Vec3f color;
	const World& world;


	ShadeRec(const World& _world)
		: hit_an_object(false),
		hit_point(),
		normal(),
		world(_world)
	{}

	ShadeRec(const ShadeRec& shadeRec)
		:world(shadeRec.world),
		hit_an_object(shadeRec.hit_an_object),
		hit_point(shadeRec.hit_point),
		normal(shadeRec.normal),
		color(shadeRec.color)
	{}
};

#endif // !SHADEREC_H
