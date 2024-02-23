#include "object.hpp"

Sphere::Sphere(Matrix<4> transformation) : mat_(transformation) {}
bool Sphere::IsIntersectable() const { return true; }
Intersections Sphere::GetIntersections(Ray r) const {
  return SphereIntersection(*this, r);
}
const Matrix<4> &Sphere::GetTransformation() const { return mat_; }

void Sphere::Transform(const Matrix<4> &transformation) {
  mat_ *= transformation;
}

Intersections SphereIntersection(const Sphere &s, Ray r) {
  r = r.Transform(s.GetTransformation().Eigen().inverse().eval());
  Intersections i;
  auto sphere_to_ray = r.GetOrigin() - Point(0, 0, 0);
  auto a = Dot(r.GetDirection(), r.GetDirection());
  auto b = 2 * Dot(r.GetDirection(), sphere_to_ray);
  auto c = sphere_to_ray.Dot(sphere_to_ray) - 1;
  auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return i;
  }
  auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
  auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

  if (t1 == t2) {
    i.Add(t1, static_cast<const Object *>(&s));
  } else {
    i.Add(t1, static_cast<const Object *>(&s));
    i.Add(t2, static_cast<const Object *>(&s));
  }
  return i;
}