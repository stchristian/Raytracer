#pragma once
#include <vector>

#include "headers/math/Math.h"

/*This class generates num_samples 2d points in the unit square [0,1] x [0,1].
Sample points are organized in sets, so the total number (size) of point generated will be num_samples * num_sets.*/
class Sampler 
{
public:
	//Sample generation must be implemented in child class.
	virtual void generate_samples() = 0;

	void setup_shuffled_indices();
	Vec2f sample_unit_square();
	void shuffle_x_coordinates();
	void shuffle_y_coordinates();

	Sampler();
	Sampler(int _num_samples);
	Sampler(int _num_samples, int _num_sets);

	int get_num_samples() const { return num_samples; }
	void print_to_console() const;

protected:
	int num_samples;
	int num_sets;
	size_t size;
	std::vector<Vec2f> samples;
	std::vector<int> shuffled_indices;
	unsigned int count;
	int jump;
		
};