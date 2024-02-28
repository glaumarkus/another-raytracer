#pragma once

#include "object.hpp"

class Sphere : public Object {
public:
  Sphere() = default;
  Sphere(Material mat);
  Sphere(Matrix<4> transformation);
  Sphere(Matrix<4> transformation, Material mat);
  bool IsIntersectable() const override;
  Intersections GetIntersections(Ray r) const override;
  void Transform(const Matrix<4> &transformation) override;
  const Matrix<4> &GetTransformation() const override;
  void SetMaterial(const Material m) override;
  Material GetMaterial() const override;
  Vector GetNormalAtPoint(Point p) const override;

protected:
  Matrix<4> mat_{math_constants::m4_identity};
  Material material_;
};

Intersections SphereIntersection(const Sphere &s, Ray r);
Vector SphereNormal(const Sphere &s, const Point &p);