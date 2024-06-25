#pragma once
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Using;

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

// beware that interval.h has different implementation for infinity
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degree_to_radians(double degree) { return (degree * pi / 180.0); }
inline double abs(double a) { return (a >= 0) ? a : -a; }

inline double random_double() {
  // Returns a random real number in [0,1)
  // Why 1.0 ? why not something else?
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  // Returns a random real number in [min, max)
  return min + (max - min) * random_double();
}
