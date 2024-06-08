#include <Log.hh>

namespace TB {
class LogImpl {
public:
  LogImpl() {}
  LogImpl(const char *file, int line, Level level)
      : file_(file), line_(line), level_(level), timestamp_() {
    char log_header[1024];
    snprintf(log_header, sizeof(log_header), "[%s] %s\t%s:%d ", level_name[level_],
             timestamp_.toFormatString().c_str(), file_, line_);
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

Log::Log() : impl_(new LogImpl(__FILE__, __LINE__, Level::INFO)) {}
Log::Log(const char *file, int line, Level level) : impl_(new LogImpl(file, line, level)) {}

Log::~Log() {
  impl_->finish();
  std::string buffer(impl_->oss_.str());

  ::write(1, buffer.data(), buffer.size());
}

std::ostream &Log::stream() { return impl_->oss_; }

} // namespace TB
