#pragma once
#include "interval.h"
#include "vecops.h"

using color = vec;

void writePixel(std::ostream &out, color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // translate values in range of [0,1] into [0, 255]

  static const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));
  out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}
