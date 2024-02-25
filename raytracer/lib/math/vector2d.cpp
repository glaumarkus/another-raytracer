#include "vector2d.hpp"
#include "Eigen/src/Core/Matrix.h"

Point::Point(double v) : Tuple(v) {}
Point::Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {}
Point::Point(Eigen::Vector4d &&v) : Tuple(std::move(v)) {}
Point::Point(const Eigen::Vector4d &v) : Tuple(v) {}

Tuple::Tuple(double v) : vec(v, v, v, 0.0) {}
Tuple::Tuple(double x, double y, double z) : vec(x, y, z, 0.0) {}
Tuple::Tuple(double x, double y, double z, double w) : vec(x, y, z, w) {}
Tuple::Tuple(Eigen::Vector4d &&v) : vec(std::move(v)) {}
Tuple::Tuple(const Eigen::Vector4d &v) : vec(v) {}

double &Tuple::x() { return vec.x(); }
double &Tuple::y() { return vec.y(); }
double &Tuple::z() { return vec.z(); }
double &Tuple::w() { return vec.w(); }
const double &Tuple::x() const { return vec.x(); }
const double &Tuple::y() const { return vec.y(); }
const double &Tuple::z() const { return vec.z(); }
const double &Tuple::w() const { return vec.w(); }
const Eigen::Vector4d &Tuple::Eigen() const { return vec; }
void Tuple::Negate() { vec = math_constants::empty.Eigen() - vec; }
double Tuple::Dot(const Tuple &other) { return vec.dot(other.vec); }

Tuple &Tuple::operator+=(const Tuple &other) {
  vec += other.vec;
  return *this;
}
Tuple &Tuple::operator-=(const Tuple &other) {
  vec -= other.vec;
  return *this;
}

Tuple &Tuple::operator*=(const double v) {
  vec *= v;
  return *this;
}

Tuple &Tuple::operator/=(const double v) {
  vec /= v;
  return *this;
}

Tuple operator+(const Tuple &lhs, const Tuple &rhs) {
  return Tuple(Eigen::Vector4d(lhs.Eigen() + rhs.Eigen()));
}
Tuple operator-(const Tuple &lhs, const Tuple &rhs) {
  return Tuple(Eigen::Vector4d(lhs.Eigen() - rhs.Eigen()));
}

Tuple operator*(const Tuple &lhs, const double rhs) {
  return Tuple(Eigen::Vector4d(lhs.Eigen() * rhs));
}

Tuple operator/(const Tuple &lhs, const double rhs) {
  return Tuple(Eigen::Vector4d(lhs.Eigen() / rhs));
}

double Tuple::Magnitude() { return vec.norm(); }

void Tuple::Normalize() { vec.normalize(); }

Tuple Tuple::Normalized() { return Tuple(vec.normalized()); }

double Dot(const Tuple &lhs, const Tuple &rhs) {
  return lhs.Eigen().dot(rhs.Eigen());
}

Tuple Tuple::Cross(const Tuple &other) {
  Eigen::Vector3d cross = vec.head<3>().cross(other.Eigen().head<3>());
  return Tuple(Eigen::Vector4d(cross.x(), cross.y(), cross.z(), 0.0));
}

Point operator+(const Point &point, const Vector &vector) {
  return Point(Eigen::Vector4d(point.Eigen() + vector.Eigen()));
}

Point operator-(const Point &point, const Vector &vector) {
  return Point(Eigen::Vector4d(point.Eigen() - vector.Eigen()));
}

bool operator==(const Tuple &lhs, const Tuple &rhs) {
  return lhs.Eigen() == rhs.Eigen();
}
bool operator!=(const Tuple &lhs, const Tuple &rhs) {
  return lhs.Eigen() != rhs.Eigen();
}

bool Tuple::operator==(const Tuple &other) { return Eigen() == other.Eigen(); };
bool Tuple::operator!=(const Tuple &other) { return *this == other; }

Tuple Tuple::Reflect(const Tuple &other) {
  return Tuple(vec - other.Eigen() * 2 * vec.dot(other.Eigen()));
}