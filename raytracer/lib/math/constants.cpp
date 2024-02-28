#include "constants.hpp"

bool equal(double first, double second) {
  bool result = false;
  if (std::abs(first - second) < kEpsilon) {
    result = true;
  }
  return result;
};

bool equalv(Tuple first, Tuple second) {
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
