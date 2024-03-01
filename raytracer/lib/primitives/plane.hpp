#pragma once

#include "object.hpp"

#pragma once

#include "object.hpp"

class Plane : public Object {
public:
  Plane() = default;
  Plane(Material mat);
  Plane(Matrix<4> transformation);
  Plane(Matrix<4> transformation, Material mat);
  bool IsIntersectable() const override;
  Intersections GetIntersections(Ray r) const override;
  void Transform(const Matrix<4> &transformation) override;
  const Matrix<4> &GetTransformation() const override;
  void SetMaterial(const Material m) override;
  const Material &GetMaterial() const override;
  Material &GetMaterial() override;
  Vector GetNormalAtPoint(Point p) const override;

protected:
  Matrix<4> mat_{math_constants::m4_identity};
  Material material_;
};

Intersections PlaneIntersection(const Plane &s, Ray r);
Vector PlaneNormal(const Plane &s, const Point &p);