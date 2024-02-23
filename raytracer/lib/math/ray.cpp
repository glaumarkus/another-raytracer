#include "ray.hpp"

Ray::Ray(Point p, Vector v) : origin_(p), dir_(v) {}

Point Ray::Position(double t) { return origin_ + dir_ * t; }

const Point &Ray::GetOrigin() const { return origin_; }
const Vector &Ray::GetDirection() const { return dir_; }

Ray Ray::Transform(const Matrix<4> &transform) {
  return Ray((transform * origin_).Eigen(), (transform * dir_).Eigen());
}