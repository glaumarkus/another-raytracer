#include "light.hpp"

PointLight::PointLight(Point p, Color c) : Light(), origin_(p), intensity_(c) {}

Point PointLight::GetPoint() const { return origin_; }
Color PointLight::GetIntensity() const { return intensity_; }