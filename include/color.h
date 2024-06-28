#pragma once
#include "interval.h"
#include "vecops.h"

using color = vec;

inline double linear_to_gamma(double linear_component) {
  if (linear_component > 0) {
    return sqrt(linear_component);
  }
  return 0;
}

void writePixel(std::ostream &out, color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // translate values in range of [0,1] into [0, 255]
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  static const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));
  out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}
