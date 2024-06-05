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
inline vec operator+(const vec &v1, const vec &v2); // vector addition
inline vec operator-(const vec &v1, const vec &v2);
inline vec operator*(const vec &v, const double t); // scalar multiplication
inline vec operator/(const vec &v, const double t); // scalar division
std::ostream &operator<<(std::ostream &ost, vec v);

inline double dot(const vec &v1, const vec &v2); // scalar product of two
                                                 // vectors
vec cross(const vec &v1, const vec &v2);         // vector product
#endif
