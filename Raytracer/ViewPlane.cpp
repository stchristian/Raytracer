#include "ViewPlane.h"

ViewPlane::ViewPlane(int _width, int _height, FLOAT_T _pixel_size)
	: width(_width), height(_height),
	pixel_size(_pixel_size)
{ }

ViewPlane::ViewPlane(const ViewPlane& other)
	: width(other.width), height(other.height), pixel_size(other.pixel_size), sampler_ptr(other.get_sampler())
{ }

ViewPlane::~ViewPlane()
{ }

void ViewPlane::set_samples_per_pixel(const int n)
{
	if (n > 1) sampler_ptr = std::make_shared<Jittered>(n);
	if (n == 1) sampler_ptr = std::make_shared<Regular>(1);
}