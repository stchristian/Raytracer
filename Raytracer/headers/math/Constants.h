#pragma once

#include <cstdlib>
//So that we can switch to double/float.
using FLOAT_T = float;
//Constants
const FLOAT_T K_EPSILON = 1e-6;
const FLOAT_T INV_RAND_MAX = 1.0 / (FLOAT_T)RAND_MAX;