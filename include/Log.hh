#ifndef LOG_HH
#define LOG_HH
#include <unistd.h>
#include <string.h>

#include <memory>
#include <sstream>


#include <Timestamp.hh>

#define size_t unsigned long

// LOG format:
/** level:[timestamp]
 * [INFO] 2024-06-08 14:26:32 \t[file]:[line] [message]
 */

namespace TB {
class Timestamp;
class LogImpl;
enum Level { INFO = 0, WARNING, ERROR, NUM };

class Log {
public:
public:
  Log();
  Log(Level level);
  Log(const char *file, int line, Level level);
  ~Log();

  std::ostream &stream();

public:
  std::shared_ptr<LogImpl> impl_;

}; // class Log

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_INFO Log(__FILENAME__, __LINE__, Level::INFO).stream()
#define LOG_WARNING Log(__FILENAME__, __LINE__, Level::WARNING).stream()
#define LOG_ERROR Log(__FILENAME__, __LINE__, Level::ERROR).stream()

#define LOG LOG_INFO

}; // namespace TB

#endif // Log_HH