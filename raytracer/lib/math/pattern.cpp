#include "pattern.hpp"
#include "math/constants.hpp"
#include "primitives/object.hpp"
#include <cmath>

Color Pattern::ColorOnObject(const Point &point, const Object *obj) const {
  auto object_point =
      obj->GetTransformation().Eigen().inverse() * point.Eigen();
  auto pattern_point = (GetTransform().Eigen().inverse() * object_point).eval();
  return GetColor(Point(pattern_point));
}

void StripePattern::SetTransform(const Matrix<4> &mat) { transform_ = mat; }
const Matrix<4> &StripePattern::GetTransform() const { return transform_; }

StripePattern::StripePattern(Color first, Color second)
    : first_(first), second_(second) {}

Color StripePattern::GetColor(const Point &point) const {
  auto val = point.x() < 0.0 ? std::abs(point.x()) + 1 - kEpsilon : point.x();
  if (static_cast<int>(val) % 2 == 0) {
    return first_;
  }
  return second_;
}

void TestPattern::SetTransform(const Matrix<4> &mat) { transform_ = mat; }
const Matrix<4> &TestPattern::GetTransform() const { return transform_; }

Color TestPattern::GetColor(const Point &point) const {
  return Color(point.x(), point.y(), point.z());
}

void Gradient::SetTransform(const Matrix<4> &mat) { transform_ = mat; }
const Matrix<4> &Gradient::GetTransform() const { return transform_; }

Gradient::Gradient(Color first, Color second)
    : first_(first), second_(second) {}

Color Gradient::GetColor(const Point &point) const {
  auto distance = second_ - first_;
  auto fraction = point.x() - std::floor(point.x());
  return first_ + distance * fraction;
}

void Ring::SetTransform(const Matrix<4> &mat) { transform_ = mat; }
const Matrix<4> &Ring::GetTransform() const { return transform_; }

Ring::Ring(Color first, Color second) : first_(first), second_(second) {}

Color Ring::GetColor(const Point &point) const {
  auto val =
      std::floor(std::sqrt(point.x() * point.x() + point.z() * point.z()));
  if (static_cast<int>(val) % 2 == 0) {
    return first_;
  }
  return second_;
}

void Checker::SetTransform(const Matrix<4> &mat) { transform_ = mat; }
const Matrix<4> &Checker::GetTransform() const { return transform_; }

Checker::Checker(Color first, Color second) : first_(first), second_(second) {}

Color Checker::GetColor(const Point &point) const {
  auto val = std::abs(point.x()) + std::abs(point.y()) + std::abs(point.z());
  if (static_cast<int>(val) % 2 == 0) {
    return first_;
  }
  return second_;
}
