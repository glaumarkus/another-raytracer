#pragma once

#include "math/intersections.hpp"
#include "math/mat.hpp"
#include "math/material.hpp"
#include "math/ray.hpp"
#include "math/vector2d.hpp"
#include <vector>

class Intersections;

class Object {
public:
  virtual bool IsIntersectable() const = 0;
  virtual Intersections GetIntersections(Ray r) const = 0;
  virtual void Transform(const Matrix<4> &transformation) = 0;
  virtual const Matrix<4> &GetTransformation() const = 0;
  virtual void SetMaterial(const Material m) = 0;
  virtual const Material &GetMaterial() const = 0;
  virtual Material &GetMaterial() = 0;
  virtual Vector GetNormalAtPoint(Point p) const = 0;
};
