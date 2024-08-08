#ifndef VECOPS_H // compile the later code only if VECOPS_H macro isn't defined.
#define VECOPS_H // define VECOPS_H so this file can't be later included again.
#include "utils.h"
#include <iostream>

class vec {
public:
  double value[3];
  vec(double p = 0, double q = 0, double r = 0); // ordinary constructor
  double x() const;
  double y() const;
  double z() const;
  vec operator-() const;
  double operator[](int i) const;
  double &operator[](int i);
  vec operator+=(const vec &v);
  vec operator*=(double t);
  vec operator/=(double t);
  double magnitudeSquared() const;
  double magnitude() const;
  vec direction() const;
  static vec random();
  static vec random(double min, double max);
  bool near_zero() const;
};

inline vec operator+(const vec &v1, const vec &v2) {
  return vec(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
inline vec operator-(const vec &v1, const vec &v2) {
  return vec(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
inline vec operator*(const vec &v, const double t) {
  return vec(v.x() * t, v.y() * t, v.z() * t);
} // scalar multiplication
inline vec operator*(const double t, const vec &v) {
  return vec(v.x() * t, v.y() * t, v.z() * t);
}
inline vec operator*(const vec &v1, const vec &v2) {
  return vec(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
inline vec operator/(const vec &v, const double t) {
  return v * (1.0 / t);
}; // scalar division

inline std::ostream &operator<<(std::ostream &ost, const vec &v) {
  ost << v.x() << ' ' << v.y() << ' ' << v.z() << ' ';
  return ost;
}

inline double dot(const vec &v1, const vec &v2) {
  return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}

inline vec cross(const vec &v1, const vec &v2) {
  double x = v1.y() * v2.z() - v1.z() * v2.y();
  double y = v1.z() * v2.x() - v1.x() * v2.z();
  double z = v1.x() * v2.y() - v1.y() * v2.x();
  vec t = vec();
  return vec(x, y, z);
}

inline vec random_in_unit_sphere() {
  // change the implementation to a better one
  // for example generate using spherical coordinates
  while (true) {
    auto p = vec::random(-1, 1);
    if (p.magnitudeSquared() < 1) {
      return p;
    }
  }
}

inline vec random_unit_vector() { return random_in_unit_sphere().direction(); }

inline vec random_on_hemisphere(const vec &normal) {
  vec on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0) {
    return on_unit_sphere;
  } else {
    return -on_unit_sphere;
  }
}

inline vec random_in_unit_disk() {
  while (true) {
    auto p = vec(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.magnitudeSquared() < 1)
      return p;
  }
}

inline vec reflect(const vec &v, const vec &n) { return v - 2 * dot(v, n) * n; }

inline vec refract(const vec &uv, const vec &n, double etai_over_etat) {
  auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec r_out_perp = etai_over_etat * (uv + cos_theta * n);
  vec r_out_parallel =
      -std::sqrt(std::fabs(1.0 - r_out_perp.magnitudeSquared())) * n;
  return r_out_perp + r_out_parallel;
}

using point = vec;

#endif
