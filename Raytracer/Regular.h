#pragma once
#include "Sampler.h"

class Regular: public Sampler {
public:
	Regular(void);							
	Regular(const int _num_samples);					

private:
	int sqrt_num_samples; //Number of samples per axis. 
	void generate_samples(void) override;
};

