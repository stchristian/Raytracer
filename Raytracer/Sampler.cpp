#include "Sampler.h"
#include <algorithm>
#include <iostream>

Sampler::Sampler()
	: num_samples(1),
	num_sets(83),
	size(num_samples * num_sets),
	count(0),
	jump(0)
{
	samples.reserve(size);
	shuffled_indices.reserve(size);
	setup_shuffled_indices();
}

Sampler::Sampler(int _num_samples)
	:num_samples(_num_samples),
	num_sets(83),
	size(num_samples * num_sets),
	count(0),
	jump(0)
{
	samples.reserve(size);
	shuffled_indices.reserve(size);
	setup_shuffled_indices();
}

Sampler::Sampler(int _num_samples, int _num_sets)
	:num_samples(_num_samples),
	num_sets(_num_sets),
	size(num_samples * num_sets)
{
	samples.reserve(size);
	shuffled_indices.reserve(size);
	setup_shuffled_indices();
}

void Sampler::setup_shuffled_indices()
{
	std::vector<int> indices(num_samples);
	for (int i = 0; i < num_samples; i++)
		indices.push_back(i);

	for (int p = 0; p < num_sets; p++) {
		std::random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);
	}
}

Vec2f Sampler::sample_unit_square() {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (RandUtility::rand_int() % num_sets) * num_samples;				// random index jump initialised to zero in constructor

	return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

void Sampler::print_to_console() const
{	
	std::cout << "Total size: " << size << " samples" << std::endl;
	for(int p = 0; p < num_sets; p++)
    {
		std::cout << std::endl << p << ". set" << std::endl;
        for(int j = 0; j < num_samples; j++)
        {
			std::cout << samples.at(num_samples * p + j);
        }
    }	
}

// shuffle_x_coordinates
// shuffle the x coordinates of the points within each set
void Sampler::shuffle_x_coordinates(void) {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < num_samples - 1; i++) {
			int target = RandUtility::rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}


// shuffle_y_coordinates
// shuffle the y coordinates of the points within set
void Sampler::shuffle_y_coordinates(void) {
	for (int p = 0; p < num_sets; p++)
		for (int i = 0; i < num_samples - 1; i++) {
			int target = RandUtility::rand_int() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
}