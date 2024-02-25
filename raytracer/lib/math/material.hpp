#pragma once

#include "imgui/color.hpp"

class Material {
public:
  Material() = default;
  Material(Color color, double ambient, double diffuse, double specular,
           double shininess);
  Color GetColor() const;
  double Ambient() const;
  double Diffuse() const;
  double Specular() const;
  double Shininess() const;

protected:
  Color color_{1, 1, 1};
  double ambient_{0.1};
  double diffuse_{0.9};
  double specular_{0.9};
  double shininess_{200};
};
