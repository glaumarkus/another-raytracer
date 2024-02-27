#pragma once

// #import <cmath>
#include "vector2d.hpp"
#include <math.h>
#include <valarray>
#include <iostream>

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
  } else {
    std::cout << first.x() << " " << second.x() << "\n";
    std::cout << first.y() << " " << second.y() << "\n";
    std::cout << first.z() << " " << second.z() << "\n";
  }
  return result;
};
