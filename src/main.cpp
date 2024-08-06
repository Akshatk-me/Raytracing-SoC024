#include "../include/camera.h"
#include "../include/hittable.h"
#include "../include/include_these.h"
#include "../include/material.h"

// just a absolute value function of double.

int main() {
  // world
  hittable_list world;
  /*
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.0);
  auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.2);
  world.add(
      make_shared<sphere>(point(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.4, material_bubble));
  world.add(make_shared<sphere>(point(1.0, 0.0, -1.0), 0.5, material_right));
  */

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.50);
  auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

  world.add(
      make_shared<sphere>(point(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.4, material_bubble));
  world.add(make_shared<sphere>(point(1.0, 0.0, -1.0), 0.5, material_right));

  // camera
  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 75; // 100 is good
  cam.max_depth = 10;

  cam.vfov = 90;
  cam.lookfrom = point(-2, 2, 1);
  cam.lookat = point(0, 0, -1);
  cam.vup = vec(0, 1, 0);

  cam.render(world);
}
