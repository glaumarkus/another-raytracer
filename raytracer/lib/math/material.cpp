#include "material.hpp"

#include "pattern.hpp"

Material::Material(Color color, double ambient, double diffuse, double specular,
                   double shininess)
    : color_(color), ambient_(ambient), diffuse_(diffuse), specular_(specular),
      shininess_(shininess) {}
Color Material::GetColor() const { return color_; }
bool Material::HasPattern() const { return pattern_ == nullptr; }
Color Material::GetColor(const Point &p) const { return pattern_->GetColor(p); }
const std::shared_ptr<Pattern> Material::GetPattern() const { return pattern_; }
double Material::Ambient() const { return ambient_; }
double Material::Diffuse() const { return diffuse_; }
double Material::Specular() const { return specular_; }
double Material::Shininess() const { return shininess_; }

void Material::SetColor(Color color) { color_ = color; }
void Material::SetAmbient(double ambient) { ambient_ = ambient; }
void Material::SetDiffuse(double diffuse) { diffuse_ = diffuse; }
void Material::SetSpecular(double specular) { specular_ = specular; }
void Material::SetShininess(double shininess) { shininess_ = shininess; }
void Material::SetPattern(std::shared_ptr<Pattern> p) { pattern_ = p; }
