#pragma once

#include "headers/math/Math.h"
#include "Sampler.h"
#include "Jittered.h"
#include "Regular.h"

#include <memory>

typedef std::shared_ptr<Sampler> Sampler_ptr;

class ViewPlane
{
	Sampler_ptr sampler_ptr; //Smart pointer

public:
	int width, height;    //PRIVATE
	FLOAT_T pixel_size;	  //PRIVATE

	ViewPlane() = default;
	ViewPlane(int _width, int _height, FLOAT_T _pixel_size);
	ViewPlane(const ViewPlane& other);
	~ViewPlane();

	void set_sampler(Sampler_ptr _sampler_ptr);
	Sampler_ptr get_sampler() const; 
	void set_samples_per_pixel(const int n);
	int get_samples_per_pixel() const;
	void set_dimensions(int _width, int _height, FLOAT_T _pixel_size);
};

inline void ViewPlane::set_sampler(Sampler_ptr _sampler_ptr)
{
	sampler_ptr = _sampler_ptr;
}

inline Sampler_ptr ViewPlane::get_sampler() const
{
	return sampler_ptr;
}

inline int ViewPlane::get_samples_per_pixel() const
{
	sampler_ptr->get_num_samples();
}

inline void ViewPlane::set_dimensions(int _width, int _height, FLOAT_T _pixel_size)
{
	width = _width; height = _height; pixel_size = _pixel_size;
}
