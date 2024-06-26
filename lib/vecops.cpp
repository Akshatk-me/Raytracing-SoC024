#include "../include/vecops.h"
#include <cmath>

vec::vec(double p, double q, double r) {
  value[0] = p;
  value[1] = q;
  value[2] = r;
}

double vec::x() const { return value[0]; }
double vec::y() const { return value[1]; }
double vec::z() const { return value[2]; }

vec vec::operator-() const { return vec(-value[0], -value[1], -value[2]); }

double vec::operator[](int i) const { return value[i]; };
double &vec::operator[](int i) { return value[i]; };

vec vec::operator+=(const vec &v) {
  value[0] += v.x();
  value[1] += v.y();
  value[2] += v.z();
  return *this; // it's necessary to return a value as assignment operator also
                // needs a value not just an operation.
}

vec vec::operator*=(const double t) {
  value[0] *= t;
  value[1] *= t;
  value[2] *= t;
  return *this;
}
vec vec::operator/=(double t) { return *this *= 1 / t; };

double vec::magnitudeSquared() const {
  return value[0] * value[0] + value[1] * value[1] + value[2] * value[2];
}

double vec::magnitude() const { return std::sqrt(magnitudeSquared()); }

vec vec::direction() const {
  double mag = magnitude();
  return vec(value[0] / mag, value[1] / mag, value[2] / mag);
}

vec vec::random() {
  return vec(random_double(), random_double(), random_double());
}

vec vec::random(double min, double max) {
  return vec(random_double(min, max), random_double(min, max),
             random_double(min, max));
}

// point is an alias for vec, it's better for providing geometric clarity
