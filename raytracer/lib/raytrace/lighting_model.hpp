#pragma once
#include "imgui/color.hpp"
#include "light.hpp"
#include "math/material.hpp"
#include <memory>

class LightingModel {
public:
  virtual bool CalculateShadow() const = 0;
  virtual Color
  GetLightingColor(const Material &material,
                   const std::vector<std::shared_ptr<Light>> &lights,
                   const Point &point, const Vector &eye_vector,
                   const Vector &normal_vector, double in_shadow) const = 0;
};

class PhongReflectionModel : public LightingModel {
public:
  bool CalculateShadow() const override;
  Color GetLightingColor(const Material &material,
                         const std::vector<std::shared_ptr<Light>> &lights,
                         const Point &point, const Vector &eye_vector,
                         const Vector &normal_vector,
                         double in_shadow) const override;
};

class PhongReflectionShadowModel : public LightingModel {
public:
  bool CalculateShadow() const override;
  Color GetLightingColor(const Material &material,
                         const std::vector<std::shared_ptr<Light>> &lights,
                         const Point &point, const Vector &eye_vector,
                         const Vector &normal_vector,
                         double in_shadow) const override;
};
