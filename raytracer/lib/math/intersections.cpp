#include "intersections.hpp"
#include "object.hpp"
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

PrepareComputations::PrepareComputations(IntersectionData intersection_data,
                                         Ray r)
    : intersection_(intersection_data),
      intersection_point_(r.Position(intersection_data.t)),
      eye_vector_(r.GetDirection() * -1),
      normal_vector_(
          intersection_data.obj->GetNormalAtPoint(intersection_point_)),
      is_inside_(false) {
  if (normal_vector_.Dot(eye_vector_) < 0) {
    is_inside_ = true;
    normal_vector_ *= -1;
  }
}

Vector PrepareComputations::GetEye() const { return eye_vector_; }
Vector PrepareComputations::GetNormal() const { return normal_vector_; }
Point PrepareComputations::GetPoint() const { return intersection_point_; }
const Object *PrepareComputations::GetObject() const {
  return intersection_.obj;
}
bool PrepareComputations::IsInside() const { return is_inside_; }