#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

enum class LogLevel {
  Verbose = 0,
  Debug = 1,
  Error = 5,
};

class Logger {
public:
  Logger() = default;
  ~Logger() = default;
  void SetLogLevel(LogLevel ll);
  void LogVerbose(const std::string &msg);
  void LogDebug(const std::string &msg);
  void LogError(const std::string &msg);
  const std::string &GetLog() const;

private:
  std::string GetDuration() const;
  void Log(const std::string &msg);
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_{
      std::chrono::high_resolution_clock::now()};
  LogLevel ll_{LogLevel::Verbose};
  std::string log_;
};
