#pragma once

#include "timer.hpp"
#include <string>

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
  Timer timer_;
  LogLevel ll_{LogLevel::Verbose};
  std::string log_;
};
