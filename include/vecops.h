#ifndef VECOPS_H // compile the later code only if VECOPS_H macro isn't defined.
#define VECOPS_H // define VECOPS_H so this file can't be later included again.

class vec {

public:
  double value[3];
  vec(double p = 0, double q = 0, double r = 0); // ordinary constructor
  double x() const;
  double y() const;
  double z() const;
  vec operator+(const vec &v2) const;
  vec operator*(const double t) const;
  vec operator/(const double t) const;
  double dot(const vec &v2);
  vec cross(const vec &v2);
  double magnitude() const;
  double magnitudeSquared() const;
  vec direction(const vec &reference = vec());
};
#endif
