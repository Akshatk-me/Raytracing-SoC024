#pragma once

#include "hittable.h"
#include "include_these.h"
#include "utils.h"

class camera {
public:
  double aspect_ratio = 16.0 / 9.0; // width/height
  int image_width = 400;
  int samples_per_pixel = 100; // Count of random samples for each pixel

  void render(const hittable &world) {
    initialize();
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
        // observed
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world);
        }
        auto t = pixel_samples_scale * pixel_color;
        writePixel(myfile, t);
      }
      myfile << '\n';
    }
    myfile.close();

    std::clog << "\rDone. \n";
  }

private:
  int image_height;
  point pixel00_loc;
  vec pixel_delta_u;
  vec pixel_delta_v;
  point camera_center;
  double pixel_samples_scale; // color scale factor for a sum of pixel samples

  void initialize() {
    // define image height, ensure >= 1;
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    // Camera
    // calculate viewport_width based on actual image_height and image_width;
    double viewport_height = 4.0; // specified in some actual distance unit
    double viewport_width =
        viewport_height * (double(image_width) / image_height);
    double focalLength = 1.0;
    camera_center = point(0, 0, 0);

    // Calculate vectors across veiwport
    vec viewport_u = vec(viewport_width, 0, 0);
    vec viewport_v = vec(0, -viewport_height, 0);

    // Both these are magnitude and dirn of each pixel along u and v.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of upper left pixel. fl, viewport_v are along -ve
    // z. camera center - focalLength - viewport_u/2 - viewport_v/2
    pixel00_loc = camera_center - vec(0, 0, focalLength) - viewport_u / 2 -
                  viewport_v / 2;
  }

  ray get_ray(int i, int j) const {
    // returns random ray from origin to randomly around pixel location (i, j);
    auto offset = sample_square();
    // given pixel location return ray
    point pixel_center = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                         ((j + offset.y()) * pixel_delta_v);
    vec ray_direction = pixel_center - camera_center;
    ray r(camera_center, pixel_center);
    return r;
  }

  vec sample_square() const {
    // Returns the vector to a random point in unit square.
    return vec(random_double() - 0.5, random_double() - 0.5, 0);
  }

  color ray_color(const ray &r, const hittable &world, int depth = 10) {
    hit_record rec;
    interval ray_t(0.001, infinity);
    if (world.hit(r, ray_t, rec) && depth >= 0) {
      vec direction = rec.normal + random_unit_vector();
      return 0.5 * ray_color(ray(rec.p, direction), world, depth - 1);
    } else {
      auto x = r.getDirection().direction();
      auto a = 0.5 * (x.y() + 1.0);
      // x = vec(abs(x.x()), abs(x.y()), abs(x.z()));
      // return x;
      return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
  }
};
