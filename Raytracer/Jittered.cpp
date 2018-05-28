#include "Jittered.h"

void Jittered::generate_samples()
{
    for(int p = 0; p < num_sets; p++)
    {
        for(int j = 0; j < sqrt_num_samples; j++)
        {
            for(int k = 0; k < sqrt_num_samples; k++)
            {
                samples.push_back(Vec2f( (k + RandUtility::rand_float()) / sqrt_num_samples, 
                                         (j + RandUtility::rand_float()) / sqrt_num_samples) );
            }   
        }
    }
}

Jittered::Jittered(void)
	: Sampler(),
	sqrt_num_samples((int)sqrt(num_samples))
{
	generate_samples();
}
Jittered::Jittered(const int _num_samples)
	: Sampler(pow((int)sqrt(_num_samples), 2)),
	sqrt_num_samples((int)sqrt(_num_samples))
{
	generate_samples();
}

Jittered::Jittered(const int _num_samples, const int _num_sets)
	: Sampler(pow((int)sqrt(_num_samples),2), _num_sets),
	sqrt_num_samples((int)sqrt(_num_samples))
{
	generate_samples();
}