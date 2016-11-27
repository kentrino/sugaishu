#include <sstream>
#include <vector>

#include <util.h>

using namespace std;

string toString(vector<int> vec, int vecSize)
{
  vector<int>::iterator it;
  ostringstream s;

  for (it = vec.begin(); it < vec.begin() + vecSize; it++) {
    if (it == vec.begin()) {
      s << "[" << *it;
      continue;
    }
    s << " " << *it;
  }
  s << "]";
  return s.str();
}
