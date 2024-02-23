#pragma once

#include "mat.hpp"
#include "vector2d.hpp"

class Ray {
public:
  Ray() = default;
  ~Ray() = default;
  Ray(Point p, Vector v);
  Point Position(double t);
  Ray Transform(const Matrix<4> &transform);

  const Point &GetOrigin() const;
  const Vector &GetDirection() const;

protected:
  Point origin_;
  Vector dir_;
};
