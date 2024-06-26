#include "../include/camera.h"
#include "../include/hittable.h"
#include "../include/include_these.h"

// just a absolute value function of double.

int main() {
  // world
  hittable_list world;
  world.add(make_shared<sphere>(point(0, -100.5, -1), 99.75));
  world.add(make_shared<sphere>(point(0, 0, -1), 0.75));

  // camera
  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.render(world);
}
