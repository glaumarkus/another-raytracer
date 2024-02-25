#pragma once

// #import <cmath>
#include <math.h>
#include <valarray>
#include "vector2d.hpp"

constexpr double kEpsilon = 0.00001;

auto equal = [](double first, double second) {
  bool result = false;
  if (std::abs(first - second) < kEpsilon) {
    result = true;
  }
  return result;
};

auto equalv = [](Tuple first, Tuple second) {
  bool result = false;
  if (std::abs(first.x() - second.x()) < kEpsilon &&
      std::abs(first.y() - second.y()) < kEpsilon &&
      std::abs(first.z() - second.z()) < kEpsilon) {
    result = true;
  }
  return result;
};

