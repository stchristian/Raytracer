#include "Pinhole.h"
#include "Tracer.h"

Pinhole::Pinhole(Vec3f _eye, Vec3f _lookat, Vec3f _up)
    :Camera(_eye,_lookat,_up)
{ }

void Pinhole::render_scene(const World& world, Image& image) const
{
	Vec3f L;
	Ray ray;
	int depth = 0;

	const ViewPlane& vp       = world.view_plane;
	Sampler_ptr sampler = world.view_plane.get_sampler();
	
	Vec2f sp; //sample point
	Vec2f pp; //sample point on pixel

	ray.origin = eye;
	FLOAT_T pixel_size = vp.pixel_size / zoom;

	image.set_dimension(vp.width, vp.height);

	for (int y = 0; y < vp.height; y++)
	{
		for (int x = 0; x < vp.width; x++)
		{
			L = Vec3f(0); //Black 

			for (int j = 0; j < sampler->get_num_samples(); j++)
			{
				sp = sampler->sample_unit_square();
				pp = (Vec2f(x, y) - Vec2f(vp.width, vp.height) * 0.5 + sp) * pixel_size;

				ray.d = (x_cam * pp.x + y_cam * pp.y - z_cam * d).normalize();

				L += world.tracer->trace_ray(ray);
			}

			L /= sampler->get_num_samples();
			L *= exposure_time;
			image(x, y) = L;
		}
	}
}

void Pinhole::set_roll_angle(FLOAT_T angle)
{
	Mat3f rot(Mat3f::rotate(angle, lookat - eye));
	x_cam.multiply(rot);
	y_cam.multiply(rot);

	//Or we could do this, but slightly less efficient
	//up.multiply(rot);
	//compute_ONB();
}