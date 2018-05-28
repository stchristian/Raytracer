#pragma once

#include "Camera.h"

class Pinhole : public Camera 
{
public:
    Pinhole(Vec3f _eye, Vec3f _lookat, Vec3f _up);

    void render_scene(const World& world, Image& image) const override;
	void set_zoom(FLOAT_T _zoom);
	void set_roll_angle(FLOAT_T angle);

private:
	FLOAT_T d = 140;
	FLOAT_T zoom = 1.0;
};

inline void Pinhole::set_zoom(FLOAT_T _zoom) { zoom = _zoom; }