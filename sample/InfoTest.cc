#include <Log.hh>
using namespace TB;

int main(int argc, char const *argv[]) {
  LOG_INFO << "hello world";
  int i;
  LOG_WARNING << i << " is not initialized.";
  for (int j = 0; j < 5; j++) {
    LOG_INFO << "current i = " << i << "."
             << "current j = " << j;
  }
#ifdef __WIN__
  LOG_INFO << "On window platform.";
#else
  LOG_ERROR << "Not on window platform.";
#endif

      return 0;
}
