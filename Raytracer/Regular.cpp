#include "Regular.h"

Regular::Regular(void)							
	: Sampler(),
	sqrt_num_samples((int)sqrt(num_samples))
{}

Regular::Regular(const int _num_samples)
	: Sampler(pow((int)sqrt(_num_samples), 2)),
	sqrt_num_samples((int)sqrt(_num_samples))
{
	generate_samples();
}

void Regular::generate_samples(void) {
	for (int j = 0; j < num_sets; j++)
		for (int p = 0; p < sqrt_num_samples; p++)		
			for (int q = 0; q < sqrt_num_samples; q++)
				samples.push_back(Vec2f((q + 0.5) / sqrt_num_samples, (p + 0.5) / sqrt_num_samples));
}
