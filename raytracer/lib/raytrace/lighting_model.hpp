#pragma once
#include "imgui/color.hpp"
#include "light.hpp"
#include "math/material.hpp"

class LightingModel {
public:
  virtual Color GetLightingColor(const Material &material,
                                 std::vector<Light *> lights,
                                 const Point &point, const Vector &eye_vector,
                                 const Vector &normal_vector) = 0;
};

class PhongReflectionModel : public LightingModel {
public:
  Color GetLightingColor(const Material &material, std::vector<Light *> lights,
                         const Point &point, const Vector &eye_vector,
                         const Vector &normal_vector) override;

protected:
};

