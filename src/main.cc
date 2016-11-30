#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <iostream>

#include <sugaish.h>

int main() {
  Sugaish::init();
  const int BASE_N_MIN = 100;
  const int BASE_N_MAX = 1000;
  Sugaish::find3(BASE_N_MIN, BASE_N_MAX);
}
