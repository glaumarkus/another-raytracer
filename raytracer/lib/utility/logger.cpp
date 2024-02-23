#include "logger.hpp"

const std::string &Logger::GetLog() const { return log_; }

void Logger::Log(const std::string &msg) {
  log_ += "[" + GetDuration() + "] ";
  log_ += msg + "\n";
}
std::string Logger::GetDuration() const {
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start_time_);
  double milliseconds = duration.count() / 1000.0;
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(4) << std::setw(9) << milliseconds
         << "ms";
  return stream.str();
}

void Logger::SetLogLevel(LogLevel ll) { ll_ = ll; }
void Logger::LogVerbose(const std::string &msg) {
  if (static_cast<int>(ll_) <= static_cast<int>(LogLevel::Verbose)) {
    Log(msg);
  }
}
void Logger::LogDebug(const std::string &msg) {
  if (static_cast<int>(ll_) <= static_cast<int>(LogLevel::Debug)) {
    Log(msg);
  }
}
void Logger::LogError(const std::string &msg) {
  if (static_cast<int>(ll_) <= static_cast<int>(LogLevel::Error)) {
    Log(msg);
  }
}