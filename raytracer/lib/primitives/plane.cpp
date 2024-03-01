#include "plane.hpp"

#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "object.hpp"

bool Plane::IsIntersectable() const { return true; }
Intersections Plane::GetIntersections(Ray r) const {
  return PlaneIntersection(*this, r);
}
const Matrix<4> &Plane::GetTransformation() const { return mat_; }

void Plane::Transform(const Matrix<4> &transformation) {
  mat_ *= transformation;
}

Intersections PlaneIntersection(const Plane &pl, Ray r) {
  r = r.Transform(pl.GetTransformation().Eigen().inverse().eval());
  Intersections i;
  if (std::abs(r.GetDirection().y()) < kEpsilon) {
    return i;
  }
  auto t = -r.GetOrigin().y() / r.GetDirection().y();
  i.Add(t, static_cast<const Object *>(&pl));
  return i;
}

Vector PlaneNormal(const Plane &pl, const Point &p) { return Vector(0, 1, 0); }

void Plane::SetMaterial(const Material m) { material_ = m; }
const Material &Plane::GetMaterial() const { return material_; }
Material &Plane::GetMaterial() { return material_; }

Plane::Plane(Matrix<4> transformation) : mat_(transformation) {}
Plane::Plane(Material mat) : material_(mat) {}
Plane::Plane(Matrix<4> transformation, Material mat)
    : mat_(transformation), material_(mat) {}
Vector Plane::GetNormalAtPoint(Point p) const { return PlaneNormal(*this, p); }