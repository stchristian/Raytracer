#pragma once
#include "Sampler.h"

class Jittered : public Sampler
{
public:
	Jittered(void);
	Jittered(const int num_samples);
	Jittered(const int _num_samples, const int _num_sets);

private:
	int sqrt_num_samples; //Number of samples per axis. 
    void generate_samples() override;
};