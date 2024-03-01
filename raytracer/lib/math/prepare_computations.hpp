#pragma once

#include "intersections.hpp"
#include "vector2d.hpp"

class Object;
class Intersections;

class PrepareComputations {
public:
  PrepareComputations() = delete;
  PrepareComputations(const Intersections &intersection, Ray r);
  Vector GetEye() const;
  Vector GetNormal() const;
  Vector GetReflect() const;
  Point GetPoint() const;
  Point GetOverPoint() const;
  const Object *GetObject() const;
  bool IsInside() const;
  double N1() const;
  double N2() const;

protected:
  const Intersections &intersections_;
  Point intersection_point_;
  Point intersection_over_point_;
  Vector eye_vector_;
  Vector normal_vector_;
  Vector reflect_vector_;
  bool is_inside_;
  double n1_;
  double n2_;
};