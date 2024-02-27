#pragma once
#include "imgui/color.hpp"
#include "light.hpp"
#include "math/material.hpp"
#include <memory>

class LightingModel {
public:
  virtual Color
  GetLightingColor(const Material &material,
                   const std::vector<std::shared_ptr<Light>> &lights,
                   const Point &point, const Vector &eye_vector,
                   const Vector &normal_vector) const = 0;
};

class PhongReflectionModel : public LightingModel {
public:
  Color GetLightingColor(const Material &material,
                         const std::vector<std::shared_ptr<Light>> &lights,
                         const Point &point, const Vector &eye_vector,
                         const Vector &normal_vector) const override;
};
