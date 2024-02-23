#pragma once

// #import <cmath>
#include <math.h>
#include <valarray>

constexpr double kEpsilon = 0.00001;

auto equal = [](double first, double second) {
  bool result = false;
  if (std::abs(first - second) < kEpsilon) {
    result = true;
  }
  return result;
};