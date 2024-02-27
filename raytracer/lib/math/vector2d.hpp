#pragma once

#include "eigen3/Eigen/Dense"

class Tuple {
public:
  Tuple() = default;
  Tuple(double v);
  Tuple(double x, double y, double z);
  Tuple(double x, double y, double z, double w);
  Tuple(Eigen::Vector4d &&v);
  Tuple(const Eigen::Vector4d &v);
  Tuple &operator+=(const Tuple &other);
  Tuple &operator-=(const Tuple &other);
  Tuple &operator*=(const double v);
  Tuple &operator/=(const double v);

  bool operator==(const Tuple &other);
  bool operator!=(const Tuple &other);

  virtual double &x();
  virtual double &y();
  virtual double &z();
  virtual double &w();
  virtual const double &x() const;
  virtual const double &y() const;
  virtual const double &z() const;
  virtual const double &w() const;

  virtual const Eigen::Vector4d &Eigen() const;
  virtual void Negate();
  virtual double Magnitude() const;
  virtual void Normalize();
  Tuple Normalized() const;
  virtual double Dot(const Tuple &other) const;
  virtual Tuple Cross(const Tuple &other) const;
  Tuple Reflect(const Tuple& other) const; 

  virtual ~Tuple() = default;

protected:
  Eigen::Vector4d vec;
};

Tuple operator+(const Tuple &lhs, const Tuple &rhs);
Tuple operator-(const Tuple &lhs, const Tuple &rhs);
Tuple operator*(const Tuple &lhs, const double rhs);
Tuple operator/(const Tuple &lhs, const double rhs);
bool operator==(const Tuple &lhs, const Tuple &rhs);
bool operator!=(const Tuple &lhs, const Tuple &rhs);

double Dot(const Tuple &lhs, const Tuple &rhs);
// Tuple Cross(const Tuple &lhs, const Tuple &rhs);

// define Vector as Tuple
typedef Tuple Vector;

// define seperate Point
class Point : public Tuple {
public:
  Point() = default;
  Point(double v);
  Point(double x, double y, double z);
  Point(Eigen::Vector4d &&v);
  Point(const Eigen::Vector4d &v);

  virtual ~Point() = default;
  //   const Eigen::Vector4d &Eigen() const;
};

// add custom operators
Point operator+(const Point &point, const Vector &vector);
Point operator-(const Point &point, const Vector &vector);

//   Point &operator*=(const Point &other);
//   Point &operator/=(const Point &other);

// Point operator*(const Point &lhs, const Point &rhs);
// Point operator/(const Point &lhs, const Point &rhs);

// typedef Point Vector;

// class Vector {
//   Vector() = default;
//   Vector(double v);
//   Vector(double x, double y, double z);
//   Vector(Eigen::Vector4d &&v);
//   Vector(const Eigen::Vector4d &v);
//   Vector &operator+=(const Vector &other);
//   Vector &operator-=(const Vector &other);

//   double& x();
//   double& y();
//   double& z();
//   double& w();
//   const double& x() const;
//   const double& y() const;
//   const double& z() const;
//   const double& w() const;

//   ~Vector() = default;
//   Eigen::Vector4d vec;
// };

// class Vector : public Eigen::Vector4d {
// public:
//   Vector() = default;
//   Vector(double v);
//   Vector(double x, double y, double z);
//   Vector(Eigen::Vector4d &&v);
//   Vector(const Eigen::Vector4d &v);
//   Vector &operator+=(const Vector &other);
//   Vector &operator-=(const Vector &other);
//   Vector &operator*=(const Vector &other);
//   Vector &operator/=(const Vector &other);

//   ~Vector() = default;
// };

// Vector operator+(const Vector &lhs, const Vector &rhs);
// Vector operator-(const Vector &lhs, const Vector &rhs);
// Vector operator*(const Vector &lhs, const Vector &rhs);
// Vector operator/(const Vector &lhs, const Vector &rhs);

namespace math_constants {
static Tuple empty;
}