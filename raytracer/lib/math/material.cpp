#include "material.hpp"

Material::Material(Color color, double ambient, double diffuse, double specular,
                   double shininess)
    : color_(color), ambient_(ambient), diffuse_(diffuse), specular_(specular),
      shininess_(shininess) {}
Color Material::GetColor() const { return color_; }
double Material::Ambient() const { return ambient_; }
double Material::Diffuse() const { return diffuse_; }
double Material::Specular() const { return specular_; }
double Material::Shininess() const { return shininess_; }
