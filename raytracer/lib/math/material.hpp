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
  void SetColor(Color color);
  void SetAmbient(double ambient);
  void SetDiffuse(double diffuse);
  void SetSpecular(double specular);
  void SetShininess(double shininess);

protected:
  Color color_{1, 1, 1};
  double ambient_{0.1};
  double diffuse_{0.9};
  double specular_{0.9};
  double shininess_{200};
};
