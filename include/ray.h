#pragma once
#include "utils.h"
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

class interval {
public:
  double min, max;
  interval() : min(-infinity), max(+infinity) {}

  interval(double min, double max) : min(min), max(max) {}

  double size() const { return max - min; }
  bool contains(double x) const { return ((min <= x) && (x <= max)); }

  bool surrounds(double x) const { return ((min < x) && (x < max)); }

  static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
