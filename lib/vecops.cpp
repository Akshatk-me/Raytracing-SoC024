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

vec vec::operator+(const vec &v2) const {
  return vec(value[0] + v2.x(), value[1] + v2.y(), value[2] + v2.z());
}

vec vec::operator*(double t) const {
  return vec(value[0] * t, value[1] * t, value[2] * t);
}

vec vec::operator/(double t) const {
  return vec(value[0] / t, value[1] / t, value[2] / t);
}

double vec::dot(const vec &v2) {
  return (value[0] * v2.x() + value[1] * v2.y() + value[2] * v2.z());
}

vec vec::cross(const vec &v2) {
  double x = value[1] * v2.z() - value[2] * v2.y();
  double y = value[3] * v2.x() - value[1] * v2.z();
  double z = value[1] * v2.y() - value[2] * v2.x();
  return vec(x, y, z);
}

double vec::magnitude() const {
  return std::sqrt(value[0] * value[0] + value[1] * value[1] +
                   value[2] * value[2]);
}

double vec::magnitudeSquared() const {
  return value[0] * value[0] + value[1] * value[1] + value[2] * value[2];
}

vec vec::direction(const vec &v2) {
  double mag = this->magnitude();
  return vec(value[0] / mag, value[1] / mag, value[2] / mag);
}
