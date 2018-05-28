#pragma once

#include <vector>

#include "GeometricObject.h"
#include "ViewPlane.h"
#include "Image.h"

class Tracer;
class Pinhole;

/*This class represents a world or a scene, that has objects in it. We can render an image of this world after we specified the camera.
The tracer determines the radiance for a specific ray.*/
class World {
private:
	Pinhole *camera;
public:
	ViewPlane view_plane;
	Vec3f bg_color;
	std::vector<GeometricObject*> objects;
	Tracer* tracer = nullptr;

	World() = default;
	~World();
	void build();
	void render_scene(Image& image) const;
	void render_perspective(Image& image) const;
	void set_camera(Pinhole *_camera);
	Pinhole* get_camera() { return camera; }
	void add_object(GeometricObject *object) { objects.push_back(object); }
	/*Maybe this function would make more sense in Tracer?*/
	ShadeRec hit_all_objects(const Ray& ray) const;
};

inline void World::set_camera(Pinhole *_camera) { camera = _camera; }
