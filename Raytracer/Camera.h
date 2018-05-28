#pragma once
#include "Math.h"
#include "World.h"

class Camera
{
public:
	Camera(Vec3f _eye, Vec3f _lookat, Vec3f _up);

	void compute_ONB(); //compute orthonormal basis
	virtual void render_scene(const World& w, Image& image) const = 0;
	void set_roll_angle(FLOAT_T angle);

protected:
	Vec3f eye, lookat, up;
	Vec3f x_cam, y_cam, z_cam; //The orthonormal basis of the cameras coordinate system
	FLOAT_T exposure_time = 1.0;

};