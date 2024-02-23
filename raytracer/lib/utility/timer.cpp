#include "timer.hpp"

std::string Timer::Measure() const {
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start_time_);
  double milliseconds = duration.count() / 1000.0;
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(4) << std::setw(9) << milliseconds
         << "ms";
  return stream.str();
}