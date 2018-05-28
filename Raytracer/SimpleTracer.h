#pragma once
#include "Tracer.h"

class SimpleTracer : public Tracer
{
public:
	SimpleTracer() = default;

	SimpleTracer(World *_world)
		:Tracer(_world)
	{}

	Vec3f trace_ray(const Ray& ray) const
	{
		ShadeRec sr(world->hit_all_objects(ray));

		if (sr.hit_an_object)
		{
			//SHADING STEP
			return sr.color; //FOR NOW JUST RETURN IT's color
		}
		else { 
			return world->bg_color; 
		}
	}
};