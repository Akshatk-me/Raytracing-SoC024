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

    // prevent degenrate scatter dirceton
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(const color &albedo, double fuzz)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    vec reflected = reflect(r_in.getDirection(), rec.normal);
    reflected = reflected.direction() + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.getDirection(), rec.normal) > 0);
  }
};

class dielectric : public material {
private:
  double refraction_index;

  static double reflectance(double cosine, double refraction_index) {
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
  }

public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
    vec unit_direction = r_in.getDirection().direction();

    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec direction;

    if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
      direction = reflect(unit_direction, rec.normal);
      // reflect
    }

    else {
      // refract
      direction = refract(unit_direction, rec.normal, ri);
    }
    scattered = ray(rec.p, direction);
    return true;
  }
};
