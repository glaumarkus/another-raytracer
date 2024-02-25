#include "color.hpp"
#include <algorithm>

Color::Color(double v) : vec(v, v, v, 1.0) {}
Color::Color(double r, double g, double b) : vec(r, g, b, 1.0) {}
Color::Color(double r, double g, double b, double a) : vec(r, g, b, a) {}
Color::Color(Eigen::Vector4d &&v) : vec(std::move(v)) {}
Color::Color(const Eigen::Vector4d &v) : vec(v) {}

double &Color::r() { return vec.x(); }
double &Color::g() { return vec.y(); }
double &Color::b() { return vec.z(); }
double &Color::a() { return vec.w(); }
const double &Color::r() const { return vec.x(); }
const double &Color::g() const { return vec.y(); }
const double &Color::b() const { return vec.z(); }
const double &Color::a() const { return vec.w(); }
const Eigen::Vector4d &Color::Eigen() const { return vec; }

// void Color::Cross(const Color &other) { vec.cross(other.vec); }

Color &Color::operator+=(const Color &other) {
  vec += other.vec;
  return *this;
}
Color &Color::operator-=(const Color &other) {
  vec -= other.vec;
  return *this;
}

Color &Color::operator*=(const Color &other) {
  vec =
      Eigen::Vector4d(vec.x() * other.Eigen().x(), vec.y() * other.Eigen().y(),
                      vec.z() * other.Eigen().z(), vec.w() * other.Eigen().w());

  return *this;
}

Color &Color::operator*=(const double other) {
  vec *= other;
  return *this;
}

Color operator+(const Color &lhs, const Color &rhs) {
  return Color(Eigen::Vector4d(lhs.Eigen() + rhs.Eigen()));
}
Color operator-(const Color &lhs, const Color &rhs) {
  return Color(Eigen::Vector4d(lhs.Eigen() - rhs.Eigen()));
}

Color operator*(const Color &lhs, const double rhs) {
  return Color(lhs.Eigen() * rhs);
}

Color operator*(const Color &lhs, const Color &rhs) {

  return Color(Eigen::Vector4d(
      lhs.Eigen().x() * rhs.Eigen().x(), lhs.Eigen().y() * rhs.Eigen().y(),
      lhs.Eigen().z() * rhs.Eigen().z(), lhs.Eigen().w() * rhs.Eigen().w()));
}

ColorStruct Color::GetRenderColor() {
  ColorStruct c;
  c.r = static_cast<unsigned char>(vec.x() * 255);
  c.g = static_cast<unsigned char>(vec.y() * 255);
  c.b = static_cast<unsigned char>(vec.z() * 255);
  c.a = static_cast<unsigned char>(vec.w() * 255);
  return c;
}

unsigned char Color::ru() const { return 255 * ClampColorValue(vec.x()); }
unsigned char Color::gu() const { return 255 * ClampColorValue(vec.y()); }
unsigned char Color::bu() const { return 255 * ClampColorValue(vec.z()); }
unsigned char Color::au() const { return 255 * ClampColorValue(vec.w()); }

double ClampColorValue(double in) { return std::clamp(in, 0.0, 1.0); }