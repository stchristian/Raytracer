#pragma once

#include <chrono>
#include <iostream>

#define MEASURE_CODE_SPEED(CODE)										 \
using namespace std::chrono;											 \
high_resolution_clock::time_point tstart = high_resolution_clock::now(); \
CODE																	 \
high_resolution_clock::time_point tend = high_resolution_clock::now();   \
duration<double, std::micro> time_span = tend - tstart;                  \
std::cout << "The code executed in " << time_span.count() << " microseconds" << std::endl;