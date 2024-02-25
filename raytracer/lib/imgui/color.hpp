#pragma once

#include "eigen3/Eigen/Dense"

struct ColorStruct {
  unsigned char r, g, b, a;
};

class Color {
public:
  Color() = default;
  Color(double v);
  Color(double r, double g, double b);
  Color(double r, double g, double b, double a);
  Color(Eigen::Vector4d &&v);
  Color(const Eigen::Vector4d &v);
  Color &operator+=(const Color &other);
  Color &operator-=(const Color &other);
  Color &operator*=(const Color &other);
  Color &operator*=(const double other);

  ColorStruct GetRenderColor();
  const Eigen::Vector4d &Eigen() const;

  virtual double &r();
  virtual double &g();
  virtual double &b();
  virtual double &a();
  virtual const double &r() const;
  virtual const double &g() const;
  virtual const double &b() const;
  virtual const double &a() const;

  virtual unsigned char ru() const;
  virtual unsigned char gu() const;
  virtual unsigned char bu() const;
  virtual unsigned char au() const;

  virtual ~Color() = default;

protected:
  Eigen::Vector4d vec;
};

Color operator+(const Color &lhs, const Color &rhs);
Color operator-(const Color &lhs, const Color &rhs);
Color operator*(const Color &lhs, const double rhs);
Color operator*(const Color &lhs, const Color &rhs);

namespace Colors {
static Color black(0, 0, 0);
static Color white(1, 1, 1);
} // namespace Colors

double ClampColorValue(double in);