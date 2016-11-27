#include <cstdio>

#include <combination_number.h>
#include <cstdint>

#define COMBINATION_N_MAX 2000
#define COMBINATION_R_MAX 4

namespace CombinationNumber {

int64_t _m[COMBINATION_N_MAX][COMBINATION_R_MAX];
bool _initialized = false;

int64_t calc(int n, int r)
{
  int i;
  int64_t factor = 1;
  int64_t divisor = 1;

  int _r = r;
  for (i = 0; i < r; i++) {
    factor *= n;
    divisor *= _r;
    n--;
    _r--;
  }

  if (divisor == 0) {
    return 0;
  }

  return factor / divisor;
}

void init() {
  int i, j;
  if (_initialized) return;

  _initialized = true;
  for (i = 0; i < COMBINATION_N_MAX; i++) {
    for (j = 0; j < COMBINATION_R_MAX; j++) {
      _m[i][j] = calc(i, j);
    }
  }
}

int64_t get(int n, int r) {
  if (!_initialized) {
    printf("CombinationNumber is not initialzed.");
    return 0;
  }
  return _m[n][r];
}

}