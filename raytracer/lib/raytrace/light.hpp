#pragma once

#include "imgui/color.hpp"
#include "math/vector2d.hpp"

class Light {
public:
  virtual Point GetPoint() const = 0;
  virtual Color GetIntensity() const = 0;
};

class PointLight : public Light {
public:
  PointLight(Point p, Color c);
  Point GetPoint() const override;
  Color GetIntensity() const override;

protected:
  Point origin_;
  Color intensity_;
};
