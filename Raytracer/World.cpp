#include <chrono>

#include "World.h"
#include "Sphere.h"
#include "SimpleTracer.h"
#include "Pinhole.h"

World::~World()
{
	for (auto obj_ptr : objects)
	{
		delete obj_ptr;
	}
	if( tracer != nullptr )
		delete tracer;

	delete camera;
}

void World::build()
{
	view_plane.set_dimensions(512, 512, 1.0);
	view_plane.set_samples_per_pixel(1);

	tracer = new SimpleTracer(this);
	bg_color = Vec3f(0, 0, 0); //BLACK

	set_camera(new Pinhole(Vec3f(0, 0, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0)));
	camera->set_zoom(3.0);

	objects.push_back(new Sphere(Vec3f(0, 0, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(2, 0, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(-2, 0, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(0, 2, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(0, -2, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(6, 0, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(-6, 0, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(0, 6, 0), 0.75));
	objects.push_back(new Sphere(Vec3f(0, -6, 0), 0.75));
}

void World::render_scene(Image& image) const
{	
	
	using namespace std::chrono;
	high_resolution_clock::time_point tstart = high_resolution_clock::now();

	//ORTHOGONAL PROJECTION
	//Ray ray; 
	//ray.direction = Vec3f(0, 0, -1);
	//Vec2f samplePoint;
	//Vec2f res;
	//image.set_dimension(view_plane.width, view_plane.height);
	//Vec3f pixel_color;

	//Sampler_ptr sampler = view_plane.get_sampler();

	//for (int i = 0; i < view_plane.height; i++)
	//{
	//	for (int j = 0; j < view_plane.width; j++)
	//	{
	//		for (int k = 0; k < sampler->get_num_samples(); k++)
	//		{
	//			samplePoint = sampler->sample_unit_square();
	//			res.x = view_plane.pixel_size * (j - 0.5 * view_plane.width  + samplePoint.x);	
	//			res.y = view_plane.pixel_size * (i - 0.5 * view_plane.height + samplePoint.y);

	//			ray.o = Vec3f(res.x, res.y, 100);
	//			pixel_color += tracer->trace_ray(ray);
	//		}
	//		
	//		pixel_color /= sampler->get_num_samples(); //Averaging colors
	//		image(j, i) = pixel_color;
	//	}
	//}

	camera->render_scene(*this, image);

	high_resolution_clock::time_point tend = high_resolution_clock::now();
	duration<double, std::milli> time_span = tend - tstart;
	std::cout << "Scene rendered in " << time_span.count() << " ms" << std::endl;
}

void World::render_perspective(Image& image) const
{
	Vec3f pixel_color;
	Ray ray;

	Vec3f eye(0, 0, 5);
	FLOAT_T d = 140;
	ray.o = eye;

	image.set_dimension(view_plane.width, view_plane.height);

	for (int y = 0; y < view_plane.height; y++)
	{
		for (int x = 0; x < view_plane.width; x++)
		{
			ray.d = Vec3f(view_plane.pixel_size * (x - 0.5 * (view_plane.width - 1.0)), 
						  view_plane.pixel_size * (y - 0.5 * (view_plane.height - 1.0)), -d);
			
			ray.d.normalize();
			pixel_color = tracer->trace_ray(ray);
			image(x, y) = pixel_color;
		}
	}

}

ShadeRec World::hit_all_objects(const Ray& ray) const
{
	ShadeRec sr(*this);
	FLOAT_T tmin = std::numeric_limits<FLOAT_T>::max(), t;
	for (auto obj_ptr : objects)
	{
		if (obj_ptr->hit(ray, t, sr) && (t < tmin))
		{
			sr.hit_an_object = true;
			tmin = t;
			sr.color = obj_ptr->color;
		}
	}
	return sr;
}