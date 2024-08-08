#pragma once

#include "hittable.h"
#include "include_these.h"
#include "material.h"
#include "utils.h"
#include "vecops.h"

class camera {
public:
  double aspect_ratio = 16.0 / 9.0; // width/height
  int image_width = 400;
  int samples_per_pixel = 100; // Count of random samples for each pixel
  int max_depth = 50;
  double vfov = 90;
  point lookfrom = point(0, 0, 0);
  point lookat = point(0, 0, -1);
  vec vup = vec(0, 1, 0);

  double defocus_angle = 0;
  double focus_dist = 10;

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
          pixel_color += ray_color(r, world, max_depth);
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
  vec u, v, w;

  vec defocus_disk_u;
  vec defocus_disk_v;

  void initialize() {
    // define image height, ensure >= 1;
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    // Camera
    // calculate viewport_width based on actual image_height and image_width;
    camera_center = lookfrom;
    auto t = lookfrom - lookat;
    auto theta = degree_to_radians(vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focus_dist;
    double viewport_width =
        viewport_height * (double(image_width) / image_height);

    w = t.direction();
    u = cross(vup, w).direction();
    v = cross(w, u);
    // Calculate vectors across veiwport
    vec viewport_u = viewport_width * u;
    vec viewport_v = viewport_height * (-v);

    // Both these are magnitude and dirn of each pixel along u and v.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of upper left pixel. fl, viewport_v are along -ve
    // z. camera center - focalLength - viewport_u/2 - viewport_v/2
    auto viewport_upper_left =
        camera_center - (focus_dist * w) - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc = viewport_upper_left + 0.5 + (pixel_delta_u + pixel_delta_v);

    auto defocus_radius =
        focus_dist * std::tan(degree_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }

  ray get_ray(int i, int j) const {
    // returns random ray from origin to randomly around pixel location (i, j);
    auto offset = sample_square();
    // given pixel location return ray
    point pixel_center = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                         ((j + offset.y()) * pixel_delta_v);
    auto ray_origin =
        (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
    vec ray_direction = pixel_center - camera_center;
    ray r(camera_center, pixel_center);
    return r;
  }

  vec sample_square() const {
    // Returns the vector to a random point in unit square.
    return vec(random_double() - 0.5, random_double() - 0.5, 0);
  }

  point defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  }

  color ray_color(const ray &r, const hittable &world, int depth = 10) {
    hit_record rec;
    interval ray_t(0.001, 10000);
    if (world.hit(r, ray_t, rec) && depth >= 0) {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * ray_color(scattered, world, depth - 1);
      }
      // vec direction = rec.normal + random_unit_vector();
      return color(0, 0, 0);
    } else {
      auto x = r.getDirection().direction();
      auto a = 0.5 * (x.y() + 1.0);
      // x = vec(abs(x.x()), abs(x.y()), abs(x.z()));
      // return x;
      return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
  }
};
