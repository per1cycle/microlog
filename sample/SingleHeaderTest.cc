#include <log.h>

using namespace TB;

int main(int argc, char const *argv[])
{
  
  LOG_INFO << "test info";

  LOG_WARNING << "test warning";

  LOG_ERROR << "test error";

  return 0;
}
