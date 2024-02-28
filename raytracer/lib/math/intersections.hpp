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

