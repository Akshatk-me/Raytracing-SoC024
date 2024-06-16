#include "../include/color.h"
#include "../include/ray.h"
#include "../include/vecops.h"

#include <fstream>
#include <iostream>

inline double abs(double a) {
  if (a >= 0) {
    return a;
  } else {
    return -a;
  }
}

color ray_color(const ray &t) {
  auto x = t.getDirection().direction();
  x = vec(abs(x.x()), abs(x.y()), abs(x.z()));
  std::cout << x;
  return x;
}

int main() {
  double aspect_ratio = 16.0 / 9.0; // width/height
  int image_width = 400;

  // define image height, ensure >= 1;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  // calculate viewport_width based on actual image_height and image_width;
  double viewport_height = 4.0; // specified in some actual distance unit
  double viewport_width =
      viewport_height * (double(image_width) / image_height);
  double focalLength = 1.0;
  point camera_center = point(0, 0, 0);

  // Calculate vectors across veiwport
  vec viewport_u = vec(viewport_width, 0, 0);
  vec viewport_v = vec(0, -viewport_height, 0);

  // Both these are magnitude and dirn of each pixel along u and v.
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_width;

  // Calculate the location of upper left pixel. fl, viewport_v are along -ve z.
  // camera center - focalLength - viewport_u/2 - viewport_v/2
  point pixel00_loc =
      camera_center - vec(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;

  // Open a file image.ppm
  std::ofstream myfile;
  myfile.open("image.ppm");

  // Render
  myfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (double j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << image_height - j << ' '
              << std::flush;
    for (double i = 0; i < image_width; i++) {
      // send ray toward every pixel from camera_center and write the color
      // observed.
      point pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec ray_direction = pixel_center - camera_center;
      ray r(camera_center, pixel_center);

      color pixel_color = ray_color(r);
      writePixel(myfile, pixel_color);
    }
    myfile << '\n';
  }
  myfile.close();
  std::clog << "\rDone. \n";
}
