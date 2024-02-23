#pragma once

#include "intersections.hpp"
#include "mat.hpp"
#include "ray.hpp"
#include "vector2d.hpp"
#include <vector>

class Object {
public:
  virtual bool IsIntersectable() const = 0;
  virtual Intersections GetIntersections(Ray r) const = 0;
  virtual void Transform(const Matrix<4>& transformation) = 0;
  virtual const Matrix<4> &GetTransformation() const = 0;
};

class Sphere : public Object {
public:
  Sphere() = default;
  Sphere(Matrix<4> transformation);
  bool IsIntersectable() const override;
  Intersections GetIntersections(Ray r) const override;
  void Transform(const Matrix<4>& transformation) override;
  const Matrix<4> &GetTransformation() const override;

protected:
  Matrix<4> mat_{math_constants::m4_identity};
};

Intersections SphereIntersection(const Sphere &s, Ray r);
