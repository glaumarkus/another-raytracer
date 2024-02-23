#include "intersections.hpp"
#include <limits>

const std::vector<IntersectionData> &Intersections::Get() const { return i_; }
void Intersections::Add(double t, const Object *obj) {
  i_.emplace_back(IntersectionData{.t = t, .obj = obj});
}
bool Intersections::Empty() const { return i_.empty(); }

IntersectionData Intersections::Hit() const {
  IntersectionData smallest;
  smallest.t = std::numeric_limits<double>::max();
  for (const auto &hits : i_) {
    if (hits.t < smallest.t && hits.t > 0) {
      smallest = hits;
    }
  }
  return smallest;
}