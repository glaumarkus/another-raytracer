#pragma once

#include "intersections.hpp"
#include "mat.hpp"
#include "ray.hpp"
#include "vector2d.hpp"
#include <vector>
#include "material.hpp"

class Object {
public:
  virtual bool IsIntersectable() const = 0;
  virtual Intersections GetIntersections(Ray r) const = 0;
  virtual void Transform(const Matrix<4>& transformation) = 0;
  virtual const Matrix<4> &GetTransformation() const = 0;
  virtual void SetMaterial(const Material m) = 0;
  virtual Material GetMaterial() const = 0;
};

class Sphere : public Object {
public:
  Sphere() = default;
  Sphere(Material mat);
  Sphere(Matrix<4> transformation);
  Sphere(Matrix<4> transformation, Material mat);
  bool IsIntersectable() const override;
  Intersections GetIntersections(Ray r) const override;
  void Transform(const Matrix<4>& transformation) override;
  const Matrix<4> &GetTransformation() const override;
  void SetMaterial(const Material m) override;
  Material GetMaterial() const override;

protected:
  Matrix<4> mat_{math_constants::m4_identity};
  Material material_;
};

Intersections SphereIntersection(const Sphere &s, Ray r);
Vector SphereNormal(const Sphere& s, const Point& p);