#include "../include/color.h"

void writeColor(std::ostream &out, color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // translate values in range of [0,1] into [0, 255]
  int rbyte = int(r * 255.999);
  int gbyte = int(g * 255.999);
  int bbyte = int(b * 255.999);
  out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}
