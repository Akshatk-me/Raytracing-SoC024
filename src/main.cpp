#include <iostream>

#define IMAGEWIDTH 255
#define IMAGEHEIGHT 255

void printPixel(int r, int g, int b);

int main() {
  // Render
  std::cout << "P3\n" << IMAGEWIDTH << ' ' << IMAGEHEIGHT << "\n255\n";

  for (int j = 0; j < IMAGEHEIGHT; j++) {
    for (int i = 0; i < IMAGEWIDTH; i++) {
      printPixel(int(float(i) / IMAGEWIDTH * 256),
                 int(float(j) / IMAGEHEIGHT * 256), 0);
    }
    std::cout << '\n';
  }
}

void printPixel(int r, int g, int b) {
  // prints in the format r g b .
  std::cout << r << ' ' << g << ' ' << b << ' ';
}
