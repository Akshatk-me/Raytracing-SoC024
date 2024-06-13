#ifndef VECOPS_H // compile the later code only if VECOPS_H macro isn't defined.
#define VECOPS_H // define VECOPS_H so this file can't be later included again.
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
inline vec operator/(const vec &v, const double t) {
  return v * (1.0 / t);
}; // scalar division

inline std::ostream &operator<<(std::ostream &ost, const vec &v) {
  ost << v.x() << ' ' << v.y() << ' ' << v.z() << ' ';
  return ost;
}

inline double dot(const vec &v1, const vec &v2) {
  return (v1.x() * v2.x() + v2.x() * v2.y() + v1.z() * v2.z());
}

inline vec cross(const vec &v1, const vec &v2) {
  double x = v1.y() * v2.z() - v1.z() * v2.y();
  double y = v1.z() * v2.x() - v1.x() * v2.z();
  double z = v1.x() * v2.y() - v1.y() * v2.x();
  vec t = vec();
  return vec(x, y, z);
}

using point = vec;

#endif
