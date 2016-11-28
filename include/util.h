#ifndef SUGAISH_UTIL_H_
#define SUGAISH_UTIL_H_

#include <sstream>
#include <vector>

using std::ostringstream;
using std::string;
using std::vector;

string toString(vector<int> vec, int vecSize);

template <class ElementType>
string toString(ElementType *arr, int arrSize) {
  int i = 0;
  ostringstream s;

  for (i = 0; i < arrSize; ++i) {
    if (i == 0) {
      s << "[" << arr[i];
      continue;
    }
    s << " " << arr[i];
  }
  s << "]";
  return s.str();
}

extern int debug_out;

#endif  // SUGAISH_UTIL_H_
