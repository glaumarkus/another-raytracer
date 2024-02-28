#pragma once

#include "intersections.hpp"
#include "vector2d.hpp"

class Object;
class IntersectionData;

class PrepareComputations {
public:
  PrepareComputations() = delete;
  PrepareComputations(IntersectionData intersection_data, Ray r);
  Vector GetEye() const;
  Vector GetNormal() const;
  Point GetPoint() const;
  Point GetOverPoint() const;
  const Object *GetObject() const;
  bool IsInside() const;

protected:
  const IntersectionData intersection_;
  Point intersection_point_;
  Point intersection_over_point_;
  Vector eye_vector_;
  Vector normal_vector_;
  bool is_inside_;
};