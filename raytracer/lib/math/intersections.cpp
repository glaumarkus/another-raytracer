#include "intersections.hpp"
#include "math/constants.hpp"
#include "primitives/object.hpp"
#include "ray.hpp"

#include <algorithm>
#include <limits>

const std::vector<IntersectionData> &Intersections::Get() const { return i_; }
void Intersections::Add(double t, const Object *obj) {
  i_.emplace_back(IntersectionData{.t = t, .obj = obj});
}

void Intersections::Add(const std::vector<IntersectionData> &intersections) {
  i_.insert(i_.end(), intersections.begin(), intersections.end());
}

void Intersections::Sort() {
  std::sort(i_.begin(), i_.end(),
            [](const IntersectionData &lhs, const IntersectionData &rhs) {
              return lhs.t < rhs.t;
            });
}

bool Intersections::Empty() const { return i_.empty(); }

std::expected<IntersectionData, IntersectionError> Intersections::Hit() const {
  IntersectionData smallest;
  smallest.t = std::numeric_limits<double>::max();
  for (const auto &hits : i_) {
    if (hits.t < smallest.t && hits.t > 0) {
      smallest = hits;
    }
  }

  if (smallest.obj)
    return smallest;
  return std::unexpected<IntersectionError>(
      IntersectionError::kNoIntersections);
}

