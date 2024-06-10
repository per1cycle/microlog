#include <Log.hh>

using namespace TB;

class test
{
private:
  int val_;
public:
  test();
  test(int val);
  ~test();
};
test::test(){
  LOG_ERROR << "Cannot initialize test with empty constructor.";
}
test::test(int val)
{
  LOG_INFO << "Initialize test val with value " << val << ".";
  val_ = val;
}

test::~test()
{
  LOG_WARNING << "destruct class.";
  
}

int main(int argc, char const *argv[])
{
  for(size_t i = 0; i < 128; i ++)
    test t1 = test(10), t2 = test();  
  
  return 0;
}
