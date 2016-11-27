#ifndef __UTIL_H__
#define __UTIL_H__
#include <sstream>
#include <vector>

using namespace std;

string toString(vector<int> vec, int vecSize);

template <class ElementType>
string toString(ElementType *arr, int arrSize) {
  int i = 0;
  ostringstream s;

  for (i = 0; i < arrSize; i++) {
    if (i == 0) {
      s << "[" << arr[i];
      continue;
    }
    s << " " << arr[i];
  }
  s << "]";
  return s.str();
}

#endif
