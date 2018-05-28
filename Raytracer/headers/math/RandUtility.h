#pragma once
#include "Constants.h"

class RandUtility
{
	static unsigned int seed;
public:
	static void set_seed(const unsigned int _seed) { seed = _seed; srand(seed); }
	static int rand_int() { return rand(); }
	static float rand_float() { return rand() * INV_RAND_MAX; }
};

