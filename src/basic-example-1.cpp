#include "../include/color.h"
#include "../include/ray.h"
#include "../include/vecops.h"

#include <fstream>
#include <iostream>

#define IMAGEWIDTH 255
#define IMAGEHEIGHT 255

int main() {
  // Open a file image.ppm
  std::ofstream myfile;
  myfile.open("image.ppm");

  // Render
  myfile << "P3\n" << IMAGEWIDTH << ' ' << IMAGEHEIGHT << "\n255\n";
  for (double j = 0; j < IMAGEHEIGHT; j++) {
    std::clog << "\rScanlines remaining: " << IMAGEHEIGHT - j << ' '
              << std::flush;
    for (double i = 0; i < IMAGEWIDTH; i++) {
      color pixel = color(i / IMAGEHEIGHT, j / IMAGEWIDTH, 0);
      writePixel(myfile, pixel);
    }
    myfile << '\n';
  }
  myfile.close();
  std::clog << "\rDone. \n";
  vec t = vec(1, 1, 1);
  point x = point();

  ray beam = ray(x, t);
  std::cout << beam.at(10);
}
