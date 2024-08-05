#pragma once

#include <string.h>

#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>

#define size_t unsigned long
namespace pericycle {
enum Level { INFO = 0, WARNING, ERROR, NUM };

class Timestamp {
public:
  Timestamp() {}
  // Timestamp(size_t time);
  ~Timestamp() {}

public:
  size_t now() {
    auto timestamp = std::chrono::seconds(std::time(NULL));
    return static_cast<size_t>(timestamp.count());
  }
  std::string toString() {
    std::string tmp = std::to_string(now());
    return tmp;
  }
  std::string toFormatString() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
  }
};

class LogImpl {
public:
  LogImpl() {}
  LogImpl(const char *file, int line, Level level)
      : file_(file), line_(line), level_(level), timestamp_() {
    char log_header[1024];
    snprintf(log_header, sizeof(log_header), "[%s] %s\t%s:%d ",
             level_name[level_], timestamp_.toFormatString().c_str(), file_,
             line_);
    oss_ << log_header;
  }

  ~LogImpl() {}

public:
  void finish() { oss_ << '\n'; }

public:
  Level level_;
  std::ostringstream oss_;
  const char *file_;
  int line_;
  Timestamp timestamp_;
  constexpr static const char *level_name[Level::NUM] = {
      "\033[1;32mINFO\033[1;37m",
      "\033[1;33mWARNING\033[1;37m",
      "\033[1;31mERROR\033[1;37m",
  };
};

class Log {
public:
public:
  Log() : impl_(new LogImpl(__FILE__, __LINE__, Level::INFO)) {}
  Log(Level level) : impl_(new LogImpl(__FILE__, __LINE__, level)) {}
  Log(const char *file, int line, Level level)
      : impl_(new LogImpl(file, line, level)) {}
  ~Log() {
    impl_->finish();
    std::string buffer(impl_->oss_.str());
    ::fwrite(buffer.data(), 1, buffer.size(), stdout);
  }

  std::ostream &stream() { return impl_->oss_; }

public:
  std::shared_ptr<LogImpl> impl_;

}; // class Log

// @ref https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define __FILENAME__                                                           \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO Log(__FILENAME__, __LINE__, Level::INFO).stream()
#define LOG_WARNING Log(__FILENAME__, __LINE__, Level::WARNING).stream()
#define LOG_ERROR Log(__FILENAME__, __LINE__, Level::ERROR).stream()
#define LOG LOG_INFO
// #define SET_GLOBAL_LOG_LEVEL(LOG_LEVEL) todo
} // namespace TB