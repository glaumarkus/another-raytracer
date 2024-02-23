#pragma once

#include "vector2d.hpp"
#include <vector>

class Object;

struct IntersectionData {
  double t {0};
  const Object *obj {nullptr};
};

class Intersections {
public:
  IntersectionData Hit() const;
  bool Empty() const;
  void Add(double t, const Object *obj);
  const std::vector<IntersectionData> &Get() const;

protected:
  std::vector<IntersectionData> i_;
};
