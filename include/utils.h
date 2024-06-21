#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Using;

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
double degree_to_radians(double degree) { return (degree * pi / 180.0); }
inline double abs(double a) { return (a >= 0) ? a : -a; }

// common headers
#include "color.h"
#include "ray.h"
#include "vecops.h"
