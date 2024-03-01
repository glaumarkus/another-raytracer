#include "prepare_computations.hpp"

#include "constants.hpp"
#include "intersections.hpp"
#include "primitives/object.hpp"
#include "ray.hpp"

struct in_vector_result {
  int idx{-1};
  bool result{false};
};

auto in_vector = [](const std::vector<const Object *> &intersections,
                    const Object *ptr) {
  for (int i = 0; i < intersections.size(); i++) {
    if (intersections[i] == ptr) {
      return in_vector_result{
          .idx = i,
          .result = true,
      };
    }
  }
  return in_vector_result();
};

auto remove_from_vector = [](std::vector<const Object *> &intersections,
                             const Object *ptr) {
  for (const auto &obj : intersections) {
    if (obj == ptr)
      return true;
  }
  return false;
};

PrepareComputations::PrepareComputations(const Intersections &intersection,
                                         Ray r)
    : intersections_(intersection), eye_vector_(r.GetDirection() * -1),
      is_inside_(false) {

  intersection_point_ = r.Position(intersections_.Hit().value().t);
  normal_vector_ =
      intersections_.Hit().value().obj->GetNormalAtPoint(intersection_point_);

  if (normal_vector_.Dot(eye_vector_) < 0) {
    is_inside_ = true;
    normal_vector_ *= -1;
  }
  intersection_over_point_ = intersection_point_ + normal_vector_ * kEpsilon;
  intersection_over_point_ = intersection_point_ - normal_vector_ * kEpsilon;
  reflect_vector_ = r.GetDirection().Reflect(normal_vector_);

  // calculate n1 / n2
  std::vector<const Object *> containers;
  for (const auto i : intersections_.Get()) {
    if (i.t == intersections_.Hit().value().t) {
      if (containers.empty()) {
        n1_ = 1.0;
      } else {
        n1_ =
            containers.at(containers.size() - 1)->GetMaterial().RefractiveIdx();
      }
    }

    // check if collision already happened
    auto in_vector_res = in_vector(containers, i.obj);
    if (in_vector_res.result) {
      containers.erase(containers.begin() + in_vector_res.idx);
    } else {
      containers.emplace_back(i.obj);
    }

    // append n2
    if (i.t == intersections_.Hit().value().t) {
      if (containers.empty()) {
        n2_ = 1.0;
      } else {
        n2_ =
            containers.at(containers.size() - 1)->GetMaterial().RefractiveIdx();
      }
      break;
    }
  }
}

Vector PrepareComputations::GetEye() const { return eye_vector_; }
Vector PrepareComputations::GetNormal() const { return normal_vector_; }
Point PrepareComputations::GetPoint() const { return intersection_point_; }
const Object *PrepareComputations::GetObject() const {
  return intersections_.Hit().value().obj;
}
bool PrepareComputations::IsInside() const { return is_inside_; }
Point PrepareComputations::GetOverPoint() const {
  return intersection_over_point_;
}

Vector PrepareComputations::GetReflect() const { return reflect_vector_; }

double PrepareComputations::N1() const { return n1_; }
double PrepareComputations::N2() const { return n2_; }
