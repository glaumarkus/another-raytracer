#pragma once

#include "imgui/color.hpp"
#include "math/vector2d.hpp"
#include <memory>

class Pattern;
class Material {
public:
  Material() = default;
  Material(Color color, double ambient, double diffuse, double specular,
           double shininess);
  Color GetColor() const;
  Color GetColor(const Point &p) const;
  double Ambient() const;
  double Diffuse() const;
  double Specular() const;
  double Shininess() const;
  bool HasPattern() const;
  const std::shared_ptr<Pattern> GetPattern() const;
  double Reflective() const;
  double RefractiveIdx() const;
  double Transparent() const;
  void SetColor(Color color);
  void SetAmbient(double ambient);
  void SetDiffuse(double diffuse);
  void SetSpecular(double specular);
  void SetShininess(double shininess);
  void SetPattern(std::shared_ptr<Pattern> p);
  void SetReflective(double reflective);
  void SetRefractiveIdx(double refractive_idx);
  void SetTransparent(double transparent);

protected:
  Color color_{1, 1, 1};
  double ambient_{0.1};
  double diffuse_{0.9};
  double specular_{0.9};
  double shininess_{200};
  std::shared_ptr<Pattern> pattern_{nullptr};
  double reflective_{0.0};
  double refractive_idx_{1.0};
  double transparency_{0.0};
};
