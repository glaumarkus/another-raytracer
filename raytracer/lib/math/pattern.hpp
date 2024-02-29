#pragma once

#include "imgui/color.hpp"
#include "mat.hpp"

class Object;

class Pattern {
public:
  virtual void SetTransform(const Matrix<4> &mat) = 0;
  virtual const Matrix<4> &GetTransform() const = 0;
  virtual Color GetColor(const Point &point) const = 0;
  virtual Color ColorOnObject(const Point &point, const Object *obj) const;
};

class StripePattern : public Pattern {
public:
  StripePattern(Color first, Color second);
  void SetTransform(const Matrix<4> &mat) override;
  const Matrix<4> &GetTransform() const override;
  Color GetColor(const Point &point) const override;

protected:
  Color first_;
  Color second_;
  Matrix<4> transform_;
};

class TestPattern : public Pattern {
public:
  TestPattern() = default;
  void SetTransform(const Matrix<4> &mat) override;
  const Matrix<4> &GetTransform() const override;
  Color GetColor(const Point &point) const override;

protected:
  Matrix<4> transform_{math_constants::m4_identity};
};

class Gradient : public Pattern {
public:
  Gradient(Color first, Color second);
  void SetTransform(const Matrix<4> &mat) override;
  const Matrix<4> &GetTransform() const override;
  Color GetColor(const Point &point) const override;

protected:
  Color first_;
  Color second_;
  Matrix<4> transform_;
};

class Ring : public Pattern {
public:
  Ring(Color first, Color second);
  void SetTransform(const Matrix<4> &mat) override;
  const Matrix<4> &GetTransform() const override;
  Color GetColor(const Point &point) const override;

protected:
  Color first_;
  Color second_;
  Matrix<4> transform_;
};

class Checker : public Pattern {
public:
  Checker(Color first, Color second);
  void SetTransform(const Matrix<4> &mat) override;
  const Matrix<4> &GetTransform() const override;
  Color GetColor(const Point &point) const override;

protected:
  Color first_;
  Color second_;
  Matrix<4> transform_;
};

// ToDo: make a pattern that can hold other patterns
// ToDo: make a perlin noise pattern

