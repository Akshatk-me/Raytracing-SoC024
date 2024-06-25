#pragma once

#include "interval.h"
#include "ray.h"
#include <cmath>
#include <memory>
#include <vector>

class hit_record {
public:
  point p;    // point of hit
  vec normal; // normal at point p
  double t;   // value of t for the ray.

  bool front_face;

  // we have chosen the direction of normal to always be opposite to the ray
  void set_face_normal(const ray &r, const vec &outward_normal) {
    front_face = dot(r.getDirection(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool
  hit(const ray &r, interval ray_t,
      hit_record &rec) const = 0; // this means every derived class must provide
                                  // the implementation for hit themselves
};

class hittable_list : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects;

  hittable_list() {}

  hittable_list(std::shared_ptr<hittable> object) { add(object); }

  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
    hit_record temp_rec;
    bool hit_anything = false;

    auto closest_so_far = ray_t.max;

    // iterates over objects, if hits temp_rec is updates, then temp_rec is
    // updated.
    for (const auto &object : objects) {
      if (object->hit(r, ray_t, temp_rec)) {
        hit_anything = true;
        // add the closest object to the record
        if (closest_so_far > temp_rec.t) {
          closest_so_far = temp_rec.t;
          rec = temp_rec;
        }
      }
    }
    return hit_anything;
  }
};

class sphere : public hittable {
private:
  point center;
  double radius;

public:
  sphere(const point &center, double radius)
      : center(center), radius((radius > 0.0) ? radius : 0.0) {}

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
    vec OC = center - r.getOrigin();

    // all these auto variables are "double" at the time of writing this
    auto a = r.getDirection().magnitudeSquared();
    auto h = dot(r.getDirection(), OC);
    auto c = OC.magnitudeSquared() - radius * radius;

    auto discriminant = h * h - a * c; // psuedo discriminant
    if (discriminant < 0) {
      return false;
    }

    auto root = (h - sqrt(discriminant)) / a;

    // if both roots lie outside the range (t_min, t_max), return false
    if (!ray_t.contains(root)) {
      root = (h + sqrt(discriminant)) / a;
      if (!ray_t.contains(root)) {
        return false;
      }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
  }
};
