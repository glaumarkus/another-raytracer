#pragma once

#include "vector2d.hpp"
#include <expected>
#include <vector>

class Object;
class Ray;

struct IntersectionData {
  double t{0};
  const Object *obj{nullptr};
};

enum class IntersectionError {
  kNoIntersections,
};

class Intersections {
public:
  std::expected<IntersectionData, IntersectionError> Hit() const;
  bool Empty() const;
  void Add(double t, const Object *obj);
  void Add(const std::vector<IntersectionData> &intersections);
  const std::vector<IntersectionData> &Get() const;
  void Sort();

protected:
  std::vector<IntersectionData> i_;
};

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