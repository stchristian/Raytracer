#pragma once
#include "World.h"

/*Trace a ray in the world, and determine the color that the ray hits. Child classes can override the trace_ray function.*/
class Tracer {
protected:
	World* world = nullptr;
public:
	Tracer() = default;

	Tracer(World* _world)
		:world(_world)
	{}

	virtual Vec3f trace_ray(const Ray& ray) const;
};