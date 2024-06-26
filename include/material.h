#pragma once

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       color &attenuation, ray &scattered) const {
    return false;
  }
};

class lambertian : public material {
private:
  color albedo;

public:
  lambertian(const color &albedo) : albedo(albedo) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    auto scatter_direction = rec.normal + random_unit_vector();
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
};
