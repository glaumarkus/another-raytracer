#include "prepare_computations.hpp"

#include "intersections.hpp"
#include "constants.hpp"
#include "primitives/object.hpp"
#include "ray.hpp"

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
  intersection_over_point_ = intersection_point_ + normal_vector_ * kEpsilon;
}

Vector PrepareComputations::GetEye() const { return eye_vector_; }
Vector PrepareComputations::GetNormal() const { return normal_vector_; }
Point PrepareComputations::GetPoint() const { return intersection_point_; }
const Object *PrepareComputations::GetObject() const {
  return intersection_.obj;
}
bool PrepareComputations::IsInside() const { return is_inside_; }
Point PrepareComputations::GetOverPoint() const {
  return intersection_over_point_;
}