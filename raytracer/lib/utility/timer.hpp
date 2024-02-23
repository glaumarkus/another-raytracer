#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Timer {
public:
  Timer() = default;
  ~Timer() = default;
  std::string Measure() const;

protected:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_{
      std::chrono::high_resolution_clock::now()};
};

