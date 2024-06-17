#pragma once
#include "vecops.h"

class ray {
private:
  point origin;
  vec direction;

public:
  ray() {}
  ray(const point &origin, const vec &direction)
      : origin(origin), direction(direction) {}
  const point getOrigin() const { return origin; }
  const point getDirection() const { return direction; }

  const point at(const double t) const { return origin + (direction * t); }
};
